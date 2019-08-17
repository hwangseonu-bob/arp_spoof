#pragma once

#include <utility>
#include <string>

#include "../types.h"

namespace network {
    class IpAddr {
    public:
        const static size_t size = 4;
    protected:
        bytes addr;
    public:
        IpAddr() : addr(bytes(size)) {}

        IpAddr(const IpAddr &ip) : addr(bytes(ip.addr.begin(), ip.addr.begin() + size)) {}

        explicit IpAddr(uint32_t ip) : IpAddr(reinterpret_cast<byte *>(&ip)) {}

        explicit IpAddr(const bytes& ip) : addr(bytes(ip.begin(), ip.begin() + size)) {}

        explicit IpAddr(const byte *ip) : addr(bytes(ip, ip + size)) {}

        explicit IpAddr(const std::string &ip);
    public:
        std::string to_string() const;
        bytes to_bytes() const;
    public:
        bool operator==(const IpAddr& other);
    };

    std::ostream &operator<<(std::ostream &o, const IpAddr &mac);
}