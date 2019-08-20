#pragma once

#include <net/if_arp.h>
#include "../../../includes/network/HwAddr.h"
#include "../../../includes/network/IpAddr.h"

namespace network {
    class Arp {
    public:
        const static size_t size = 28;
    public:
        uint16_t hw_type{0x0001};
        uint16_t pt_type{0x0800};
        byte hw_len{HwAddr::size};
        byte pt_len{IpAddr::size};
        uint16_t opcode{ARPOP_REQUEST};
        HwAddr sender_mac{};
        IpAddr sender_ip{};
        HwAddr target_mac{};
        IpAddr target_ip{};
    public:
        Arp() = default;
        Arp(const Arp &) = default;

        explicit Arp(bytes pk);
        explicit Arp(const byte *pk);

        Arp(uint16_t hw_type, uint16_t pt_type, uint8_t hw_len, uint8_t pt_len, uint16_t opcode,
            HwAddr smac, IpAddr sip, HwAddr tmac, IpAddr tip) :
                hw_type(hw_len), pt_type(pt_type), hw_len(hw_len), pt_len(pt_len), opcode(opcode),
                sender_mac(smac), sender_ip(sip), target_mac(tmac), target_ip(tip) {};

        Arp(uint16_t opcode, HwAddr smac, IpAddr sip, HwAddr tmac, IpAddr tip) :
                opcode(opcode), sender_mac(smac), sender_ip(sip), target_mac(tmac), target_ip(tip) {};
    public:
        bytes to_bytes() const;
        std::string to_string() const;
    };

    std::ostream &operator<<(std::ostream &o, const Arp &arp);
}