#pragma once

#include "../HwAddr.h"
#include "../IpAddr.h"

namespace network {
    class IP {
    public:
        byte vihl{};
        byte tos{};
        uint16_t total_length{};
        uint16_t identification{};
        uint16_t flags{};
        byte ttl{};
        byte protocol{};
        uint16_t checksum{};
        IpAddr src;
        IpAddr dst;
    public:
        IP() = default;
        IP(const IP &) = default;

        explicit IP(const bytes &pk);
        explicit IP(const byte *pk);

    public:
        bytes to_bytes() const;
        size_t header_size() const;
    };

}