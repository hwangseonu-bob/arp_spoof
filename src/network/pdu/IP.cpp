#include <cstring>
#include <netinet/in.h>
#include "../../../includes/network/pdu/IP.h"

namespace network {

    IP::IP(const bytes &pk) {
        memcpy(this, pk.data(), 12);
        total_length = ntohs(total_length);
        identification = ntohs(identification);
        flags = ntohs(flags);
        checksum = ntohs(checksum);
        src = IpAddr(bytes(pk.begin() + 12, pk.begin() + 12 + IpAddr::size));
        dst = IpAddr(bytes(pk.begin() + 12 + IpAddr::size, pk.begin() + 12 + IpAddr::size + IpAddr::size));
    }

    IP::IP(const byte *pk) {
        memcpy(this, pk, 12);
        total_length = ntohs(total_length);
        identification = ntohs(identification);
        flags = ntohs(flags);
        checksum = ntohs(checksum);
        src = IpAddr(bytes(pk + 12, pk + 12 + IpAddr::size));
        dst = IpAddr(bytes(pk + 12 + IpAddr::size, pk + 12 + IpAddr::size + IpAddr::size));
    }

    bytes IP::to_bytes() const {
        auto clone = IP(*this);
        clone.total_length = htons(total_length);
        clone.identification = htons(identification);
        clone.flags = htons(flags);
        clone.checksum = htons(checksum);
        auto *ptr = (byte*)&clone;
        return bytes(ptr, ptr + header_size());
    }

    size_t IP::header_size() const {
        return (vihl & 0xF) << 2;
    }

}