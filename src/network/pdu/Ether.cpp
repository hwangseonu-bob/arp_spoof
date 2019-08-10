#include <cstring>

#include "network/pdu/Ether.h"

namespace network {
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

    bytes Ether::to_bytes() const {
        bytes result;

        bytes dmac = dst.to_bytes();
        bytes smac = src.to_bytes();

        result.insert(result.end(), dmac.begin(), dmac.end());
        result.insert(result.end(), smac.begin(), smac.end());
        result.push_back(byte((type & 0xFF00) >> 8));
        result.push_back(byte(type & 0x00FF));
        return result;
    }
}
