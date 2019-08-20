#pragma once

#include "../HwAddr.h"

namespace network {
    class Ether {
    public:
        const static size_t size = 14;
    public:
        HwAddr dst{};
        HwAddr src{};
        uint16_t type{0x0800};
    public:
        Ether() = default;
        Ether(const Ether &eth) = default;

        explicit Ether(bytes pk);
        explicit Ether(const byte *pk);

        Ether(HwAddr dst, HwAddr src, uint16_t type) : dst(dst), src(src), type(type) {}

    public:
        bytes to_bytes() const;
        std::string to_string() const;
    };

    std::ostream &operator<<(std::ostream &o, const Ether &eth);
}