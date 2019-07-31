#include <cstring>
#include "Ip.h"

using namespace network;

Ip::Ip(const byte *ip) {
    this->version = ip[0] >> 4;
    this->ihl = ip[0] & 0xF;
    this->tos = ip[1];
    this->total_length = ip[2] << 8 | ip[3];
    this->identification = ip[4] << 8 | ip[5];
    this->flags = ip[6] << 8 | ip[7];
    this->ttl = ip[8];
    this->protocol = ip[9];
    this->checksum = ip[10] << 8 | ip[11];
    this->src = IpAddr(ip + 12);
    this->dst = IpAddr(ip + 16);
}

Ip::Ip(byte v, byte hl, byte tos, u_short tl, u_short id, u_short flags,
       byte ttl, byte proto, u_short chksum, const IpAddr &src, const IpAddr &dst) {
    this->version = v;
    this->ihl = hl;
    this->tos = tos;
    this->total_length = tl;
    this->identification = id;
    this->flags = flags;
    this->ttl = ttl;
    this->protocol = proto;
    this->checksum = chksum;
    this->src = src;
    this->dst = dst;
}

byte *Ip::to_bytes() const {
    byte *bytes = reinterpret_cast<byte *>(malloc(header_length()));
    bytes[0] = version << 4 | ihl;
    bytes[1] = tos;
    bytes[2] = byte(total_length & 0xF0 >> 8);
    bytes[3] = byte(total_length & 0x0F);
    bytes[4] = byte(identification & 0xF0 >> 8);
    bytes[5] = byte(identification & 0x0F);
    bytes[6] = byte(flags & 0xF0 >> 8);
    bytes[7] = byte(flags & 0x0F);
    bytes[8] = ttl;
    bytes[9] = protocol;
    bytes[10] = byte(checksum & 0xF0 >> 8);
    bytes[11] = byte(checksum & 0x0F);
    std::memcpy(bytes + 12, src.addr, IpAddr::size);
    std::memcpy(bytes + 16, dst.addr, IpAddr::size);
    return bytes;
}

uint Ip::header_length() const {
    return ihl << 2;
}
