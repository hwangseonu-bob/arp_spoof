#include "../../../includes/network/pdu/Arp.h"

namespace network {

    bytes Arp::to_bytes() const {
        bytes result;
        bytes tmp;

        result.push_back(hw_type >> 8);
        result.push_back(hw_type & 0x00FF);
        result.push_back(pt_type >> 8);
        result.push_back(pt_type & 0x00FF);
        result.push_back(hw_size);
        result.push_back(pt_size);
        result.push_back(opcode >> 8);
        result.push_back(opcode & 0x00FF);

        tmp = sender_mac.to_bytes();
        result.insert(result.end(), tmp.begin(), tmp.end());
        tmp = sender_ip.to_bytes();
        result.insert(result.end(), tmp.begin(), tmp.end());
        tmp = target_mac.to_bytes();
        result.insert(result.end(), tmp.begin(), tmp.end());
        tmp = target_ip.to_bytes();
        result.insert(result.end(), tmp.begin(), tmp.end());

        return result;
    }

    size_t Arp::size() const {
        return header_size();
    }

    size_t Arp::header_size() const {
        return 28;
    }
}