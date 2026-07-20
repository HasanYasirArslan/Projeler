#include "common.h"
#include <pthread.h>

// Global değişkenler
pcap_t *handle = NULL;
uint32_t server_ip = 0;
int error_mode = 0;
int running = 1;

// Hata modları
#define MODE_NORMAL       0
#define MODE_HOST         1
#define MODE_NETWORK      2
#define MODE_TTL          3
#define MODE_PROTOCOL     4
#define MODE_PORT         5
#define MODE_FRAG         6
#define MODE_PROHIBIT     7
#define MODE_PARAM        8

// Mod isimlerini al
const char* get_mode_name(int mode) {
    switch (mode) {
        case MODE_NORMAL:     return "Normal (Echo Reply)";
        case MODE_HOST:       return "Host Unreachable";
        case MODE_NETWORK:    return "Network Unreachable";
        case MODE_TTL:        return "TTL Exceeded";
        case MODE_PROTOCOL:   return "Protocol Unreachable";
        case MODE_PORT:       return "Port Unreachable";
        case MODE_FRAG:       return "Fragmentation Needed";
        case MODE_PROHIBIT:   return "Communication Prohibited";
        case MODE_PARAM:      return "Parameter Problem (Checksum Error)";
        default:              return "Unknown";
    }
}

// Paket işleyici
void packet_handler(u_char *user, const struct pcap_pkthdr *header, const u_char *packet) {
    (void)user;
    (void)header;
    
    struct eth_header *eth = (struct eth_header *)packet;
    if (ntohs(eth->eth_type) != 0x0800) return;
    
    struct ip_header *ip = (struct ip_header *)(packet + ETH_HLEN);
    if (ip->protocol != 1) return;
    if (ip->dest_ip != server_ip) return;
    
    int ip_hlen = (ip->version_ihl & 0x0F) * 4;
    struct icmp_header *icmp = (struct icmp_header *)(packet + ETH_HLEN + ip_hlen);
    
    if (icmp->type != ICMP_ECHO_REQUEST) return;
    
    printf("\n[ISTEK] ");
    print_ip(ip->src_ip);
    printf(" -> seq=%d\n", ntohs(icmp->sequence));
    
    // Checksum kontrolü
    uint16_t received_checksum = icmp->checksum;
    icmp->checksum = 0;
    uint16_t calculated_checksum = calculate_checksum((uint16_t *)icmp, 8);
    icmp->checksum = received_checksum;
    
    int checksum_error = 0;
    if (received_checksum != calculated_checksum) {
        printf("[UYARI] Bozuk checksum tespit edildi!\n");
        checksum_error = 1;
    }
    
    // Yanıt oluştur
    uint8_t reply_packet[128];
    memset(reply_packet, 0, sizeof(reply_packet));
    
    struct eth_header *reply_eth = (struct eth_header *)reply_packet;
    memcpy(reply_eth->dest_mac, eth->src_mac, 6);
    memcpy(reply_eth->src_mac, eth->dest_mac, 6);
    reply_eth->eth_type = htons(0x0800);
    
    struct ip_header *reply_ip = (struct ip_header *)(reply_packet + ETH_HLEN);
    reply_ip->version_ihl = 0x45;
    reply_ip->total_length = htons(20 + 8);
    reply_ip->identification = ip->identification;
    reply_ip->ttl = 64;
    reply_ip->protocol = 1;
    reply_ip->src_ip = ip->dest_ip;
    reply_ip->dest_ip = ip->src_ip;
    
    struct icmp_header *reply_icmp = (struct icmp_header *)(reply_packet + ETH_HLEN + 20);
    
    int current_mode = checksum_error ? MODE_PARAM : error_mode;
    
    switch (current_mode) {
        case MODE_HOST:
            reply_icmp->type = ICMP_DEST_UNREACH;
            reply_icmp->code = ICMP_HOST_UNREACH;
            break;
        case MODE_NETWORK:
            reply_icmp->type = ICMP_DEST_UNREACH;
            reply_icmp->code = ICMP_NET_UNREACH;
            break;
        case MODE_TTL:
            reply_icmp->type = ICMP_TIME_EXCEEDED;
            reply_icmp->code = ICMP_EXC_TTL;
            break;
        case MODE_PROTOCOL:
            reply_icmp->type = ICMP_DEST_UNREACH;
            reply_icmp->code = ICMP_PROT_UNREACH;
            break;
        case MODE_PORT:
            reply_icmp->type = ICMP_DEST_UNREACH;
            reply_icmp->code = ICMP_PORT_UNREACH;
            break;
        case MODE_FRAG:
            reply_icmp->type = ICMP_DEST_UNREACH;
            reply_icmp->code = ICMP_FRAG_NEEDED;
            break;
        case MODE_PROHIBIT:
            reply_icmp->type = ICMP_DEST_UNREACH;
            reply_icmp->code = ICMP_COMM_PROHIB;
            break;
        case MODE_PARAM:
            reply_icmp->type = ICMP_PARAM_PROBLEM;
            reply_icmp->code = ICMP_PARAM_PTR;
            break;
        default:
            reply_icmp->type = ICMP_ECHO_REPLY;
            reply_icmp->code = 0;
            reply_icmp->id = icmp->id;
            reply_icmp->sequence = icmp->sequence;
            break;
    }
    
    reply_icmp->checksum = 0;
    reply_icmp->checksum = calculate_checksum((uint16_t *)reply_icmp, 8);
    reply_ip->checksum = calculate_checksum((uint16_t *)reply_ip, 20);
    
    if (pcap_sendpacket(handle, reply_packet, ETH_HLEN + 20 + 8) == 0) {
        printf("[YANIT] %s\n", get_mode_name(current_mode));
    }
    
    printf("\nMod [%d]: %s > ", error_mode, get_mode_name(error_mode));
    fflush(stdout);
}

// Paket yakalama thread'i
void* capture_thread(void* arg) {
    (void)arg;
    while (running) {
        struct pcap_pkthdr *header;
        const u_char *packet;
        int res = pcap_next_ex(handle, &header, &packet);
        if (res > 0) {
            packet_handler(NULL, header, packet);
        }
        usleep(10000);
    }
    return NULL;
}

void print_menu() {
    printf("\n");
    printf("╔═══════════════════════════════════════════════════════════╗\n");
    printf("║              ICMP SERVER - HATA MODLARI                   ║\n");
    printf("╠═══════════════════════════════════════════════════════════╣\n");
    printf("║  0  - Echo Reply                    (Type 0,  Code 0)     ║\n");
    printf("║  1  - Host Unreachable              (Type 3,  Code 1)     ║\n");
    printf("║  2  - Network Unreachable           (Type 3,  Code 0)     ║\n");
    printf("║  3  - TTL Exceeded                  (Type 11, Code 0)     ║\n");
    printf("║  4  - Protocol Unreachable          (Type 3,  Code 2)     ║\n");
    printf("║  5  - Port Unreachable              (Type 3,  Code 3)     ║\n");
    printf("║  6  - Fragmentation Needed          (Type 3,  Code 4)     ║\n");
    printf("║  7  - Communication Prohibited      (Type 3,  Code 13)    ║\n");
    printf("╠═══════════════════════════════════════════════════════════╣\n");
    printf("║  m  - Menu goster    |    q  - Cikis                      ║\n");
    printf("╚═══════════════════════════════════════════════════════════╝\n");
    printf("\n[NOT] Bozuk checksum gönderilirse otomatik Parameter Problem döner.\n");
}

int main(int argc, char **argv) {
    char errbuf[PCAP_ERRBUF_SIZE];
    char *dev;
    struct bpf_program fp;
    char filter[] = "icmp";
    bpf_u_int32 net, mask;
    pthread_t tid;
    
    if (argc < 2) {
        printf("Kullanim: %s <server-ip>\n", argv[0]);
        return 1;
    }
    
    struct in_addr addr;
    if (inet_aton(argv[1], &addr) == 0) {
        fprintf(stderr, "Hata: Gecersiz IP adresi\n");
        return 1;
    }
    server_ip = addr.s_addr;
    
    dev = pcap_lookupdev(errbuf);
    if (dev == NULL) {
        fprintf(stderr, "Arayuz bulunamadi: %s\n", errbuf);
        return 1;
    }
    
    printf("=== ICMP Server ===\n");
    printf("Arayuz: %s\n", dev);
    printf("Server IP: %s\n", argv[1]);
    
    if (pcap_lookupnet(dev, &net, &mask, errbuf) == -1) {
        net = 0;
        mask = 0;
    }
    
    handle = pcap_open_live(dev, BUFSIZ, 1, 1000, errbuf);
    if (handle == NULL) {
        fprintf(stderr, "Arayuz acilamadi: %s\n", errbuf);
        return 1;
    }
    
    if (pcap_compile(handle, &fp, filter, 0, net) == -1 ||
        pcap_setfilter(handle, &fp) == -1) {
        fprintf(stderr, "Filtre hatasi\n");
        return 1;
    }
    
    pcap_setnonblock(handle, 1, errbuf);
    
    // Paket yakalama thread'ini başlat
    pthread_create(&tid, NULL, capture_thread, NULL);
    
    print_menu();
    
    char input[32];
    while (running) {
        printf("\nMod [%d]: %s > ", error_mode, get_mode_name(error_mode));
        fflush(stdout);
        
        if (fgets(input, sizeof(input), stdin) == NULL) break;
        
        input[strcspn(input, "\n")] = 0;
        
        if (strcmp(input, "q") == 0 || strcmp(input, "Q") == 0) {
            running = 0;
            break;
        }
        
        if (strcmp(input, "m") == 0 || strcmp(input, "M") == 0) {
            print_menu();
            continue;
        }
        
        int new_mode = atoi(input);
        if (new_mode >= 0 && new_mode <= 7) {
            error_mode = new_mode;
            printf("Mod degistirildi: %s\n", get_mode_name(error_mode));
        } else if (strlen(input) > 0) {
            printf("Gecersiz secim. 'm' ile menuyu gorebilirsiniz.\n");
        }
    }
    
    pthread_join(tid, NULL);
    pcap_freecode(&fp);
    pcap_close(handle);
    
    printf("\nServer kapatildi.\n");
    return 0;
}