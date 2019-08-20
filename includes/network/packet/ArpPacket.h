#pragma once

#include <net/ethernet.h>
#include "../pdu/Ether.h"
#include "../pdu/Arp.h"

namespace network {
    class ArpPacket {
    public:
        const static size_t size = Ether::size + Arp::size;
        Ether eth{};
        Arp arp{};
    public:
        ArpPacket() = default;
        ArpPacket(const ArpPacket &) = default;

        explicit ArpPacket(bytes pk) : eth(Ether(bytes(pk.begin(), pk.begin() + Ether::size))),
                                       arp(Arp(bytes(pk.begin() + Ether::size, pk.begin() + size))) {}

        explicit ArpPacket(const byte *pk) : eth(Ether(bytes(pk, pk + Ether::size))),
                                             arp(Arp(bytes(pk + Ether::size, pk + size))) {}

        ArpPacket(uint16_t opcode, HwAddr smac, IpAddr sip, HwAddr tmac, IpAddr tip) :
                eth(Ether(tmac, smac, ETHERTYPE_ARP)), arp(Arp(opcode, smac, sip, tmac, tip)) {}
    public:
        bytes to_bytes() const;
    };
}