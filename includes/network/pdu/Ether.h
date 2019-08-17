#pragma once

#include "../HwAddr.h"

namespace network {
    class Ether {
    public:
        HwAddr dst;
        HwAddr src;
        uint16_t type{};
    public:
        Ether() = default;
        Ether(const Ether&) = default;

        explicit Ether(const HwAddr &dst, const HwAddr &src, uint16_t type = 0x0800) : dst(dst), src(src), type(type) {}

        explicit Ether(const bytes& pk) : dst(HwAddr(bytes(pk.begin(), pk.begin() + HwAddr::size))),
                                   src(HwAddr(bytes(pk.begin() + HwAddr::size, pk.begin() + HwAddr::size * 2))),
                                   type(pk[HwAddr::size * 2] << 8 | pk[HwAddr::size * 2 + 1]) {}

        explicit Ether(const byte *pk) : dst(HwAddr(bytes(pk, pk + HwAddr::size))),
                                         src(HwAddr(bytes(pk + HwAddr::size, pk + HwAddr::size * 2))),
                                         type(pk[HwAddr::size * 2] << 8 | pk[HwAddr::size * 2 + 1]) {}

    public:
        bytes to_bytes() const;
        size_t size() const;
        size_t header_size() const;
    };

}