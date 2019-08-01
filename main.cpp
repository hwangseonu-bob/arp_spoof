#include <iostream>
#include <pcap.h>
#include <cstring>
#include <net/if_arp.h>
#include "network/ArpPacket.h"

#define MAX_BYTES 2048

using namespace network;
using namespace std;

int main(int argc, char *argv[]) {
    pcap_t *desc = nullptr;
    char errbuf[PCAP_ERRBUF_SIZE] = {};
    char *dev = argv[1];

    std::memset(errbuf, 0, PCAP_ERRBUF_SIZE);

    cout << "open device " << dev << endl;

    if ((desc = pcap_open_live(dev, MAX_BYTES, 0, 512, errbuf)) == nullptr) {
        cout << "error: "  << errbuf << endl;
        return -1;
    }

    ArpPacket arp(ARPOP_REQUEST,
            "AA:AA:AA:AA:AA:AA", "192.168.168.1",
            "BB:BB:BB:BB:BB:BB", "192.168.168.33");

    byte *packet = arp.to_bytes();

    if (pcap_sendpacket(desc, packet, ArpPacket::size) != 0) {
        fprintf(stderr, "\nError sending the packet : %s\n", pcap_geterr(desc));
        exit(EXIT_FAILURE);
    }

    free(packet);
    pcap_close(desc);
    return 0;
}