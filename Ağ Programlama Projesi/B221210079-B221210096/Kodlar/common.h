#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <arpa/inet.h>
#include <pcap.h>
#include <time.h>
#include <unistd.h>

// Ethernet başlık boyutu
#define ETH_HLEN 14

// ICMP Tipleri
#define ICMP_ECHO_REPLY      0   // Echo Reply
#define ICMP_DEST_UNREACH    3   // Destination Unreachable
#define ICMP_ECHO_REQUEST    8   // Echo Request
#define ICMP_TIME_EXCEEDED   11  // Time Exceeded
#define ICMP_PARAM_PROBLEM   12  // Parameter Problem

// ICMP Kodları - Destination Unreachable (Type 3)
#define ICMP_NET_UNREACH     0   // Network Unreachable
#define ICMP_HOST_UNREACH    1   // Host Unreachable
#define ICMP_PROT_UNREACH    2   // Protocol Unreachable
#define ICMP_PORT_UNREACH    3   // Port Unreachable
#define ICMP_FRAG_NEEDED     4   // Fragmentation Needed and DF Set
#define ICMP_SR_FAILED       5   // Source Route Failed
#define ICMP_NET_UNKNOWN     6   // Destination Network Unknown
#define ICMP_HOST_UNKNOWN    7   // Destination Host Unknown
#define ICMP_HOST_ISOLATED   8   // Source Host Isolated
#define ICMP_NET_PROHIB      9   // Network Administratively Prohibited
#define ICMP_HOST_PROHIB     10  // Host Administratively Prohibited
#define ICMP_NET_UNR_TOS     11  // Network Unreachable for TOS
#define ICMP_HOST_UNR_TOS    12  // Host Unreachable for TOS
#define ICMP_COMM_PROHIB     13  // Communication Administratively Prohibited
#define ICMP_PREC_VIOLATION  14  // Host Precedence Violation
#define ICMP_PREC_CUTOFF     15  // Precedence Cutoff in Effect



// ICMP Kodları - Time Exceeded (Type 11)
#define ICMP_EXC_TTL         0   // TTL Exceeded in Transit
#define ICMP_EXC_FRAGTIME    1   // Fragment Reassembly Time Exceeded

// ICMP Kodları - Parameter Problem (Type 12)
#define ICMP_PARAM_PTR       0   // Pointer indicates the error
#define ICMP_PARAM_MISSING   1   // Missing a required option
#define ICMP_PARAM_LENGTH    2   // Bad length

// Ethernet Başlığı
struct eth_header {
    uint8_t dest_mac[6];
    uint8_t src_mac[6];
    uint16_t eth_type;
} __attribute__((packed));

// IP Başlığı
struct ip_header {
    uint8_t  version_ihl;
    uint8_t  tos;
    uint16_t total_length;
    uint16_t identification;
    uint16_t flags_offset;
    uint8_t  ttl;
    uint8_t  protocol;
    uint16_t checksum;
    uint32_t src_ip;
    uint32_t dest_ip;
} __attribute__((packed));

// ICMP Başlığı
struct icmp_header {
    uint8_t  type;
    uint8_t  code;
    uint16_t checksum;
    uint16_t id;
    uint16_t sequence;
} __attribute__((packed));

// Checksum hesapla
uint16_t calculate_checksum(uint16_t *data, int len) {
    uint32_t sum = 0;
    while (len > 1) {
        sum += *data++;
        len -= 2;
    }
    if (len == 1) {
        sum += *(uint8_t *)data;
    }
    sum = (sum >> 16) + (sum & 0xFFFF);
    sum += (sum >> 16);
    return (uint16_t)(~sum);
}

// IP adresini yazdır
void print_ip(uint32_t ip) {
    struct in_addr addr;
    addr.s_addr = ip;
    printf("%s", inet_ntoa(addr));
}

#endif
