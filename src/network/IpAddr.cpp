#include <regex>
#include <iostream>

#include "../../includes/network/IpAddr.h"

using namespace std;

namespace network {
    IpAddr::IpAddr(const string &ip) {
        std::regex reg(
                "^(([0-9]|[1-9][0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-5])\\.){3}([0-9]|[1-9][0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-5])$");

        if (std::regex_match(ip, reg)) {
            int values[size];
            byte ptr[size];
            sscanf(ip.c_str(), "%d.%d.%d.%d", values, values + 1, values + 2, values + 3);
            for (int i = 0; i < size; i++) ptr[i] = values[i];
            addr = bytes(ptr, ptr + size);
        } else {
            throw std::invalid_argument("invalid arguments : " + ip + " is not an ip address");
        }
    }

    string IpAddr::to_string() const {
        char str[16];
        sprintf(str, "%d.%d.%d.%d", addr[0], addr[1], addr[2], addr[3]);
        return string(str);
    }

    bytes IpAddr::to_bytes() const {
        return bytes(addr.begin(), addr.begin() + size);
    }

    bool IpAddr::operator==(const IpAddr& other) {
        if (addr[0] != other.addr[0]) return false;
        if (addr[1] != other.addr[1]) return false;
        if (addr[2] != other.addr[2]) return false;
        return addr[3] == other.addr[3];
    }

    std::ostream &operator<<(std::ostream &o, const IpAddr &mac) {
        return o << mac.to_string();
    }
}

