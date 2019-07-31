#include <cstring>

#include "ArpPacket.h"

using namespace network;

byte *ArpPacket::to_bytes() const {
    size_t sz = Ether::size + ip.total_length;
    byte *bytes = reinterpret_cast<byte*>(malloc(sz));

    std::memcpy(bytes, ether.to_bytes(), Ether::size);
    std::memcpy(bytes + Ether::size, ip.to_bytes(), ip.header_length());
    std::memcpy(bytes + Ether::size + ip.header_length(), arp.to_bytes(), sizeof(arp));
    return bytes;
}
