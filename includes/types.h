#pragma once

#include <cstdint>
#include <vector>
#include <utility>

namespace network {
    class HwAddr;
    class IpAddr;
}

using byte=uint8_t;
using bytes=std::vector<byte>;
using netpair=std::pair<network::HwAddr, network::IpAddr>;
