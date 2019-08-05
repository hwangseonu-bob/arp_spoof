#pragma once

#include <cstdint>
#include "network/HwAddr.h"
#include "network/IpAddr.h"

using byte=uint8_t;

namespace network {
    class Arp {
    public:
        static const int size = 28;
    public:
        u_short hw_type{};
        u_short pt_type{};
        byte hw_size{};
        byte pt_size{};
        u_short opcode{};
        HwAddr sender_mac;
        IpAddr sender_ip;
        HwAddr target_mac;
        IpAddr target_ip;
    public:
        Arp() = default;
        Arp(const Arp& arp) = default;
        explicit Arp(const byte arp[]);
        explicit Arp(u_short oc, const HwAddr& smac, const IpAddr& sip, const HwAddr& tmac, const IpAddr& tip);
        explicit Arp(u_short ht, u_short pt, byte hs, byte ps, u_short oc,
                const HwAddr& smac, const IpAddr& sip, const HwAddr& tmac, const IpAddr& tip);
    public:
        byte* to_bytes() const;
    };
}