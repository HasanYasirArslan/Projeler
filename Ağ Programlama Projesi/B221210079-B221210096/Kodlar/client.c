#include "common.h"
#include <sys/time.h>
#include <signal.h>

// Global değişkenler
pcap_t *handle = NULL;
uint16_t ping_id = 0;
uint16_t ping_seq = 0;
struct timeval send_time;
int reply_received = 0;  // 1=Echo Reply, 2=Hata mesajı
int bad_checksum = 0;
int running = 1;

void signal_handler(int sig) {
    (void)sig;
    running = 0;
}

// Paket işleyici
void packet_handler(u_char *user, const struct pcap_pkthdr *header, const u_char *packet) {
    (void)user;
    (void)header;
    
    struct timeval recv_time;
    gettimeofday(&recv_time, NULL);
    
    struct eth_header *eth = (struct eth_header *)packet;
    if (ntohs(eth->eth_type) != 0x0800) return;
    
    struct ip_header *ip = (struct ip_header *)(packet + ETH_HLEN);
    if (ip->protocol != 1) return;
    
    int ip_hlen = (ip->version_ihl & 0x0F) * 4;
    struct icmp_header *icmp = (struct icmp_header *)(packet + ETH_HLEN + ip_hlen);
    
    // Type 0: Echo Reply - BAŞARILI
    if (icmp->type == ICMP_ECHO_REPLY) {
        if (ntohs(icmp->id) == ping_id && ntohs(icmp->sequence) == ping_seq) {
            long time_ms = (recv_time.tv_sec - send_time.tv_sec) * 1000 +
                          (recv_time.tv_usec - send_time.tv_usec) / 1000;
            printf("Yanit: ");
            print_ip(ip->src_ip);
            printf(" icmp_seq=%d ttl=%d sure=%ldms\n", ntohs(icmp->sequence), ip->ttl, time_ms);
            reply_received = 1;  // Başarılı yanıt
        }
        return;
    }
    
    // Type 3: Destination Unreachable - HATA
    if (icmp->type == ICMP_DEST_UNREACH) {
        printf("Hata: ");
        print_ip(ip->src_ip);
        printf(" - ");
        switch (icmp->code) {
            case ICMP_NET_UNREACH: printf("Destination Network Unreachable\n"); break;
            case ICMP_HOST_UNREACH: printf("Destination Host Unreachable\n"); break;
            case ICMP_PROT_UNREACH: printf("Destination Protocol Unreachable\n"); break;
            case ICMP_PORT_UNREACH: printf("Destination Port Unreachable\n"); break;
            case ICMP_FRAG_NEEDED: printf("Fragmentation Needed and DF Set\n"); break;
            case ICMP_COMM_PROHIB: printf("Communication Administratively Prohibited\n"); break;
            default: printf("Destination Unreachable (code=%d)\n", icmp->code);
        }
        reply_received = 2;  // Hata yanıtı
        return;
    }
    
    // Type 11: Time Exceeded - HATA
    if (icmp->type == ICMP_TIME_EXCEEDED) {
        printf("Hata: ");
        print_ip(ip->src_ip);
        printf(" - ");
        if (icmp->code == ICMP_EXC_TTL)
            printf("TTL Exceeded in Transit\n");
        else
            printf("Fragment Reassembly Time Exceeded\n");
        reply_received = 2;
        return;
    }
    
    // Type 12: Parameter Problem - HATA
    if (icmp->type == ICMP_PARAM_PROBLEM) {
        printf("Hata: ");
        print_ip(ip->src_ip);
        printf(" - Parameter Problem ");
        switch (icmp->code) {
            case ICMP_PARAM_PTR: printf("(Pointer Error)\n"); break;
            case ICMP_PARAM_MISSING: printf("(Missing Option)\n"); break;
            case ICMP_PARAM_LENGTH: printf("(Bad Length)\n"); break;
            default: printf("(code=%d)\n", icmp->code);
        }
        reply_received = 2;
        return;
    }
}

void print_usage(char *prog) {
    printf("Kullanim: %s <hedef-ip> [--bad-checksum]\n", prog);
}

int main(int argc, char **argv) {
    char errbuf[PCAP_ERRBUF_SIZE];
    char *dev;
    struct bpf_program fp;
    char filter[] = "icmp";
    bpf_u_int32 net, mask;
    uint8_t packet[128];
    struct in_addr dest_addr;
    int packet_count = 4;
    int sent = 0, received = 0, errors = 0;
    
    signal(SIGINT, signal_handler);
    
    if (argc < 2) {
        print_usage(argv[0]);
        return 1;
    }
    
    if (inet_aton(argv[1], &dest_addr) == 0) {
        fprintf(stderr, "Hata: Gecersiz IP adresi\n");
        return 1;
    }
    
    for (int i = 2; i < argc; i++) {
        if (strcmp(argv[i], "--bad-checksum") == 0) {
            bad_checksum = 1;
        }
    }
    
    dev = pcap_lookupdev(errbuf);
    if (dev == NULL) {
        fprintf(stderr, "Arayuz bulunamadi: %s\n", errbuf);
        return 1;
    }
    
    printf("PING %s (%s)\n", argv[1], dev);
    if (bad_checksum) printf("Bozuk checksum modu aktif\n");
    
    if (pcap_lookupnet(dev, &net, &mask, errbuf) == -1) {
        net = 0;
        mask = 0;
    }
    
    handle = pcap_open_live(dev, BUFSIZ, 1, 1000, errbuf);
    if (handle == NULL) {
        fprintf(stderr, "Arayuz acilamadi: %s\n", errbuf);
        return 1;
    }
    
    if (pcap_compile(handle, &fp, filter, 0, net) == -1) {
        fprintf(stderr, "Filtre derlenemedi: %s\n", pcap_geterr(handle));
        return 1;
    }
    
    if (pcap_setfilter(handle, &fp) == -1) {
        fprintf(stderr, "Filtre uygulanamadi: %s\n", pcap_geterr(handle));
        return 1;
    }
    
    pcap_setnonblock(handle, 1, errbuf);
    
    struct in_addr src_addr;
    src_addr.s_addr = net;
    
    ping_id = getpid() & 0xFFFF;
    
    uint8_t src_mac[6] = {0};
    char mac_path[256];
    snprintf(mac_path, sizeof(mac_path), "/sys/class/net/%s/address", dev);
    FILE *mac_file = fopen(mac_path, "r");
    if (mac_file) {
        int m[6];
        if (fscanf(mac_file, "%x:%x:%x:%x:%x:%x", &m[0], &m[1], &m[2], &m[3], &m[4], &m[5]) == 6) {
            for (int i = 0; i < 6; i++) src_mac[i] = (uint8_t)m[i];
        }
        fclose(mac_file);
    }
    
    for (ping_seq = 1; ping_seq <= packet_count && running; ping_seq++) {
        reply_received = 0;
        memset(packet, 0, sizeof(packet));
        
        struct eth_header *eth = (struct eth_header *)packet;
        memset(eth->dest_mac, 0xFF, 6);
        memcpy(eth->src_mac, src_mac, 6);
        eth->eth_type = htons(0x0800);
        
        struct ip_header *ip = (struct ip_header *)(packet + ETH_HLEN);
        ip->version_ihl = 0x45;
        ip->total_length = htons(20 + 8);
        ip->identification = htons(ping_id + ping_seq);
        ip->ttl = 64;
        ip->protocol = 1;
        ip->src_ip = src_addr.s_addr;
        ip->dest_ip = dest_addr.s_addr;
        ip->checksum = calculate_checksum((uint16_t *)ip, 20);
        
        struct icmp_header *icmp = (struct icmp_header *)(packet + ETH_HLEN + 20);
        icmp->type = ICMP_ECHO_REQUEST;
        icmp->id = htons(ping_id);
        icmp->sequence = htons(ping_seq);
        
        if (bad_checksum) {
            icmp->checksum = 0xDEAD;
        } else {
            icmp->checksum = calculate_checksum((uint16_t *)icmp, 8);
        }
        
        gettimeofday(&send_time, NULL);
        
        if (pcap_sendpacket(handle, packet, ETH_HLEN + 20 + 8) != 0) {
            fprintf(stderr, "Gonderme hatasi\n");
            continue;
        }
        sent++;
        
        // Yanıt gelene kadar bekle
        while (!reply_received && running) {
            struct pcap_pkthdr *hdr;
            const u_char *pkt_data;
            int res = pcap_next_ex(handle, &hdr, &pkt_data);
            if (res > 0) packet_handler(NULL, hdr, pkt_data);
            else if (res == 0) usleep(10000);
        }
        
        // İstatistikleri güncelle
        if (reply_received == 1) {
            received++;  // Sadece Echo Reply
        } else if (reply_received == 2) {
            errors++;    // Hata mesajları
        }
        
        if (ping_seq < packet_count && running) sleep(1);
    }
    
    // İstatistikler
    printf("\n--- %s istatistikleri ---\n", argv[1]);
    int loss = sent > 0 ? ((sent - received) * 100 / sent) : 0;
    if (errors > 0) {
        printf("%d gonderildi, %d alindi, +%d hata, %%%d kayip\n", sent, received, errors, loss);
    } else {
        printf("%d gonderildi, %d alindi, %%%d kayip\n", sent, received, loss);
    }
    
    pcap_freecode(&fp);
    pcap_close(handle);
    return received > 0 ? 0 : 1;
}
