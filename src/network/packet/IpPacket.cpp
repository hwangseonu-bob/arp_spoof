#include "../../../includes/network/packet/IpPacket.h"

namespace network {

    IpPacket::IpPacket(bytes pk) {
        eth = Ether(bytes(pk.begin(), pk.begin() + Ether::size));
        ip = IP(bytes(pk.begin() + Ether::size, pk.begin() + Ether::size + 20));
        data = bytes(pk.begin() + Ether::size + ip.header_size(), pk.begin() + Ether::size + ip.total_length);
    }

    IpPacket::IpPacket(const byte *pk) {
        eth = Ether(bytes(pk, pk + Ether::size));
        ip = IP(bytes(pk + Ether::size, pk + Ether::size + 20));
        data = bytes(pk + Ether::size + ip.header_size(), pk + Ether::size + ip.total_length);
    }

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
        return Ether::size + ip.total_length;
    }
}