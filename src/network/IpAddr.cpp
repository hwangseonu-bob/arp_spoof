#include "../../includes/network/IpAddr.h"

#include <regex>

namespace network {
    IpAddr::IpAddr(bytes ip) {
        std::copy(ip.begin(), ip.begin() + size, addr.begin());
    }

    IpAddr::IpAddr(const byte *ip) {
        std::copy(ip, ip + size, addr.begin());
    }

    IpAddr::IpAddr(uint32_t ip) {
        byte *ptr = reinterpret_cast<byte*>(&ip);
        std::copy(ptr, ptr + size, addr.begin());
    }

    IpAddr::IpAddr(std::string ip) {
        std::regex reg(
                "^(([0-9]|[1-9][0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-5])\\.){3}([0-9]|[1-9][0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-5])$");

        if (std::regex_match(ip, reg)) {
            int values[size];
            sscanf(ip.c_str(), "%d.%d.%d.%d", values, values + 1, values + 2, values + 3);
            for (int i = 0; i < size; i++) addr[i] = values[i];
        } else {
            throw std::invalid_argument("invalid arguments : " + ip + " is not an ip address");
        }
    }

    bytes IpAddr::to_bytes() const {
        return bytes(addr.begin(), addr.end());
    }

    std::string IpAddr::to_string() const {
        char str[16];
        sprintf(str, "%d.%d.%d.%d", addr[0], addr[1], addr[2], addr[3]);
        return std::string(str);
    }

    bool IpAddr::operator==(const IpAddr &other) {
        return addr == other.addr;
    }

    bool IpAddr::operator!=(const IpAddr &other) {
        return addr != other.addr;
    }

    std::ostream& operator<<(std::ostream& o, const IpAddr& ipAddr) {
        return o << ipAddr.to_string();
    }

}