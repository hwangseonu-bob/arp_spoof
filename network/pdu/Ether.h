#ifndef ARP_SENDER_ETHER_H
#define ARP_SENDER_ETHER_H

#include <cstdint>
#include <ostream>
#include "../HwAddr.h"

using byte=uint8_t;

namespace network {
    class Ether {
    public:
        static const int size = 14;
        HwAddr dst;
        HwAddr src;
        u_short type {0x0800};
    public:
        Ether() = default;
        Ether(const Ether& eth) = default;
        explicit Ether(const byte pk[size]);
        explicit Ether(const HwAddr& dst, const HwAddr& src, u_short type);
    public:
        byte* to_bytes() const;
    };
}

#endif //ARP_SENDER_ETHER_H
