#include <iostream>
#include "../../../includes/network/pdu/IP.h"

namespace network {
    bytes IP::to_bytes() const {
        bytes result;
        bytes tmp;

        result.push_back(version << 4 | ihl);
        result.push_back(tos);
        result.push_back(total_length >> 8);
        result.push_back(total_length & 0xFF);
        result.push_back(identification >> 8);
        result.push_back(identification & 0xFF);
        result.push_back(flags >> 8);
        result.push_back(flags & 0xFF);
        result.push_back(ttl);
        result.push_back(protocol);
        result.push_back(checksum >> 8);
        result.push_back(checksum & 0xFF);

        tmp = src.to_bytes();
        result.insert(result.end(), tmp.begin(), tmp.end());
        tmp = dst.to_bytes();
        result.insert(result.end(), tmp.begin(), tmp.end());

        return result;
    }

    size_t IP::size() const {
        return total_length;
    }

    size_t IP::header_size() const {
        return ihl * 4;
    }

    size_t IP::trailer_size() const {
        return size() - header_size();
    }
}