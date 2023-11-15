#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

// Example structure representing a network packet
struct Packet {
    uint32_t sourceIP;
    uint32_t destIP;
    uint16_t sourcePort;
    uint16_t destPort;
    // Other packet-related information
};

// Function to filter packets based on predefined rules
bool firewallFilter(const struct Packet *packet) {
    // Check packet against firewall rules
    // Implement firewall rules here
    if (packet->sourceIP == 0x0A0A0A0A && packet->destPort == 80) {
        // Example rule: Block packets from source IP 10.10.10.10 to destination port 80 (HTTP)
        printf("Packet blocked by firewall!\n");
        return false; // Block packet
    }
    return true; // Allow packet
}

int main() {
    // Simulated incoming packets
    struct Packet incomingPacket1 = {0x0A0A0A0A, 0x0B0B0B0B, 80, 8080};
    struct Packet incomingPacket2 = {0x0B0B0B0B, 0x0A0A0A0A, 443, 80};

    // Check packets against firewall rules
    bool allowPacket1 = firewallFilter(&incomingPacket1);
    bool allowPacket2 = firewallFilter(&incomingPacket2);

    if (allowPacket1) {
        printf("Packet 1 allowed by firewall!\n");
    } else {
        printf("Packet 1 blocked by firewall!\n");
    }

    if (allowPacket2) {
        printf("Packet 2 allowed by firewall!\n");
    } else {
        printf("Packet 2 blocked by firewall!\n");
    }

    return 0;
}
