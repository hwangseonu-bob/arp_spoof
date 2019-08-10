#pragma once

#include <cstdint>
#include <string>

using byte=uint8_t;
using bytes=std::vector<byte>;

namespace network {
    class IpAddr {
    public:
        static const int size = 4;
    protected:
        byte addr[size] {};
    public:
        IpAddr() = default;
        IpAddr(const IpAddr &ip) = default;
        explicit IpAddr(const byte ip[size]);
        explicit IpAddr(uint32_t ip);
        explicit IpAddr(const std::string &ip) noexcept(false);
    public:
        bytes to_bytes() const;
        std::string to_string() const;
        void parse_string(const std::string &ip) noexcept(false);
    public:
        bool operator==(const IpAddr &ip);
        IpAddr &operator=(const std::string &ip);
    };
}

std::ostream &operator<<(std::ostream &o, const network::IpAddr &addr);