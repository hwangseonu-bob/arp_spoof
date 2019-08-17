#pragma once

#include <net/ethernet.h>
#include "../pdu/Ether.h"
#include "../pdu/Arp.h"

namespace network {
    class ArpPacket {
    public:
        Ether eth;
        Arp arp;
    public:
        ArpPacket() = default;
        ArpPacket(const ArpPacket &pk) = default;

        explicit ArpPacket(const byte *pk) : eth(Ether(pk)), arp(Arp(pk + eth.size())) {}

        explicit ArpPacket(const bytes& pk) : eth(Ether(bytes(pk.begin(), pk.begin() + 14))),
                                             arp(Arp(bytes(pk.begin() + eth.size(), pk.begin() + eth.size() + 28))) {}

        explicit ArpPacket(u_short opcode, const HwAddr &sender_mac, const IpAddr &sender_ip,
                           const HwAddr &target_mac, const IpAddr &target_ip) :
                eth(Ether(target_mac, sender_mac, ETHERTYPE_ARP)),
                arp(Arp(opcode, sender_mac, sender_ip, target_mac, target_ip)) {}

    public:
        bytes to_bytes() const;
        size_t size() const;
    };
}