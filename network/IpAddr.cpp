#include <cstring>
#include <regex>
#include "IpAddr.h"

using namespace network;

IpAddr::IpAddr() = default;

IpAddr::IpAddr(const network::IpAddr &ip) {
    std::memcpy(addr, ip.addr, size);
}

IpAddr::IpAddr(const byte *ip) {
    std::memcpy(addr, ip, size);
}

IpAddr::IpAddr(const char *ip) {
    parse_string(std::string(ip));
}

IpAddr::IpAddr(const std::string &ip) {
    parse_string(ip);
}

void IpAddr::parse_string(const std::string &ip) noexcept(false) {
    std::regex reg(
            "^(([0-9]|[1-9][0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-5])\\.){3}([0-9]|[1-9][0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-5])$");

    std::string str(ip);
    int i = 0;
    if (std::regex_match(ip, reg)) {
        size_t pos = 0;
        std::string token;
        while ((pos = str.find('.')) != std::string::npos) {
            addr[i++] = std::stoi(str.substr(0, pos));
            str.erase(0, pos + 1);
        }
        addr[i] = std::stoi(str);
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

std::ostream &operator<<(std::ostream &o, const IpAddr &addr) {
    o << addr.to_string();
    return o;
}


