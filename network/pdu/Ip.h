#ifndef ARP_SENDER_IP_H
#define ARP_SENDER_IP_H

#include <cstdint>
#include "../IpAddr.h"

using byte=uint8_t;
using u_short=uint16_t;

namespace network {
    class Ip {
    public:
        byte version;
        byte ihl;
        byte tos;
        u_short total_length;
        u_short identification;
        u_short flags;
        byte ttl;
        byte protocol;
        u_short checksum;
        IpAddr src;
        IpAddr dst;
    public:
        Ip() = default;
        explicit Ip(const byte ip[]);
        explicit Ip(byte v, byte hl, byte tos,
                u_short tl, u_short id, u_short flags,
                byte ttl, byte proto, u_short chksum,
                const IpAddr& src, const IpAddr& dst);
    public:
        uint header_length() const;
        byte* to_bytes() const;
    };
}

#endif //ARP_SENDER_IP_H
