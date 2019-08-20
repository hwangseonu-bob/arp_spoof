#include "../../includes/network/HwAddr.h"

#include <regex>

namespace network {

    HwAddr::HwAddr(bytes mac) {
        std::copy(mac.begin(), mac.begin() + size, addr.begin());
    }

    HwAddr::HwAddr(const byte *mac) {
        std::copy(mac, mac + size, addr.begin());
    }

    HwAddr::HwAddr(std::string mac) {
        std::regex reg("^(([0-9A-Fa-f]{2})[:-]){5}([0-9A-Fa-f]{2})$");
        if (regex_match(mac, reg)) {
            int values[size];
            if (mac.find(':') != std::string::npos)
                sscanf(mac.c_str(), "%x:%x:%x:%x:%x:%x%*c", values, values + 1, values + 2, values + 3, values + 4, values + 5);
            if (mac.find('-') != std::string::npos)
                sscanf(mac.c_str(), "%x-%x-%x-%x-%x-%x%*c", values, values + 1, values + 2, values + 3, values + 4, values + 5);
            for (int i = 0; i < size; i++) addr[i] = byte(values[i]);
        } else {
            throw std::runtime_error(mac + " is not mac address");
        }
    }

    bytes HwAddr::to_bytes() const {
        return bytes(addr.begin(), addr.end());
    }

    std::string HwAddr::to_string() const {
        char str[18];
        sprintf(str, "%02x:%02x:%02x:%02x:%02x:%02x", addr[0], addr[1], addr[2], addr[3], addr[4], addr[5]);
        return std::string(str);
    }

    bool HwAddr::operator==(const HwAddr &other) {
        return addr == other.addr;
    }

    bool HwAddr::operator!=(const HwAddr &other) {
        return addr != other.addr;
    }

    std::ostream& operator<<(std::ostream& o, const HwAddr& hwAddr) {
        return o << hwAddr.to_string();
    }

}