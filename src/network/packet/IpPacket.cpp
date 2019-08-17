#include "../../../includes/network/packet/IpPacket.h"

namespace network {

    bytes IpPacket::to_bytes() const {
        bytes result;
        bytes tmp;

        tmp = eth.to_bytes();
        result.insert(result.end(), tmp.begin(), tmp.end());

        tmp = ip.to_bytes();
        result.insert(result.end(), tmp.begin(), tmp.end());

        result.insert(result.end(), data.begin(), data.end());

        return result;
    }

    size_t IpPacket::size() const {
        return eth.size() + ip.size();
    }
}