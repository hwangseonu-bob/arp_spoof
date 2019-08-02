#ifndef ARP_SENDER_UTILS_H
#define ARP_SENDER_UTILS_H

#include <pcap.h>

#include "HwAddr.h"
#include "IpAddr.h"

network::HwAddr get_dev_mac(const char *dev);
network::HwAddr get_target_mac(pcap *desc, const network::HwAddr &smac,
                               const network::IpAddr &sip, const network::IpAddr &tip);

#endif //ARP_SENDER_UTILS_H
