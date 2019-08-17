#pragma once

#include "../pdu/Ether.h"
#include "../pdu/IP.h"

namespace network {
    class IpPacket {
    public:
        Ether eth;
        IP ip;
    public:
        IpPacket() = default;
        IpPacket(const IpPacket &pk) = default;

        explicit IpPacket(const byte *pk) : eth(Ether(pk)), ip(IP(pk + eth.size())) {}
//                                            data(bytes(pk + eth.size() + ip.header_size(), pk + eth.size() + ip.size())) {}

        explicit IpPacket(const bytes &pk) : eth(Ether(pk)), ip(IP(bytes(pk.begin() + eth.size(), pk.end()))) {}
//                                             data(bytes(pk.begin() + eth.size() + ip.header_size(), pk.begin() + eth.size() + ip.size())) {}

    public:
        bytes to_bytes() const;
        size_t size() const;
    };

}