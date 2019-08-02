#include <cstring>
#include <iostream>
#include <net/if.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <net/if_arp.h>

#include "utils.h"
#include "ArpPacket.h"

using namespace std;
using namespace network;

HwAddr get_dev_mac(const char *dev) {
    ifreq ifr{};
    int fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_IP);

    std::strncpy(ifr.ifr_name, dev, IF_NAMESIZE-1);

    if (ioctl(fd, SIOCGIFHWADDR, &ifr) != 0) {
        close(fd);
        return HwAddr();
    }

    byte mac[6];
    memcpy(mac, ifr.ifr_addr.sa_data, HwAddr::size);

    close(fd);
    return HwAddr(mac);
}

HwAddr get_target_mac(pcap* desc, const HwAddr& smac, const IpAddr& sip, const IpAddr& tip) {
    ArpPacket arp(ARPOP_REQUEST,
                  smac, sip,
                  HwAddr(), tip);
    arp.ether.dst = HwAddr("FF:FF:FF:FF:FF:FF");
    const byte *packet = arp.to_bytes();
    if (pcap_sendpacket(desc, packet, ArpPacket::size) != 0) {
        cerr << "Error sending the packet : " << pcap_geterr(desc) << endl;
        exit(-1);
    }

    auto *filter = new bpf_program;
    if (pcap_compile(desc, filter, "arp", 1, 0) == -1 and pcap_setfilter(desc, filter) == -1) {
        cerr << "error: "  << pcap_geterr(desc) << endl;
        exit(-1);
    }

    pcap_pkthdr *header;
    int res = 0;
    while ((res = pcap_next_ex(desc, &header, &packet)) >= 0) {
        if (res == 0) continue;
        arp = ArpPacket(packet);
        if (arp.arp.opcode == ARPOP_REPLY and arp.arp.sender_ip == tip) {
            return arp.arp.sender_mac;
        }
    }
    delete(filter);
    return HwAddr("FF:FF:FF:FF:FF:FF");
}