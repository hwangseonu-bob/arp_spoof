#pragma once

#include "../pdu/Ether.h"
#include "../pdu/IP.h"

namespace network {
    class IpPacket {
    public:
        Ether eth{};
        IP ip{};
        bytes data{};
    public:
        IpPacket() = default;
        IpPacket(const IpPacket&) = default;

        explicit IpPacket(bytes pk);
        explicit IpPacket(const byte* pk);
    public:
        size_t size() const;
        bytes to_bytes() const;
    };
}