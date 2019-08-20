#pragma once

#include <array>

#include "../types.h"

namespace network {
    class HwAddr {
    public:
        const static size_t size = 6;
    protected:
        std::array<byte, size> addr{};
    public:
        HwAddr() = default;
        HwAddr(const HwAddr &) = default;

        explicit HwAddr(std::array<byte, size> mac) : addr(mac) {}
        explicit HwAddr(bytes mac);
        explicit HwAddr(const byte *mac);
        explicit HwAddr(std::string mac);
    public:
        bytes to_bytes() const;
        std::string to_string() const;
    public:
        bool operator==(const HwAddr& other);
        bool operator!=(const HwAddr& other);
    };

    std::ostream& operator<<(std::ostream& o, const HwAddr& hwAddr);
}