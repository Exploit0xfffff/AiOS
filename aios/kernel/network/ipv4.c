#include <kernel/ipv4.h>
#include <kernel/icmp.h>
#include <kernel/socket.h>
#include <kernel/process.h>
#include <kernel/rtl8139.h>
#include <kernel/arp.h>
#include <kernel/time.h>
#include <kernel/panic.h>
#include <kernel/errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static uint16_t id_counter = 0;
static uint64_t pkt_received = 0;
static void* ipv4_receive_buffer = NULL;
static uint16_t last_received_pkt_len = 0;

int init_ipv4()
{
    ipv4_receive_buffer = malloc(RTL8139_TRANSMIT_BUF_SIZE);
    memset(ipv4_receive_buffer, 0, RTL8139_TRANSMIT_BUF_SIZE);
    // Announce our hardcoded ip address before sending out any packet
    arp_announce_ip(MY_IP);
    // Get default gateway MAC address
    arp_probe(DEFAULT_GATEWAY_IP);
    return 0;
}

int ipv4_prep_pkt(ipv4_opt* opt, void* buf, uint16_t buf_len) {

    eth_opt e = (eth_opt) {.type = ETHER_TYPE_IPv4};
    
    // Hardcoded type of IP routing table
    // If local (determined by SUBNET_MASK), send to the target machine
    // Otherwise, send to default gateway
    if((SUBNET_MASK & *(uint32_t*) opt->dst.addr) == (SUBNET_MASK & *(uint32_t*) DEFAULT_GATEWAY_IP.addr)) {
        int r = arp_ip2mac(opt->dst, &e.dest_mac);
        if(r < 0) {
            arp_probe(opt->dst);
            return -1;
        }
    } else {
        int r = arp_ip2mac(DEFAULT_GATEWAY_IP, &e.dest_mac);
        if(r < 0) {
            arp_probe(DEFAULT_GATEWAY_IP);
            return -1;
        }
    }

    int len_eth_hdr = eth_prep_pkt(&e, buf, buf_len);
    if(len_eth_hdr < 0) return len_eth_hdr;
    if(len_eth_hdr + sizeof(ipv4_header) > buf_len) return -1;
    

    ipv4_header* hdr = (ipv4_header*) (buf + len_eth_hdr);
    // swap endianess of all multi bytes fields
    // assuming ip_addr is store in big endian already
    *hdr = (ipv4_header) {
        .ver_ihl = IPv4_VER_IHL,
        .dscp_ecn = IPv4_DSCP_ECN,
        .id = switch_endian16(id_counter++),
        .flags_fragoffset = switch_endian16(IPv4_NO_FRAG),
        .ttl = opt->ttl,
        .protocol = opt->protocol,
        .src = MY_IP,
        .dst = opt->dst
    };

    return len_eth_hdr + sizeof(ipv4_header);
}

int ipv4_send_pkt(void* buf, uint16_t pkt_len) {
    ipv4_header* hdr = (ipv4_header*) (buf + sizeof(eth_header));
    
    // Which is Correct?
    // hdr->len = pkt_len;
    hdr->len = switch_endian16(pkt_len - sizeof(eth_header));

    // the checksum is already in the right endianess
    hdr->hdr_checksum = ipv4_icmp_checksum(hdr, sizeof(ipv4_header));
    int res = eth_send_pkt(buf, pkt_len);
    return res;
}

int ipv4_opt_from_header(const ipv4_header* hdr, ipv4_opt* opt)
{
    *opt = (ipv4_opt) {.protocol = hdr->protocol, .dst = hdr->dst, .ttl = hdr->ttl, .src = hdr->src};
    return 0;
}

int ipv4_process_packet(void* buf, uint len)
{
    ipv4_header* hdr = (ipv4_header*) buf;

    uint8_t header_len = ((hdr->ver_ihl) & 0x0F) * 4;
    uint16_t orig_checksum = hdr->hdr_checksum;
    hdr->hdr_checksum = 0;
    uint16_t our_checksum = ipv4_icmp_checksum(buf, header_len);
    hdr->hdr_checksum = orig_checksum;
    char* eq = (orig_checksum == our_checksum) ? "==":"!=";
    
    printf("IPv4 Pkt Received from %u.%u.%u.%u, Chksum: Received[0x%x] %s Calculated[0x%x]\n", 
        hdr->src.addr[0], hdr->src.addr[1], hdr->src.addr[2], hdr->src.addr[3], 
        orig_checksum, eq, our_checksum);

    last_received_pkt_len = len;
    memmove(ipv4_receive_buffer, buf, len);
    pkt_received++;

    int n_socket_processed = 0;
    if(hdr->protocol == IPv4_PROTOCAL_ICMP) {
        PANIC_ASSERT(len >= sizeof(ipv4_header));
        n_socket_processed = socket_process_pkt(IPPROTO_ICMP, buf, len);
    } else {
        // other unrecognized protocols
        n_socket_processed = socket_process_pkt(IPPROTO_RAW, buf, len);
    }

    // if package does not belong to any socket, print it out and drop
    if(n_socket_processed == 0) {
        printf("IPv4 Pkt received, no one listening, unkown protocol:\n");
        uint8_t* buff = (uint8_t*) buf;
        for(uint i=0; i<len; i++) {
            if(i % 16 == 0 && i != 0) {
                printf("\n");
            }
            printf("0x%x ", buff[i]);
        }
        printf("\n");
    }

    return 0;
}


int ipv4_wait_for_next_packet(void* buf, uint buf_size, uint timeout_sec)
{
    uint64_t n = pkt_received;
    date_time start = current_datetime(), end;
    time_t epoch0 = datetime2epoch(&start), epoch1;
    while(pkt_received == n) {
        end = current_datetime();
        epoch1 = datetime2epoch(&end);
        if((uint)(epoch1 - epoch0) > timeout_sec) {
            return -1;
        }
        yield();
    }
    if(buf_size < last_received_pkt_len) {
        return -1;
    }
    memmove(buf, ipv4_receive_buffer, last_received_pkt_len);
    return last_received_pkt_len;
}

// ipv4_opt* new_ipv4_opt()
// {
//     ipv4_opt* opt = malloc(sizeof(ipv4_opt));
//     memset(opt, 0, sizeof(ipv4_opt));
//     return opt;
// }


// int drop_ipv4_header(void* pkt, uint16_t pkt_len, void** pkt_no_header)
// {
//     if(pkt_len < sizeof(ipv4_header)) return -1;
//     *pkt_no_header = pkt + sizeof(ipv4_header);
//     return pkt_len - sizeof(ipv4_header);
// }