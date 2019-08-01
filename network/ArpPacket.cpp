#include <cstring>
#include <netinet/if_ether.h>

#include "ArpPacket.h"

using namespace network;

byte *ArpPacket::to_bytes() const {
    byte *bytes = new byte[size];
    byte *eth = ether.to_bytes();
    byte *arp = this->arp.to_bytes();

    std::memcpy(bytes, eth, Ether::size);
    std::memcpy(bytes + Ether::size, arp, Arp::size);

    delete (eth);
    delete (arp);
    return bytes;
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
