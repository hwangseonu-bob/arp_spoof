#pragma once

#include <pcap.h>
#include "HwAddr.h"
#include "IpAddr.h"

namespace network {
    pcap *open_dev(const char *dev);
    network::HwAddr get_dev_mac(const char *dev);
    network::IpAddr get_dev_ip(const char *dev);
    network::HwAddr get_target_mac(const char *dev, const IpAddr &tip) noexcept(false);
}