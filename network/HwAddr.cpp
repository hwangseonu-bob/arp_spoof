#include <cstring>
#include <regex>
#include "HwAddr.h"

using namespace network;

HwAddr::HwAddr() = default;

HwAddr::HwAddr(const HwAddr &mac) {
    std::memcpy(addr, mac.addr, size);
}

HwAddr::HwAddr(const byte *mac) {
    std::memcpy(addr, mac, size);
}

HwAddr::HwAddr(const char *mac) noexcept(false) {
    parse_string(std::string(mac));
}

HwAddr::HwAddr(const std::string &mac) noexcept(false) {
    parse_string(mac);
}

void HwAddr::parse_string(const std::string &mac) noexcept(false) {
    std::regex reg("^(([0-9A-Fa-f]{2})[:-]){5}([0-9A-Fa-f]{2})$");
    int l = 12, inc = 2;
    if (std::regex_match(mac, reg)) {
        l = 18;
        inc = 3;
    }

    int index = 0;
    for (int i = 0; i < l; i += inc) {
        addr[index++] = std::stoi(mac.substr(i, 2), nullptr, 16);
    }
}

std::string HwAddr::to_string() const {
    char str[20];
    sprintf(str, "%02x:%02x:%02x:%02x:%02x:%02x",
            addr[0], addr[1], addr[2], addr[3], addr[4], addr[5]);
    return std::string(str);
}

HwAddr &HwAddr::operator=(const std::string &mac) {
    parse_string(mac);
    return *this;
}

std::ostream &operator<<(std::ostream &o, const HwAddr &addr) {
    o << addr.to_string();
    return o;
}
