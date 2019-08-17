#pragma once

#include <utility>
#include <net/if_arp.h>

#include "Session.h"
#include "../network/utils.h"

namespace arpspoof {
    class ArpSpoof {
    public:
        std::string device;
        network::HwAddr dev_mac;
        Session session;
    public:
        ArpSpoof() = default;
        ArpSpoof(const ArpSpoof &) = default;

        explicit ArpSpoof(std::string dev, const Session &s) :
                device(std::move(dev)), dev_mac(network::get_dev_mac(dev.c_str())), session(s) {}

        explicit ArpSpoof(std::string dev, const network::HwAddr &smac, const network::IpAddr sip,
                          const network::HwAddr& tmac, const network::IpAddr &tip) :
                device(std::move(dev)), dev_mac(network::get_dev_mac(device.c_str())), session(Session(smac, sip, tmac, tip)) {}

        explicit ArpSpoof(std::string dev, const network::IpAddr sip, const network::IpAddr &tip) :
                device(std::move(dev)), dev_mac(network::get_dev_mac(device.c_str())),
                session(Session(network::get_target_mac(device.c_str(), sip), sip, network::get_target_mac(device.c_str(), tip), tip)) {}

    private:
        void send_arp(pcap *desc, uint16_t op = ARPOP_REPLY);
    public:
        void spoof();
        void spoof_periodic(uint32_t period = 3);
        void spoofed_relay();
    };
}