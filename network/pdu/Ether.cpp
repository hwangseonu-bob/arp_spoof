#include <cstring>
#include "Ether.h"

using namespace network;

Ether::Ether(const byte *pk) {
    dst = HwAddr(pk);
    src = HwAddr(pk + HwAddr::size);
    type = pk[12] << 8 | pk[13];
}

Ether::Ether(const HwAddr &dst, const HwAddr &src, u_short type) {
    this->dst = HwAddr(dst);
    this->src = HwAddr(src);
    this->type = type;
}

byte *Ether::to_bytes() const {
    byte *bytes = reinterpret_cast<byte *>(malloc(Ether::size));
    std::memcpy(bytes, dst.addr, HwAddr::size);
    std::memcpy(bytes + HwAddr::size, src.addr, HwAddr::size);
    bytes[HwAddr::size * 2] = byte(type & 0xF0 >> 8);
    bytes[HwAddr::size * 2 + 1] = byte(type & 0x0F);
    return bytes;
}
