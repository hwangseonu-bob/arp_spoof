#pragma once

#include "../HwAddr.h"
#include "../IpAddr.h"

namespace network {
    class IP {
    public:
        byte version;
        byte ihl;
        byte tos;
        uint16_t total_length;
        uint16_t identification;
        uint16_t flags;
        byte ttl;
        byte protocol;
        uint16_t checksum;
        IpAddr src;
        IpAddr dst;
    public:
        IP() = default;
        IP(const IP &) = default;

        explicit IP(const bytes &pk) :
                version(pk[0] >> 4), ihl(pk[0] & 0xF), tos(pk[1]), total_length(pk[2] << 8 | pk[3]),
                identification(pk[4] << 8 | pk[5]),
                flags(pk[6] << 8 | pk[7]), ttl(pk[8]), protocol(pk[9]), checksum(pk[10] << 8 | pk[11]),
                src(IpAddr(bytes(pk.begin() + 12, pk.begin() + 15))),
                dst(IpAddr(bytes(pk.begin() + 16, pk.begin() + 19))) {}

        explicit IP(const byte *pk) :
                version(pk[0] >> 4), ihl(pk[0] & 0xF), tos(pk[1]), total_length(pk[2] << 8 | pk[3]),
                identification(pk[4] << 8 | pk[5]), flags(pk[6] << 8 | pk[7]), ttl(pk[8]), protocol(pk[9]),
                checksum(pk[10] << 8 | pk[11]), src(IpAddr(pk + 12)), dst(IpAddr(pk + 16)) {}

    public:
        bytes to_bytes() const;
        size_t size() const;
        size_t header_size() const;
        size_t trailer_size() const;
    };

}