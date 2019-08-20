#pragma once

#include "../types.h"
#include "../network/HwAddr.h"
#include "../network/IpAddr.h"

namespace arpspoof {
    class Session {
    public:
        netpair sender{};
        netpair target{};
    public:
        Session() = default;
        Session(const Session &) = default;

        Session(network::HwAddr smac, network::IpAddr sip, network::HwAddr tmac, network::IpAddr tip) :
                sender(netpair(smac, sip)), target(netpair(tmac, tip)) {}
    };
}