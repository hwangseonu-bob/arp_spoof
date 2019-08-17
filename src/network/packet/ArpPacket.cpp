#include "../../../includes/network/packet/ArpPacket.h"

namespace network {
    bytes ArpPacket::to_bytes() const {
        bytes result;
        bytes tmp;
        tmp = eth.to_bytes();
        result.insert(result.end(), tmp.begin(), tmp.end());
        tmp = arp.to_bytes();
        result.insert(result.end(), tmp.begin(), tmp.end());
        return result;
    }

    size_t ArpPacket::size() const {
        return eth.size() + arp.size();
    }
}