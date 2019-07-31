#include "Ether.h"

using namespace network;

Ether::Ether(const byte *pk) {
    dst = HwAddr(pk);
    src = HwAddr(pk + HwAddr::size);
    type = pk[12] << 8 | pk[13];
}

Ether::Ether(const HwAddr& dst, const HwAddr& src, u_short type) {
    this->dst = HwAddr(dst);
    this->src = HwAddr(src);
    this->type = type;
}