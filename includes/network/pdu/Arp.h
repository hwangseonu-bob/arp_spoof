#pragma once

#include "../HwAddr.h"
#include "../IpAddr.h"

namespace network {
    class Arp {
    public:
        uint16_t hw_type{};
        uint16_t pt_type{};
        byte hw_size{};
        byte pt_size{};
        uint16_t opcode{};
        HwAddr sender_mac;
        IpAddr sender_ip;
        HwAddr target_mac;
        IpAddr target_ip;
    public:
        Arp() = default;
        Arp(const Arp&) = default;
        explicit Arp(const byte *pk) :
                hw_type(pk[0] << 8 | pk[1]), pt_type(pk[2] << 8 | pk[3]), hw_size(pk[4]), pt_size(pk[5]),
                opcode(pk[6] << 8 | pk[7]),
                sender_mac(HwAddr(bytes(pk + 8, pk + 14))), sender_ip(IpAddr(bytes(pk + 14, pk + 18))),
                target_mac(HwAddr(bytes(pk + 18, pk + 24))), target_ip(IpAddr(bytes(pk + 24, pk + 28))) {}

        explicit Arp(const bytes& pk) :
                hw_type(pk[0] << 8 | pk[1]), pt_type(pk[2] << 8 | pk[3]), hw_size(pk[4]), pt_size(pk[5]),
                opcode(pk[6] << 8 | pk[7]),
                sender_mac(HwAddr(bytes(pk.begin() + 8, pk.begin() + 14))),
                sender_ip(IpAddr(bytes(pk.begin() + 14, pk.begin() + 18))),
                target_mac(HwAddr(bytes(pk.begin() + 18, pk.begin() + 24))),
                target_ip(IpAddr(bytes(pk.begin() + 24, pk.begin() + 28))) {}

        explicit Arp(u_short opcode, const HwAddr &smac, const IpAddr &sip, const HwAddr &tmac, const IpAddr &tip) :
                hw_type(0x0001), pt_type(0x0800), hw_size(HwAddr::size), pt_size(IpAddr::size), opcode(opcode),
                sender_mac(smac), sender_ip(sip), target_mac(tmac), target_ip(tip) {}

        explicit Arp(u_short hw_type, u_short pt_type, byte hw_size, byte pt_size, u_short opcode,
                     const HwAddr &smac, const IpAddr &sip, const HwAddr &tmac, const IpAddr &tip) :
                hw_type(hw_type), pt_type(pt_type), hw_size(hw_size), pt_size(pt_size), opcode(opcode),
                sender_mac(smac), sender_ip(sip), target_mac(tmac), target_ip(tip) {}

    public:
        bytes to_bytes() const;
        size_t size() const;
        size_t header_size() const;
    };

}