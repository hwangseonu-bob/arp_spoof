#pragma once

#include <utility>
#include "../network/HwAddr.h"
#include "../network/IpAddr.h"
#include "ArpSpoof.h"

using network_pair=std::pair<network::HwAddr, network::IpAddr>;

namespace arpspoof {
    class Session {
    public:
        network_pair sender;
        network_pair target;

        friend class ArpSpoof;

    public:
        Session() = default;
        Session(const Session &) = default;

        explicit Session(const network::HwAddr &smac, const network::IpAddr &sip,
                         const network::HwAddr &tmac, const network::IpAddr &tip) :
                sender(network_pair(smac, sip)), target(network_pair(tmac, tip)) {}
    };
}