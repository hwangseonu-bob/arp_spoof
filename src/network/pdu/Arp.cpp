#include "../../../includes/network/pdu/Ether.h"

namespace network {
    Ether *Ether::clone() const {
        return new Ether(*this);
    }

    size_t Ether::header_length() const {
        return 14;
    }

    bytes Ether::to_bytes() const {
        bytes result;
        bytes tmp;
        tmp = dst.to_bytes();
        result.insert(result.end(), tmp.begin(), tmp.end());
        tmp = src.to_bytes();
        result.insert(result.end(), tmp.begin(), tmp.end());
        result[HwAddr::size*2] = type >> 8;
        result[HwAddr::size*2 + 1] = type & 0x00FF;
        return result;
    }
}