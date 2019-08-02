#ifndef ARP_SENDER_UTILS_H
#define ARP_SENDER_UTILS_H

#include <string>
#include <pcap.h>

#include "HwAddr.h"
#include "IpAddr.h"

pcap *open_dev(const char *dev);
network::HwAddr get_dev_mac(const char *dev);
network::IpAddr get_dev_ip(const char *dev);
network::HwAddr get_target_mac(const char *dev, const network::IpAddr &tip);
void arp_spoof(const char *dev, const std::string &gw, const std::string &target);
#endif //ARP_SENDER_UTILS_H
