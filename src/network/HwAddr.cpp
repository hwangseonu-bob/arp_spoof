#include <regex>
#include <iostream>

#include "../../includes/network/HwAddr.h"

using namespace std;

namespace network {
    HwAddr::HwAddr(const string &mac) noexcept(false) {
        regex reg("^(([0-9A-Fa-f]{2})[:-]){5}([0-9A-Fa-f]{2})$");
        if (regex_match(mac, reg)) {
            int values[size];
            byte ptr[size];
            if (mac.find(':') != string::npos)
                sscanf(mac.c_str(), "%x:%x:%x:%x:%x:%x%*c", values, values + 1, values + 2, values + 3, values + 4, values + 5);
            if (mac.find('-') != string::npos)
                sscanf(mac.c_str(), "%x-%x-%x-%x-%x-%x%*c", values, values + 1, values + 2, values + 3, values + 4, values + 5);
            for (int i = 0; i < size; i++) ptr[i] = byte(values[i]);
            addr = bytes(ptr, ptr + size);
        } else {
            throw runtime_error(mac + " is not mac address");
        }
    }

    string HwAddr::to_string() const {
        char str[18];
        sprintf(str, "%02x:%02x:%02x:%02x:%02x:%02x", addr[0], addr[1], addr[2], addr[3], addr[4], addr[5]);
        return string(str);
    }

    bytes HwAddr::to_bytes() const {
        return bytes(addr.begin(), addr.begin() + size);
    }

    bool HwAddr::operator==(const HwAddr &other) {
        return other.addr == addr;
    }

    bool HwAddr::operator!=(const HwAddr& other) {
        return other.addr != addr;
    }

    std::ostream &operator<<(std::ostream &o, const HwAddr &mac) {
        return o << mac.to_string();
    }
}

