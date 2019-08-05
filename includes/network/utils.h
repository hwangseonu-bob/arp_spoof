#pragma once

#include <string>
#include <pcap.h>

#include "network/HwAddr.h"
#include "network/IpAddr.h"

namespace network {
    pcap *open_dev(const char *dev);
    network::HwAddr get_dev_mac(const char *dev);
    network::IpAddr get_dev_ip(const char *dev);
    network::HwAddr get_target_mac(const char *dev, const IpAddr &tip);
    void arp_spoof(const char *dev, const std::string &sender, const std::string &target);
}
