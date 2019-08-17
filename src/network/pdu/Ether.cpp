#include "../../../includes/network/pdu/Ether.h"

namespace network {
    bytes Ether::to_bytes() const {
        bytes result;
        bytes tmp;
        tmp = dst.to_bytes();
        result.insert(result.end(), tmp.begin(), tmp.end());
        tmp = src.to_bytes();
        result.insert(result.end(), tmp.begin(), tmp.end());
        result.push_back(type >> 8);
        result.push_back(type & 0x00FF);
        return result;
    }

    size_t Ether::size() const {
        return header_size();
    }

    size_t Ether::header_size() const {
        return 14;
    }
}