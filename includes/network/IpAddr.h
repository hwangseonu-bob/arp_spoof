#pragma once

#include <utility>
#include <string>

#include "../types.h"

namespace network {
    class HwAddr {
    public:
        const static size_t size = 6;
    protected:
        bytes addr;
    public:
        HwAddr() : addr(bytes(size)) {}
        HwAddr(const HwAddr &mac) : addr(bytes(mac.addr.begin(), mac.addr.begin() + size)) {}
        explicit HwAddr(bytes mac) : addr(bytes(mac.begin(), mac.begin() + size)) {}
        explicit HwAddr(const bytes *mac) : addr(bytes(mac, mac + size)) {}
        explicit HwAddr(const std::string& mac);
    public:
        std::string to_string() const;
        bytes to_bytes() const;
    };

    std::ostream& operator<<(std::ostream& o, const HwAddr& mac);
}