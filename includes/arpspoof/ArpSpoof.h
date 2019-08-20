#pragma once

#include <string>
#include <net/if_arp.h>
#include "../network/HwAddr.h"
#include "../network/utils.h"
#include "Session.h"

namespace arpspoof {
    class ArpSpoof {
    public:
        std::string device;
        netpair my{};
        Session session{};
    public:
        ArpSpoof() = default;
        ArpSpoof(const ArpSpoof &) = default;

        explicit ArpSpoof(std::string dev, Session s) :
                device(std::move(dev)), session(s),
                my(netpair(network::get_dev_mac(device.c_str()), network::get_dev_ip(device.c_str()))) {}

        explicit ArpSpoof(std::string dev, network::HwAddr smac, network::IpAddr sip,
                          network::HwAddr tmac, network::IpAddr tip) :
                device(std::move(dev)), session(Session(smac, sip, tmac, tip)),
                my(netpair(network::get_dev_mac(device.c_str()), network::get_dev_ip(device.c_str()))) {}

        explicit ArpSpoof(std::string dev, network::IpAddr sip, network::IpAddr tip) :
                device(std::move(dev)),
                my(netpair(network::get_dev_mac(device.c_str()), network::get_dev_ip(device.c_str()))),
                session(Session(network::get_target_mac(device.c_str(), sip), sip,
                                network::get_target_mac(device.c_str(), tip), tip)) {}

    private:
        void send_arp(pcap *desc, int cnt = 1, uint16_t op = ARPOP_REPLY);
    public:
        void spoof();
        void spoof_periodic(uint32_t period = 3);
        void spoofed_relay();
    };
}