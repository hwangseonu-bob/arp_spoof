
#include "../../../includes/network/pdu/Ether.h"

#include <net/ethernet.h>
#include <netinet/in.h>
#include <sstream>
#include <cstring>

namespace network {

    Ether::Ether(bytes pk) {
        memcpy(this, pk.data(), 14);
        type = ntohs(type);
    }

    Ether::Ether(const byte *pk) {
        memcpy(this, pk, 14);
        type = ntohs(type);
    }

    bytes Ether::to_bytes() const {
        auto clone = Ether(*this);
        clone.type = htons(clone.type);
        auto *ptr = (byte*)&clone;
        return bytes(ptr, ptr + 14);
    }

    std::string Ether::to_string() const {
        std::stringstream ss;
        char t[6];
        sprintf(t, "0x%04x", type);
        ss << "Ether(dst: " << dst << ", src: " << src << ", type: " << t << ")";
        return ss.str();
    }

    std::ostream& operator<<(std::ostream& o, const Ether& eth) {
        return o << eth.to_string();
    }
}