#ifndef ARP_SENDER_ARPPACKET_H
#define ARP_SENDER_ARPPACKET_H

#include <cstdint>

using byte=uint8_t;

#include "pdu/Ether.h"
#include "pdu/Arp.h"

namespace network {
    class ArpPacket {
    public:
        static const int size = Ether::size + Arp::size;
        Ether ether;
        Arp arp;

    public:
        ArpPacket() = default;
        explicit ArpPacket(u_short opcode, const std::string &sender_mac, const std::string &sender_ip,
                           const std::string &target_mac, const std::string &target_ip);
        explicit ArpPacket(u_short opcode, const HwAddr &sender_mac, const IpAddr &sender_ip, const HwAddr &target_mac,
                           const IpAddr &target_ip);
    public:
        byte *to_bytes() const;
    };
}

#endif //ARP_SENDER_ARPPACKET_H
