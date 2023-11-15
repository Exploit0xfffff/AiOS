#ifndef _KERNEL_RTL8139_H
#define _KERNEL_RTL8139_H

#include <stdint.h>
#include <common.h>
#include <kernel/ethernet.h>

// Receive buffer size, actual size is below + 1500 to allow WRAP=1 in Rx Configuration Register
#define RTL8139_RECEIVE_BUF_SIZE (8192+16)
#define RTL8139_TRANSMIT_BUF_SIZE 1792

// typedef struct packet {
//     uint8_t id;
//     uint32_t size;
//     char buf[RTL8139_TRANSMIT_BUF_SIZE];
// } packet;


void init_rtl8139(uint8_t bus, uint8_t device, uint8_t function);
// packet* rtl8139_get_empty_packet();
int rtl8139_send_packet(void* buf, uint size);
mac_addr rtl8139_mac();

// Source: https://github.com/doug65536/dgos/blob/master/kernel/device/rtl8139/rtl8139.bits.h

//
// RTL8139_IDR_HI: MAC address
#define RTL8139_IDR_HI 0x00

//
// RTL8139_IDR_LO: MAC address
#define RTL8139_IDR_LO 0x04

//
// RTL8139_MAR_LO: Multicast Address Register (must be 32-bit I/O)
#define RTL8139_MAR_LO 0x08

//
// RTL8139_MAR_HI: Multicast Address Register (must be 32-bit I/O)
#define RTL8139_MAR_HI 0x0C

//
// RTL8139_CR: Command register
#define RTL8139_CR                   0x37


// Reset
#define RTL8139_CR_RST_BIT           4

// Rx enable
#define RTL8139_CR_RXEN_BIT          3

// Tx enable
#define RTL8139_CR_TXEN_BIT          2

// Rx buffer is empty (read only)
#define RTL8139_CR_RXEMPTY_BIT       0


// Reset
#define RTL8139_CR_RST_BITS          1

// Rx enable
#define RTL8139_CR_RXEN_BITS         1

// Tx enable
#define RTL8139_CR_TXEN_BITS         1

// Rx buffer is empty (read only)
#define RTL8139_CR_RXEMPTY_BITS      1

// Reset
#define RTL8139_CR_RST_MASK          ((1U << RTL8139_CR_RST_BITS)-1)

// Rx enable
#define RTL8139_CR_RXEN_MASK         ((1U << RTL8139_CR_RXEN_BITS)-1)

// Tx enable
#define RTL8139_CR_TXEN_MASK         ((1U << RTL8139_CR_TXEN_BITS)-1)

// Rx buffer is empty (read only)
#define RTL8139_CR_RXEMPTY_MASK      ((1U << RTL8139_CR_RXEMPTY_BITS)-1)

// Reset
#define RTL8139_CR_RST \
    (RTL8139_CR_RST_MASK << RTL8139_CR_RST_BIT)

// Rx enable
#define RTL8139_CR_RXEN \
    (RTL8139_CR_RXEN_MASK << RTL8139_CR_RXEN_BIT)

// Tx enable
#define RTL8139_CR_TXEN \
    (RTL8139_CR_TXEN_MASK << RTL8139_CR_TXEN_BIT)

// Rx buffer is empty (read only)
#define RTL8139_CR_RXEMPTY \
    (RTL8139_CR_RXEMPTY_MASK << RTL8139_CR_RXEMPTY_BIT)


// Reset
#define RTL8139_CR_RST_n(n)          ((n) << RTL8139_CR_RST_BIT)

// Rx enable
#define RTL8139_CR_RXEN_n(n)         ((n) << RTL8139_CR_RXEN_BIT)

// Tx enable
#define RTL8139_CR_TXEN_n(n)         ((n) << RTL8139_CR_TXEN_BIT)

// Rx buffer is empty (read only)
#define RTL8139_CR_RXEMPTY_n(n)      ((n) << RTL8139_CR_RXEMPTY_BIT)


// Reset
#define RTL8139_CR_RST_GET(n) \
    (((n) >> RTL8139_CR_RST_BIT) & RTL8139_CR_RST_MASK)

// Rx enable
#define RTL8139_CR_RXEN_GET(n) \
    (((n) >> RTL8139_CR_RXEN_BIT) & RTL8139_CR_RXEN_MASK)

// Tx enable
#define RTL8139_CR_TXEN_GET(n) \
    (((n) >> RTL8139_CR_TXEN_BIT) & RTL8139_CR_TXEN_MASK)

// Rx buffer is empty (read only)
#define RTL8139_CR_RXEMPTY_GET(n) \
    (((n) >> RTL8139_CR_RXEMPTY_BIT) & RTL8139_CR_RXEMPTY_MASK)


// Reset
#define RTL8139_CR_RST_SET(r,n) \
    ((r) = ((r) & ~RTL8139_CR_RST) | RTL8139_CR_RST_n((n)))

// Rx enable
#define RTL8139_CR_RXEN_SET(r,n) \
    ((r) = ((r) & ~RTL8139_CR_RXEN) | RTL8139_CR_RXEN_n((n)))

// Tx enable
#define RTL8139_CR_TXEN_SET(r,n) \
    ((r) = ((r) & ~RTL8139_CR_TXEN) | RTL8139_CR_TXEN_n((n)))

// Rx buffer is empty (read only)
#define RTL8139_CR_RXEMPTY_SET(r,n) \
    ((r) = ((r) & ~RTL8139_CR_RXEMPTY) | RTL8139_CR_RXEMPTY_n((n)))

//
// RTL8139_TSD_n(n): Tx status descriptor 0-3 (32-bit)
#define RTL8139_TSD_n(n) (0x10+((n)<<2))

// RTL8139_TSD


// Carrier sense lost (read only)
#define RTL8139_TSD_CRS_BIT          31

// Transmit aborted (read only)
#define RTL8139_TSD_TABT_BIT         30

// Out of window collision (read only)
#define RTL8139_TSD_OWC_BIT          29

// CD Heart Beat (10Mbps only) (read only)
#define RTL8139_TSD_CDH_BIT          28

// Number of tx collisions count
#define RTL8139_TSD_NCC_BIT          24

// Early tx threshold (in units of 8 bytes, 0=8 bytes, max 2KB)
#define RTL8139_TSD_ERTXTH_BIT       16

// Transmit OK (read only)
#define RTL8139_TSD_TOK_BIT          15

// Transmit FIFO underrun (read only)
#define RTL8139_TSD_TUN_BIT          14

// Owned 1=by driver, 0=by NIC
#define RTL8139_TSD_OWN_BIT          13

// Tx packet size
#define RTL8139_TSD_SIZE_BIT         0


// Carrier sense lost (read only)
#define RTL8139_TSD_CRS_BITS         1

// Transmit aborted (read only)
#define RTL8139_TSD_TABT_BITS        1

// Out of window collision (read only)
#define RTL8139_TSD_OWC_BITS         1

// CD Heart Beat (10Mbps only) (read only)
#define RTL8139_TSD_CDH_BITS         1

// Number of tx collisions count
#define RTL8139_TSD_NCC_BITS         4

// Early tx threshold (in units of 8 bytes, 0=8 bytes, max 2KB)
#define RTL8139_TSD_ERTXTH_BITS      6

// Transmit OK (read only)
#define RTL8139_TSD_TOK_BITS         1

// Transmit FIFO underrun (read only)
#define RTL8139_TSD_TUN_BITS         1

// Owned 1=by driver, 0=by NIC
#define RTL8139_TSD_OWN_BITS         1

// Tx packet size
#define RTL8139_TSD_SIZE_BITS        13

// Carrier sense lost (read only)
#define RTL8139_TSD_CRS_MASK         ((1U << RTL8139_TSD_CRS_BITS)-1)

// Transmit aborted (read only)
#define RTL8139_TSD_TABT_MASK        ((1U << RTL8139_TSD_TABT_BITS)-1)

// Out of window collision (read only)
#define RTL8139_TSD_OWC_MASK         ((1U << RTL8139_TSD_OWC_BITS)-1)

// CD Heart Beat (10Mbps only) (read only)
#define RTL8139_TSD_CDH_MASK         ((1U << RTL8139_TSD_CDH_BITS)-1)

// Number of tx collisions count
#define RTL8139_TSD_NCC_MASK         ((1U << RTL8139_TSD_NCC_BITS)-1)

// Early tx threshold (in units of 8 bytes, 0=8 bytes, max 2KB)
#define RTL8139_TSD_ERTXTH_MASK      ((1U << RTL8139_TSD_ERTXTH_BITS)-1)

// Transmit OK (read only)
#define RTL8139_TSD_TOK_MASK         ((1U << RTL8139_TSD_TOK_BITS)-1)

// Transmit FIFO underrun (read only)
#define RTL8139_TSD_TUN_MASK         ((1U << RTL8139_TSD_TUN_BITS)-1)

// Owned 1=by driver, 0=by NIC
#define RTL8139_TSD_OWN_MASK         ((1U << RTL8139_TSD_OWN_BITS)-1)

// Tx packet size
#define RTL8139_TSD_SIZE_MASK        ((1U << RTL8139_TSD_SIZE_BITS)-1)

// Carrier sense lost (read only)
#define RTL8139_TSD_CRS \
    (RTL8139_TSD_CRS_MASK << RTL8139_TSD_CRS_BIT)

// Transmit aborted (read only)
#define RTL8139_TSD_TABT \
    (RTL8139_TSD_TABT_MASK << RTL8139_TSD_TABT_BIT)

// Out of window collision (read only)
#define RTL8139_TSD_OWC \
    (RTL8139_TSD_OWC_MASK << RTL8139_TSD_OWC_BIT)

// CD Heart Beat (10Mbps only) (read only)
#define RTL8139_TSD_CDH \
    (RTL8139_TSD_CDH_MASK << RTL8139_TSD_CDH_BIT)

// Number of tx collisions count
#define RTL8139_TSD_NCC \
    (RTL8139_TSD_NCC_MASK << RTL8139_TSD_NCC_BIT)

// Early tx threshold (in units of 8 bytes, 0=8 bytes, max 2KB)
#define RTL8139_TSD_ERTXTH \
    (RTL8139_TSD_ERTXTH_MASK << RTL8139_TSD_ERTXTH_BIT)

// Transmit OK (read only)
#define RTL8139_TSD_TOK \
    (RTL8139_TSD_TOK_MASK << RTL8139_TSD_TOK_BIT)

// Transmit FIFO underrun (read only)
#define RTL8139_TSD_TUN \
    (RTL8139_TSD_TUN_MASK << RTL8139_TSD_TUN_BIT)

// Owned 1=by driver, 0=by NIC
#define RTL8139_TSD_OWN \
    (RTL8139_TSD_OWN_MASK << RTL8139_TSD_OWN_BIT)

// Tx packet size
#define RTL8139_TSD_SIZE \
    (RTL8139_TSD_SIZE_MASK << RTL8139_TSD_SIZE_BIT)


// Carrier sense lost (read only)
#define RTL8139_TSD_CRS_n(n)         ((n) << RTL8139_TSD_CRS_BIT)

// Transmit aborted (read only)
#define RTL8139_TSD_TABT_n(n)        ((n) << RTL8139_TSD_TABT_BIT)

// Out of window collision (read only)
#define RTL8139_TSD_OWC_n(n)         ((n) << RTL8139_TSD_OWC_BIT)

// CD Heart Beat (10Mbps only) (read only)
#define RTL8139_TSD_CDH_n(n)         ((n) << RTL8139_TSD_CDH_BIT)

// Number of tx collisions count
#define RTL8139_TSD_NCC_n(n)         ((n) << RTL8139_TSD_NCC_BIT)

// Early tx threshold (in units of 8 bytes, 0=8 bytes, max 2KB)
#define RTL8139_TSD_ERTXTH_n(n)      ((n) << RTL8139_TSD_ERTXTH_BIT)

// Transmit OK (read only)
#define RTL8139_TSD_TOK_n(n)         ((n) << RTL8139_TSD_TOK_BIT)

// Transmit FIFO underrun (read only)
#define RTL8139_TSD_TUN_n(n)         ((n) << RTL8139_TSD_TUN_BIT)

// Owned 1=by driver, 0=by NIC
#define RTL8139_TSD_OWN_n(n)         ((n) << RTL8139_TSD_OWN_BIT)

// Tx packet size
#define RTL8139_TSD_SIZE_n(n)        ((n) << RTL8139_TSD_SIZE_BIT)


// Carrier sense lost (read only)
#define RTL8139_TSD_CRS_GET(n) \
    (((n) >> RTL8139_TSD_CRS_BIT) & RTL8139_TSD_CRS_MASK)

// Transmit aborted (read only)
#define RTL8139_TSD_TABT_GET(n) \
    (((n) >> RTL8139_TSD_TABT_BIT) & RTL8139_TSD_TABT_MASK)

// Out of window collision (read only)
#define RTL8139_TSD_OWC_GET(n) \
    (((n) >> RTL8139_TSD_OWC_BIT) & RTL8139_TSD_OWC_MASK)

// CD Heart Beat (10Mbps only) (read only)
#define RTL8139_TSD_CDH_GET(n) \
    (((n) >> RTL8139_TSD_CDH_BIT) & RTL8139_TSD_CDH_MASK)

// Number of tx collisions count
#define RTL8139_TSD_NCC_GET(n) \
    (((n) >> RTL8139_TSD_NCC_BIT) & RTL8139_TSD_NCC_MASK)

// Early tx threshold (in units of 8 bytes, 0=8 bytes, max 2KB)
#define RTL8139_TSD_ERTXTH_GET(n) \
    (((n) >> RTL8139_TSD_ERTXTH_BIT) & RTL8139_TSD_ERTXTH_MASK)

// Transmit OK (read only)
#define RTL8139_TSD_TOK_GET(n) \
    (((n) >> RTL8139_TSD_TOK_BIT) & RTL8139_TSD_TOK_MASK)

// Transmit FIFO underrun (read only)
#define RTL8139_TSD_TUN_GET(n) \
    (((n) >> RTL8139_TSD_TUN_BIT) & RTL8139_TSD_TUN_MASK)

// Owned 1=by driver, 0=by NIC
#define RTL8139_TSD_OWN_GET(n) \
    (((n) >> RTL8139_TSD_OWN_BIT) & RTL8139_TSD_OWN_MASK)

// Tx packet size
#define RTL8139_TSD_SIZE_GET(n) \
    (((n) >> RTL8139_TSD_SIZE_BIT) & RTL8139_TSD_SIZE_MASK)


// Carrier sense lost (read only)
#define RTL8139_TSD_CRS_SET(r,n) \
    ((r) = ((r) & ~RTL8139_TSD_CRS) | RTL8139_TSD_CRS_n((n)))

// Transmit aborted (read only)
#define RTL8139_TSD_TABT_SET(r,n) \
    ((r) = ((r) & ~RTL8139_TSD_TABT) | RTL8139_TSD_TABT_n((n)))

// Out of window collision (read only)
#define RTL8139_TSD_OWC_SET(r,n) \
    ((r) = ((r) & ~RTL8139_TSD_OWC) | RTL8139_TSD_OWC_n((n)))

// CD Heart Beat (10Mbps only) (read only)
#define RTL8139_TSD_CDH_SET(r,n) \
    ((r) = ((r) & ~RTL8139_TSD_CDH) | RTL8139_TSD_CDH_n((n)))

// Number of tx collisions count
#define RTL8139_TSD_NCC_SET(r,n) \
    ((r) = ((r) & ~RTL8139_TSD_NCC) | RTL8139_TSD_NCC_n((n)))

// Early tx threshold (in units of 8 bytes, 0=8 bytes, max 2KB)
#define RTL8139_TSD_ERTXTH_SET(r,n) \
    ((r) = ((r) & ~RTL8139_TSD_ERTXTH) | RTL8139_TSD_ERTXTH_n((n)))

// Transmit OK (read only)
#define RTL8139_TSD_TOK_SET(r,n) \
    ((r) = ((r) & ~RTL8139_TSD_TOK) | RTL8139_TSD_TOK_n((n)))

// Transmit FIFO underrun (read only)
#define RTL8139_TSD_TUN_SET(r,n) \
    ((r) = ((r) & ~RTL8139_TSD_TUN) | RTL8139_TSD_TUN_n((n)))

// Owned 1=by driver, 0=by NIC
#define RTL8139_TSD_OWN_SET(r,n) \
    ((r) = ((r) & ~RTL8139_TSD_OWN) | RTL8139_TSD_OWN_n((n)))

// Tx packet size
#define RTL8139_TSD_SIZE_SET(r,n) \
    ((r) = ((r) & ~RTL8139_TSD_SIZE) | RTL8139_TSD_SIZE_n((n)))

// RTL8139_TSD_SIZE_MAX
#define RTL8139_TSD_SIZE_MAX 1792

//
// RTL8139_TSAD_n(n): Tx start address descriptor 0-3 (32-bit)
#define RTL8139_TSAD_n(n) (0x20+((n)<<2))

//
// RTL8139_RBSTART: Rx buffer address descriptor (32-bit)
#define RTL8139_RBSTART 0x30

//
// RTL8139_ERBCR: Early rx byte count (16-bit)
#define RTL8139_ERBCR 0x34

//
// RTL8139_ERSR: Early rx status register (8-bit)
#define RTL8139_ERSR 0x36

//
// RTL8139_CAPR: Current address of packet read (16-bit)
#define RTL8139_CAPR 0x38

//
// RTL8139_CBR: Current rx buffer address (16-bit)
#define RTL8139_CBR 0x3A

//
// RTL8139_IMR: Interrupt Mask Register (16-bit)
#define RTL8139_IMR 0x3C

//
// RTL8139_ISR: Interrupt Status Register (16-bit)
#define RTL8139_ISR 0x3E

//
// RTL8139_IxR: RTL8139_IMR and RTL8139_ISR: Interrupt Mask/Status Registers


// System error
#define RTL8139_IxR_SERR_BIT          15

// Timeout
#define RTL8139_IxR_TIMEOUT_BIT       14

// Cable length change
#define RTL8139_IxR_LENCHG_BIT        13

// Rx FIFO Overflow
#define RTL8139_IxR_FOVW_BIT          6

// Packet underrun / link change
#define RTL8139_IxR_PUNLC_BIT         5

// Rx overflow
#define RTL8139_IxR_RXOVW_BIT         4

// Transmit error
#define RTL8139_IxR_TER_BIT           3

// Transmit OK
#define RTL8139_IxR_TOK_BIT           2

// Rx error
#define RTL8139_IxR_RER_BIT           1

// Rx OK
#define RTL8139_IxR_ROK_BIT           0


// System error
#define RTL8139_IxR_SERR_BITS         1

// Timeout
#define RTL8139_IxR_TIMEOUT_BITS      1

// Cable length change
#define RTL8139_IxR_LENCHG_BITS       1

// Rx FIFO Overflow
#define RTL8139_IxR_FOVW_BITS         1

// Packet underrun / link change
#define RTL8139_IxR_PUNLC_BITS        1

// Rx overflow
#define RTL8139_IxR_RXOVW_BITS        1

// Transmit error
#define RTL8139_IxR_TER_BITS          1

// Transmit OK
#define RTL8139_IxR_TOK_BITS          1

// Rx error
#define RTL8139_IxR_RER_BITS          1

// Rx OK
#define RTL8139_IxR_ROK_BITS          1

// System error
#define RTL8139_IxR_SERR_MASK         ((1U << RTL8139_IxR_SERR_BITS)-1)

// Timeout
#define RTL8139_IxR_TIMEOUT_MASK      ((1U << RTL8139_IxR_TIMEOUT_BITS)-1)

// Cable length change
#define RTL8139_IxR_LENCHG_MASK       ((1U << RTL8139_IxR_LENCHG_BITS)-1)

// Rx FIFO Overflow
#define RTL8139_IxR_FOVW_MASK         ((1U << RTL8139_IxR_FOVW_BITS)-1)

// Packet underrun / link change
#define RTL8139_IxR_PUNLC_MASK        ((1U << RTL8139_IxR_PUNLC_BITS)-1)

// Rx overflow
#define RTL8139_IxR_RXOVW_MASK        ((1U << RTL8139_IxR_RXOVW_BITS)-1)

// Transmit error
#define RTL8139_IxR_TER_MASK          ((1U << RTL8139_IxR_TER_BITS)-1)

// Transmit OK
#define RTL8139_IxR_TOK_MASK          ((1U << RTL8139_IxR_TOK_BITS)-1)

// Rx error
#define RTL8139_IxR_RER_MASK          ((1U << RTL8139_IxR_RER_BITS)-1)

// Rx OK
#define RTL8139_IxR_ROK_MASK          ((1U << RTL8139_IxR_ROK_BITS)-1)

// System error
#define RTL8139_IxR_SERR \
    (RTL8139_IxR_SERR_MASK << RTL8139_IxR_SERR_BIT)

// Timeout
#define RTL8139_IxR_TIMEOUT \
    (RTL8139_IxR_TIMEOUT_MASK << RTL8139_IxR_TIMEOUT_BIT)

// Cable length change
#define RTL8139_IxR_LENCHG \
    (RTL8139_IxR_LENCHG_MASK << RTL8139_IxR_LENCHG_BIT)

// Rx FIFO Overflow
#define RTL8139_IxR_FOVW \
    (RTL8139_IxR_FOVW_MASK << RTL8139_IxR_FOVW_BIT)

// Packet underrun / link change
#define RTL8139_IxR_PUNLC \
    (RTL8139_IxR_PUNLC_MASK << RTL8139_IxR_PUNLC_BIT)

// Rx overflow
#define RTL8139_IxR_RXOVW \
    (RTL8139_IxR_RXOVW_MASK << RTL8139_IxR_RXOVW_BIT)

// Transmit error
#define RTL8139_IxR_TER \
    (RTL8139_IxR_TER_MASK << RTL8139_IxR_TER_BIT)

// Transmit OK
#define RTL8139_IxR_TOK \
    (RTL8139_IxR_TOK_MASK << RTL8139_IxR_TOK_BIT)

// Rx error
#define RTL8139_IxR_RER \
    (RTL8139_IxR_RER_MASK << RTL8139_IxR_RER_BIT)

// Rx OK
#define RTL8139_IxR_ROK \
    (RTL8139_IxR_ROK_MASK << RTL8139_IxR_ROK_BIT)


// System error
#define RTL8139_IxR_SERR_n(n)         ((n) << RTL8139_IxR_SERR_BIT)

// Timeout
#define RTL8139_IxR_TIMEOUT_n(n)      ((n) << RTL8139_IxR_TIMEOUT_BIT)

// Cable length change
#define RTL8139_IxR_LENCHG_n(n)       ((n) << RTL8139_IxR_LENCHG_BIT)

// Rx FIFO Overflow
#define RTL8139_IxR_FOVW_n(n)         ((n) << RTL8139_IxR_FOVW_BIT)

// Packet underrun / link change
#define RTL8139_IxR_PUNLC_n(n)        ((n) << RTL8139_IxR_PUNLC_BIT)

// Rx overflow
#define RTL8139_IxR_RXOVW_n(n)        ((n) << RTL8139_IxR_RXOVW_BIT)

// Transmit error
#define RTL8139_IxR_TER_n(n)          ((n) << RTL8139_IxR_TER_BIT)

// Transmit OK
#define RTL8139_IxR_TOK_n(n)          ((n) << RTL8139_IxR_TOK_BIT)

// Rx error
#define RTL8139_IxR_RER_n(n)          ((n) << RTL8139_IxR_RER_BIT)

// Rx OK
#define RTL8139_IxR_ROK_n(n)          ((n) << RTL8139_IxR_ROK_BIT)


// System error
#define RTL8139_IxR_SERR_GET(n) \
    (((n) >> RTL8139_IxR_SERR_BIT) & RTL8139_IxR_SERR_MASK)

// Timeout
#define RTL8139_IxR_TIMEOUT_GET(n) \
    (((n) >> RTL8139_IxR_TIMEOUT_BIT) & RTL8139_IxR_TIMEOUT_MASK)

// Cable length change
#define RTL8139_IxR_LENCHG_GET(n) \
    (((n) >> RTL8139_IxR_LENCHG_BIT) & RTL8139_IxR_LENCHG_MASK)

// Rx FIFO Overflow
#define RTL8139_IxR_FOVW_GET(n) \
    (((n) >> RTL8139_IxR_FOVW_BIT) & RTL8139_IxR_FOVW_MASK)

// Packet underrun / link change
#define RTL8139_IxR_PUNLC_GET(n) \
    (((n) >> RTL8139_IxR_PUNLC_BIT) & RTL8139_IxR_PUNLC_MASK)

// Rx overflow
#define RTL8139_IxR_RXOVW_GET(n) \
    (((n) >> RTL8139_IxR_RXOVW_BIT) & RTL8139_IxR_RXOVW_MASK)

// Transmit error
#define RTL8139_IxR_TER_GET(n) \
    (((n) >> RTL8139_IxR_TER_BIT) & RTL8139_IxR_TER_MASK)

// Transmit OK
#define RTL8139_IxR_TOK_GET(n) \
    (((n) >> RTL8139_IxR_TOK_BIT) & RTL8139_IxR_TOK_MASK)

// Rx error
#define RTL8139_IxR_RER_GET(n) \
    (((n) >> RTL8139_IxR_RER_BIT) & RTL8139_IxR_RER_MASK)

// Rx OK
#define RTL8139_IxR_ROK_GET(n) \
    (((n) >> RTL8139_IxR_ROK_BIT) & RTL8139_IxR_ROK_MASK)


// System error
#define RTL8139_IxR_SERR_SET(r,n) \
    ((r) = ((r) & ~RTL8139_IxR_SERR) | RTL8139_IxR_SERR_n((n)))

// Timeout
#define RTL8139_IxR_TIMEOUT_SET(r,n) \
    ((r) = ((r) & ~RTL8139_IxR_TIMEOUT) | RTL8139_IxR_TIMEOUT_n((n)))

// Cable length change
#define RTL8139_IxR_LENCHG_SET(r,n) \
    ((r) = ((r) & ~RTL8139_IxR_LENCHG) | RTL8139_IxR_LENCHG_n((n)))

// Rx FIFO Overflow
#define RTL8139_IxR_FOVW_SET(r,n) \
    ((r) = ((r) & ~RTL8139_IxR_FOVW) | RTL8139_IxR_FOVW_n((n)))

// Packet underrun / link change
#define RTL8139_IxR_PUNLC_SET(r,n) \
    ((r) = ((r) & ~RTL8139_IxR_PUNLC) | RTL8139_IxR_PUNLC_n((n)))

// Rx overflow
#define RTL8139_IxR_RXOVW_SET(r,n) \
    ((r) = ((r) & ~RTL8139_IxR_RXOVW) | RTL8139_IxR_RXOVW_n((n)))

// Transmit error
#define RTL8139_IxR_TER_SET(r,n) \
    ((r) = ((r) & ~RTL8139_IxR_TER) | RTL8139_IxR_TER_n((n)))

// Transmit OK
#define RTL8139_IxR_TOK_SET(r,n) \
    ((r) = ((r) & ~RTL8139_IxR_TOK) | RTL8139_IxR_TOK_n((n)))

// Rx error
#define RTL8139_IxR_RER_SET(r,n) \
    ((r) = ((r) & ~RTL8139_IxR_RER) | RTL8139_IxR_RER_n((n)))

// Rx OK
#define RTL8139_IxR_ROK_SET(r,n) \
    ((r) = ((r) & ~RTL8139_IxR_ROK) | RTL8139_IxR_ROK_n((n)))

//
// RTL8139_TCR: Tx Configuration Register (32-bit)
#define RTL8139_TCR 0x40

//
// RTL8139_RCR: Rx Configuration Register (32-bit)
#define RTL8139_RCR 0x44

//
// RTL8139_TCTR: Timer Count Register (32-bit)
#define RTL8139_TCTR 0x48

//
// RTL8139_MPC: Missed Packet Counter (32-bit)
#define RTL8139_MPC 0x4C

//
// RTL8139_9346CR: 93C46 Command Register (8-bit)
#define RTL8139_9346CR 0x50

//
// RTL8139_CONFIG0: Configuration Register 0 (8-bit)
#define RTL8139_CONFIG0 0x51

//
// RTL8139_CONFIG1: Configuration Register 1 (8-bit)
#define RTL8139_CONFIG1 0x52

//
// RTL8139_TIMERINT: Timer Interrupt Register (32-bit)
#define RTL8139_TIMERINT 0x54

//
// RTL8139_MSR: Media Status Register (8-bit)
#define RTL8139_MSR 0x58

//
// RTL8139_CONFIG3: Configuration Register 3 (8-bit)
#define RTL8139_CONFIG3 0x59

//
// RTL8139_CONFIG4: Configuration Register 4 (8-bit)
#define RTL8139_CONFIG4 0x5A

//
// RTL8139_MULINT: Multiple Interrupt Select (16-bit)
#define RTL8139_MULINT 0x5C

//
// RTL8139_RERID: PCI Revision ID (8-bit)
#define RTL8139_RERID 0x5E

//
// RTL8139_TSAD: Tx Status of All Descriptors (16-bit)
#define RTL8139_TSAD 0x60

//
// RTL8139_BMCR: Basic Mode Control Register (16-bit)
#define RTL8139_BMCR 0x62

//
// RTL8139_BMSR: Basic Mode Status Register (16-bit)
#define RTL8139_BMSR 0x64

//
// RTL8139_ANAR: Auto-Negotiation Address Register (16-bit)
#define RTL8139_ANAR 0x66

//
// RTL8139_ANLPAR: Auto-Negotiation Link Partner Register (16-bit)
#define RTL8139_ANLPAR 0x68

//
// RTL8139_ANER: Auto-Negotiation Expansion Register (16-bit)
#define RTL8139_ANER 0x6A

//
// RTL8139_DIS: Disconnect counter (16-bit)
#define RTL8139_DIS 0x6C

//
// RTL8139_FCSC: False Carrier Sense Counter (16-bit)
#define RTL8139_FCSC 0x6E

//
// RTL8139_NWAYTR: N-Way Test Register (16-bit)
#define RTL8139_NWAYTR 0x70

//
// RTL8139_REC: RX_ER Counter (16-bit)
#define RTL8139_REC 0x72

//
// RTL8139_CSCR: CS Configuration Register (16-bit)
#define RTL8139_CSCR 0x74

//
// RTL8139_PHY1_PARM: PHY Parameter 1 (32-bit)
#define RTL8139_PHY1_PARM 0x78

//
// RTL8139_TW_PARM: Twister Parameter (32-bit)
#define RTL8139_TW_PARM 0x7C

//
// RTL8139_PHY2_PARM: PHY Parameter 2 (8-bit)
#define RTL8139_PHY2_PARM 0x80

//
// RTL8139_CRC_n(n): PM CRC register for wakeup frame n (8-bit)
#define RTL8139_CRC_n(n) (0x84+(n))

//
// RTL8139_WAKELO_n(n): PM wakeup frame0 (64-bit)
#define RTL8139_WAKELO_n(n) (0x8C+((n)<<2))

//
// RTL8139_WAKEHI_n(n): PM wakeup frame0 (64-bit)
#define RTL8139_WAKEHI_n(n) (0x90+((n)<<2))

//
// RTL8139_LSBCRC0_n(n): LSB of mask byte of wakeup frame 12 to 75 (8-bit)
#define RTL8139_LSBCRC0_n(n) (0xCC+(n))

//
// Register bit defines


//
// RTL8139_RCR: Rx Configuration Register (32-bit)

#define RTL8139_RCR_ERTH_BIT        24
#define RTL8139_RCR_MULERINT_BIT    17
#define RTL8139_RCR_RER8_BIT        16
#define RTL8139_RCR_RXFTH_BIT       13
#define RTL8139_RCR_RBLEN_BIT       11
#define RTL8139_RCR_MXDMA_BIT       8
#define RTL8139_RCR_WRAP_BIT        7
#define RTL8139_RCR_AER_BIT         5
#define RTL8139_RCR_AR_BIT          4
#define RTL8139_RCR_AB_BIT          3
#define RTL8139_RCR_AM_BIT          2
#define RTL8139_RCR_APM_BIT         1
#define RTL8139_RCR_AAP_BIT         0

#define RTL8139_RCR_ERTH_BITS       4
#define RTL8139_RCR_RXFTH_BITS      3
#define RTL8139_RCR_RBLEN_BITS      2
#define RTL8139_RCR_MXDMA_BITS      3

#define RTL8139_RCR_ERTH_MASK       ((1U<<RTL8139_RCR_ERTH_BITS)-1)
#define RTL8139_RCR_RXFTH_MASK      ((1U<<RTL8139_RCR_RXFTH_BITS)-1)
#define RTL8139_RCR_RBLEN_MASK      ((1U<<RTL8139_RCR_RBLEN_BITS)-1)
#define RTL8139_RCR_MXDMA_MASK      ((1U<<RTL8139_RCR_MXDMA_BITS)-1)

#define RTL8139_RCR_ERTH \
    (RTL8139_RCR_ERTH_MASK<<RTL8139_RCR_ERTH_BIT)

#define RTL8139_RCR_RXFTH \
    (RTL8139_RCR_RXFTH_MASK<<RTL8139_RCR_RXFTH_BIT)

#define RTL8139_RCR_RBLEN \
    (RTL8139_RCR_RBLEN_MASK<<RTL8139_RCR_RBLEN_BIT)

#define RTL8139_RCR_MXDMA \
    (RTL8139_RCR_MXDMA_MASK<<RTL8139_RCR_MXDMA_BIT)

// Multiple early interrupt select
// 0 = Invoke early interrupt for unknown
//      protocols using RCR<ERTH[3:0]>
// 1 = Invoke early interrupt for known
//      protocols using MULINT<MISR[11:0]>
#define RTL8139_RCR_MULERINT        (1U<<RTL8139_RCR_MULERINT_BIT)

// 0 = Receive error packets larger than 8 bytes
// 1 = Receive error packets larger than 64 bytes (default)
#define RTL8139_RCR_RER8            (1U<<RTL8139_RCR_RER8_BIT)

// 0 = Wrap at end of buffer,
// 1 = overflow up to 1500 bytes past end
#define RTL8139_RCR_WRAP            (1U<<RTL8139_RCR_WRAP_BIT)

// Accept error packets
#define RTL8139_RCR_AER             (1U<<RTL8139_RCR_AER_BIT)

// Accept runt packets
#define RTL8139_RCR_AR              (1U<<RTL8139_RCR_AR_BIT)

// Accept broadcast packets
#define RTL8139_RCR_AB              (1U<<RTL8139_RCR_AB_BIT)

// Accept multicast packets
#define RTL8139_RCR_AM              (1U<<RTL8139_RCR_AM_BIT)

// Accept physical match packets
#define RTL8139_RCR_APM             (1U<<RTL8139_RCR_APM_BIT)

// Accept all packets
#define RTL8139_RCR_AAP             (1U<<RTL8139_RCR_AAP_BIT)

// Early Rx threshold (n/16th, or, 0=none)
#define RTL8139_RCR_ERTH_n(n)   ((n)<<RTL8139_RCR_ERTH_BIT)

// Rx FIFO threshold (1U<<(n+4), or 7=none)
#define RTL8139_RCR_RXFTH_n(n)  ((n)<<RTL8139_RCR_RXFTH_BIT)

// Rx Buffer Length (0=8K+16, 1=16K+16, 2=32K+16, 3=64K+16)
#define RTL8139_RCR_RBLEN_n(n)  ((n)<<RTL8139_RCR_RBLEN_BIT)

// Max DMA burst per Rx DMA burst (1U<<(n+4), or 7=unlimited)
#define RTL8139_RCR_MXDMA_n(n)  ((n)<<RTL8139_RCR_MXDMA_BIT)

//
// RTL8139_TCR: Tx Configuration Register (32-bit)

#define RTL8139_TCR_HWVERID_A_BIT   26
#define RTL8139_TCR_IFG_BIT         24
#define RTL8139_TCR_HWVERID_B_BIT   22
#define RTL8139_TCR_LBK_BIT         17
#define RTL8139_TCR_CRC_BIT         16
#define RTL8139_TCR_MXDMA_BIT       8
#define RTL8139_TCR_TXRR_BIT        4
#define RTL8139_TCR_CLRABT_BIT      0

#define RTL8139_TCR_HWVERID_A_BITS  5
#define RTL8139_TCR_IFG_BITS        2
#define RTL8139_TCR_HWVERID_B_BITS  2
#define RTL8139_TCR_LBK_BITS        2
#define RTL8139_TCR_MXDMA_BITS      3
#define RTL8139_TCR_TXRR_BITS       4

#define RTL8139_TCR_HWVERID_A_MASK  ((1U<<RTL8139_TCR_HWVERID_A_BITS)-1)
#define RTL8139_TCR_IFG_MASK        ((1U<<RTL8139_TCR_IFG_BITS)-1)
#define RTL8139_TCR_HWVERID_B_MASK  ((1U<<RTL8139_TCR_HWVERID_B_BITS)-1)
#define RTL8139_TCR_LBK_MASK        ((1U<<RTL8139_TCR_LBK_BITS)-1)
#define RTL8139_TCR_MXDMA_MASK      ((1U<<RTL8139_TCR_MXDMA_BITS)-1)
#define RTL8139_TCR_TXRR_MASK       ((1U<<RTL8139_TCR_TXRR_BITS)-1)

#define RTL8139_TCR_HWVERID_A \
    (RTL8139_TCR_HWVERID_A_MASK<<RTL8139_TCR_HWVERID_A_BIT)

#define RTL8139_TCR_IFG \
    (RTL8139_TCR_IFG_MASK<<RTL8139_TCR_IFG_BIT)

#define RTL8139_TCR_HWVERID_B \
    (RTL8139_TCR_HWVERID_B_MASK<<RTL8139_TCR_HWVERID_B_BIT)

#define RTL8139_TCR_LBK \
    (RTL8139_TCR_LBK_MASK<<RTL8139_TCR_LBK_BIT)

#define RTL8139_TCR_MXDMA \
    (RTL8139_TCR_MXDMA_MASK<<RTL8139_TCR_MXDMA_BIT)
#define RTL8139_TCR_TXRR \
    (RTL8139_TCR_TXRR_MASK<<RTL8139_TCR_TXRR_BIT)

// Append CRC
#define RTL8139_TCR_CRC             (1U<<RTL8139_TCR_CRC_BIT)

// Clear abort (only write 1 if in tx abort state)
#define RTL8139_TCR_CLRABT          (1U<<RTL8139_TCR_CLRABT_BIT)

// Hardware version ID A
#define RTL8139_TCR_HWVERID_A_n(n)  ((n)<<RTL8139_TCR_HWVERID_A_BIT)

// Interframe gap
#define RTL8139_TCR_IFG_n(n)        ((n)<<RTL8139_TCR_IFG_BIT)

// Hardware version ID B
#define RTL8139_TCR_HWVERID_B_n(n)  ((n)<<RTL8139_TCR_HWVERID_B_BIT)

// Loopback test
#define RTL8139_TCR_LBK_n(n)        ((n)<<RTL8139_TCR_LBK_BIT)

// Max tx DMA burst (1U<<(n+4))
#define RTL8139_TCR_MXDMA_n(n)      ((n)<<RTL8139_TCR_MXDMA_BIT)

// Tx retry count (16+n*16)
#define RTL8139_TCR_TXRR_n(n)       ((n)<<RTL8139_TCR_TXRR_BIT)

// RTL8139_TSAD: Tx Status of All Descriptors (16-bit)

#define RTL8139_TSAD_OWN_BIT        0
#define RTL8139_TSAD_TABT_BIT       4
#define RTL8139_TSAD_TUN_BIT        8
#define RTL8139_TSAD_TOK_BIT        12

#define RTL8139_TSAD_OWN_n(n)       (1U<<((n)+RTL8139_TSAD_OWN_BIT))
#define RTL8139_TSAD_TABT_n(n)      (1U<<((n)+RTL8139_TSAD_TABT_BIT))
#define RTL8139_TSAD_TUN_n(n)       (1U<<((n)+RTL8139_TSAD_TUN_BIT))
#define RTL8139_TSAD_TOK_n(n)       (1U<<((n)+RTL8139_TSAD_TOK_BIT))

#define RTL8139_RX_HDR_MAR_BIT      15
#define RTL8139_RX_HDR_PAM_BIT      14
#define RTL8139_RX_HDR_BAR_BIT      13
#define RTL8139_RX_HDR_ISE_BIT      5
#define RTL8139_RX_HDR_RUNT_BIT     4
#define RTL8139_RX_HDR_LONG_BIT     3
#define RTL8139_RX_HDR_CRC_BIT      2
#define RTL8139_RX_HDR_FAE_BIT      1
#define RTL8139_RX_HDR_ROK_BIT      0

// Multicast address received
#define RTL8139_RX_HDR_MAR          (1U<<RTL8139_RX_HDR_MAR_BIT)

// Physical address matched
#define RTL8139_RX_HDR_PAM          (1U<<RTL8139_RX_HDR_PAM_BIT)

// Broadcast address received
#define RTL8139_RX_HDR_BAR          (1U<<RTL8139_RX_HDR_BAR_BIT)

// Invalid symbol error
#define RTL8139_RX_HDR_ISE          (1U<<RTL8139_RX_HDR_ISE_BIT)

// Runt packet received
#define RTL8139_RX_HDR_RUNT         (1U<<RTL8139_RX_HDR_RUNT_BIT)

// Long packet
#define RTL8139_RX_HDR_LONG         (1U<<RTL8139_RX_HDR_LONG_BIT)

// CRC error
#define RTL8139_RX_HDR_CRC          (1U<<RTL8139_RX_HDR_CRC_BIT)

// Frame alignment error
#define RTL8139_RX_HDR_FAE          (1U<<RTL8139_RX_HDR_FAE_BIT)

// Receive OK
#define RTL8139_RX_HDR_ROK          (1U<<RTL8139_RX_HDR_ROK_BIT)

#endif