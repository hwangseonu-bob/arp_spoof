#pragma once

#include <array>
#include "../types.h"

namespace network {
    class IpAddr { public:
        const static size_t size = 4;
    protected:
        std::array<byte, size> addr{};
    public:
        IpAddr() = default;
        IpAddr(const IpAddr &) = default;

        explicit IpAddr(std::array<byte, size> ip) : addr(ip) {}
        explicit IpAddr(bytes ip);
        explicit IpAddr(uint32_t ip);
        explicit IpAddr(const byte *ip);
        explicit IpAddr(std::string ip);
    public:
        bytes to_bytes() const;
        std::string to_string() const;
    public:
        bool operator==(const IpAddr& other);
        bool operator!=(const IpAddr& other);
    };

    std::ostream& operator<<(std::ostream& o, const IpAddr& ipAddr);
}