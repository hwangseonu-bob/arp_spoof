#include <cstring>
#include <iostream>
#include <regex>

#include "network/IpAddr.h"

using namespace network;

IpAddr::IpAddr(const byte *ip) {
    std::memcpy(addr, ip, size);
}

IpAddr::IpAddr(uint32_t ip) {
    byte *bytes = reinterpret_cast<byte*>(&ip);
    std::memcpy(addr, bytes, size);
}

IpAddr::IpAddr(const std::string &ip) {
    parse_string(ip);
}

void IpAddr::parse_string(const std::string &ip) noexcept(false) {
    std::regex reg(
            "^(([0-9]|[1-9][0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-5])\\.){3}([0-9]|[1-9][0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-5])$");

    std::string format = "%d.%d.%d.%d";
    if (std::regex_match(ip, reg)) {
        std::sscanf(ip.c_str(), format.c_str(), addr, addr+1, addr+2, addr+3);
    } else {
        throw std::invalid_argument("invalid arguments : " + ip + " is not an ip address");
    }
}

std::string IpAddr::to_string() const {
    char str[20];
    sprintf(str, "%d.%d.%d.%d",
            addr[0], addr[1], addr[2], addr[3]);
    return std::string(str);
}

IpAddr &IpAddr::operator=(const std::string &ip) {
    parse_string(ip);
    return *this;
}

bool IpAddr::operator==(const IpAddr &ip) {
    if (addr[0] != ip.addr[0]) return false;
    if (addr[1] != ip.addr[1]) return false;
    if (addr[2] != ip.addr[2]) return false;
    return addr[3] == ip.addr[3];
}

std::ostream &operator<<(std::ostream &o, const IpAddr &addr) {
    o << addr.to_string();
    return o;
}


