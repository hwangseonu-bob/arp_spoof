#include "../../includes/network/utils.h"
#include "../../includes/network/packet/ArpPacket.h"

#include <sys/ioctl.h>
#include <sys/socket.h>
#include <net/if.h>
#include <netinet/ip.h>
#include <cstring>
#include <unistd.h>
#include <iostream>

namespace network {
    pcap *open_dev(const char *dev) {
        pcap *desc;
        char errbuf[PCAP_ERRBUF_SIZE] = {0,};
        if ((desc = pcap_open_live(dev, 2048, 1, 1024, errbuf)) == nullptr) {
            throw std::runtime_error("error: " + std::string(errbuf));
        }
        return desc;
    }

    HwAddr get_dev_mac(const char *dev) {
        ifreq ifr{};
        int fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_IP);

        strncpy(ifr.ifr_name, dev, IF_NAMESIZE - 1);

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

        ArpPacket arp(ARPOP_REQUEST, smac, sip, HwAddr(), tip);
        arp.eth.dst = HwAddr("FF:FF:FF:FF:FF:FF");

        int cnt = 3;
        while (cnt--) {
            if (pcap_sendpacket(desc, arp.to_bytes().data(), ArpPacket::size) != 0) {
                std::cerr << "Error sending the packet : " << pcap_geterr(desc) << std::endl;
                exit(-1);
            }

            const byte *packet = new byte[8192];
            pcap_pkthdr *header;
            int res = 0, c = 100;
            while ((res = pcap_next_ex(desc, &header, &packet)) >= 0 and c-- > 0) {
                if (res == 0) continue;
                ArpPacket pk(packet);

                if (pk.eth.type == ETHERTYPE_ARP and
                    pk.arp.opcode == ARPOP_REPLY and pk.arp.sender_ip == tip and pk.arp.sender_mac != smac) {
                    delete[](packet);
                    return pk.arp.sender_mac;
                }
            }
            delete[](packet);
        }
        throw std::runtime_error(tip.to_string() + " is not in lan");
    }
}