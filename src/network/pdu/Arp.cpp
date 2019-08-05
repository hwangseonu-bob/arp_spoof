#include <cstring>
#include <iostream>
#include <netinet/in.h>

#include "network/pdu/Arp.h"

using namespace network;

struct arp_header {
    uint16_t hw_type;
    uint16_t pt_type;
    uint8_t hw_size;
    uint8_t pt_size;
    uint16_t opcode;
};

Arp::Arp(const byte *arp) {
    auto *hd = reinterpret_cast<const arp_header *>(arp);
    hw_type = ntohs(hd->hw_type);
    pt_type = ntohs(hd->pt_type);
    hw_size = hd->hw_size;
    pt_size = hd->pt_size;
    opcode = ntohs(hd->opcode);

    sender_mac = HwAddr(arp + 8);
    sender_ip = IpAddr(arp + 14);
    target_mac = HwAddr(arp + 18);
    target_ip = IpAddr(arp + 24);
}

Arp::Arp(u_short oc, const HwAddr &smac, const IpAddr &sip, const HwAddr &tmac, const IpAddr &tip) {
    hw_type = 0x0001;
    pt_type = 0x0800;
    hw_size = HwAddr::size;
    pt_size = IpAddr::size;
    opcode = oc;
    sender_mac = smac;
    sender_ip = sip;
    target_mac = tmac;
    target_ip = tip;
}

Arp::Arp(u_short ht, u_short pt, byte hs, byte ps, u_short oc,
         const HwAddr &smac, const IpAddr &sip, const HwAddr &tmac, const IpAddr &tip) {
    hw_type = ht;
    pt_type = pt;
    hw_size = hs;
    pt_size = ps;
    opcode = oc;
    sender_mac = smac;
    sender_ip = sip;
    target_mac = tmac;
    target_ip = tip;
}

byte *Arp::to_bytes() const {
    byte *bytes = new byte[size];
    auto *hd = new arp_header;
    hd->hw_type = htons(hw_type);
    hd->pt_type = htons(pt_type);
    hd->hw_size = hw_size;
    hd->pt_size = pt_size;
    hd->opcode = htons(opcode);
    std::memcpy(bytes, hd, sizeof(arp_header));
    std::memcpy(bytes + 8, sender_mac.addr, HwAddr::size);
    std::memcpy(bytes + 14, sender_ip.addr, IpAddr::size);
    std::memcpy(bytes + 18, target_mac.addr, HwAddr::size);
    std::memcpy(bytes + 24, target_ip.addr, IpAddr::size);
    delete (hd);
    return bytes;
}

