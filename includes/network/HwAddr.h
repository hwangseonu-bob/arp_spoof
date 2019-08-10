#pragma once

#include <cstdint>
#include <ostream>
#include <string>
#include <vector>

using byte=uint8_t;
using bytes=std::vector<byte>;

namespace network {
    class HwAddr {
    public:
        static const int size{6};
    protected:
        byte addr[size]{};
    public:
        HwAddr() = default;
        HwAddr(const HwAddr &mac) = default;
        explicit HwAddr(const byte mac[size]);
        explicit HwAddr(const std::string &mac) noexcept(false);
    public:
        bytes to_bytes() const;
        std::string to_string() const;
        void parse_string(const std::string &mac) noexcept(false);
    public:
        HwAddr &operator=(const std::string &mac);
    };
}

std::ostream &operator<<(std::ostream &o, const network::HwAddr &addr);