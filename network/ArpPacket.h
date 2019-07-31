#ifndef ARP_SENDER_ARPPACKET_H
#define ARP_SENDER_ARPPACKET_H

#include <cstdint>

using byte=uint8_t;

#include "pdu/Ether.h"
#include "pdu/Ip.h"
#include "pdu/Arp.h"

namespace network {
    class ArpPacket {
    public:
        Ether ether;
        Ip ip;
        Arp arp;
    public:
        byte* to_bytes() const;
    };
}

#endif //ARP_SENDER_ARPPACKET_H
