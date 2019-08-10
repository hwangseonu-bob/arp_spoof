#pragma once

#include <cstdint>
#include <vector>

#include "network/pdu/Ether.h"
#include "network/pdu/Arp.h"

using byte=uint8_t;
using bytes=std::vector<byte>;


namespace network {
    class ArpPacket {
    public:
        static const int size = Ether::size + Arp::size;
        Ether ether;
        Arp arp;

    public:
        ArpPacket() = default;
        ArpPacket(const ArpPacket &pk) = default;
        explicit ArpPacket(const byte bytes[size]);
        explicit ArpPacket(u_short opcode, const std::string &sender_mac, const std::string &sender_ip,
                           const std::string &target_mac, const std::string &target_ip);
        explicit ArpPacket(u_short opcode, const HwAddr &sender_mac, const IpAddr &sender_ip, const HwAddr &target_mac,
                           const IpAddr &target_ip);
    public:
        bytes to_bytes() const;
    };
}