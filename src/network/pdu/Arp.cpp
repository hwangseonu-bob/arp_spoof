#include "../../../includes/network/pdu/Arp.h"

#include <arpa/inet.h>
#include <sstream>
#include <cstring>

namespace network {
    Arp::Arp(bytes pk) {
        memcpy(this, pk.data(), size);
        hw_type = htons(hw_type);
        pt_type = htons(pt_type);
        opcode = htons(opcode);
    }

    Arp::Arp(const byte *pk) {
        memcpy(this, pk, size);
        hw_type = htons(hw_type);
        pt_type = htons(pt_type);
        opcode = htons(opcode);
    }

    bytes Arp::to_bytes() const {
        auto clone = Arp(*this);
        clone.hw_type = htons(hw_type);
        clone.pt_type = htons(pt_type);
        clone.opcode = htons(opcode);
        auto *ptr = (byte*)&clone;
        return bytes(ptr, ptr + 28);
    }

    std::string Arp::to_string() const {
        std::stringstream ss;
        ss << "Arp(op: " << opcode << ", sender: " << sender_ip << ", target: " << target_ip << ")";
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &o, const Arp &arp) {
        return o << arp.to_string();
    }
}
