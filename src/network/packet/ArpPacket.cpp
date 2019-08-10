#include <netinet/if_ether.h>

#include "network/packet/ArpPacket.h"

namespace network {
    bytes ArpPacket::to_bytes() const {
        bytes result;
        bytes eth = this->ether.to_bytes();
        bytes arp = this->arp.to_bytes();

        result.insert(result.end(), eth.begin(), eth.end());
        result.insert(result.end(), arp.begin(), arp.end());
        return result;
    }

    ArpPacket::ArpPacket(const byte *bytes) {
        ether = Ether(bytes);
        arp = Arp(bytes + Ether::size);
    }

    ArpPacket::ArpPacket(u_short opcode, const std::string &sender_mac, const std::string &sender_ip,
                         const std::string &target_mac, const std::string &target_ip) {
        ether = Ether(HwAddr(target_mac), HwAddr(sender_mac), ETHERTYPE_ARP);
        arp = Arp(opcode, HwAddr(sender_mac), IpAddr(sender_ip), HwAddr(target_mac), IpAddr(target_ip));
    }

    ArpPacket::ArpPacket(u_short opcode, const HwAddr &sender_mac, const IpAddr &sender_ip,
                         const HwAddr &target_mac, const IpAddr &target_ip) {
        ether = Ether(target_mac, sender_mac, ETHERTYPE_ARP);
        arp = Arp(opcode, sender_mac, sender_ip, target_mac, target_ip);
    }
}