#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <net/if_arp.h>

#include "network/pdu/Arp.h"

namespace network {
    Arp::Arp(const byte *arp) {
        auto *hd = reinterpret_cast<const arphdr *>(arp);
        hw_type = ntohs(hd->ar_hrd);
        pt_type = ntohs(hd->ar_pro);
        hw_size = hd->ar_hln;
        pt_size = hd->ar_pln;
        opcode = ntohs(hd->ar_op);

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
        auto *hd = new arphdr;
        hd->ar_hrd = htons(hw_type);
        hd->ar_pro = htons(pt_type);
        hd->ar_hln = hw_size;
        hd->ar_pln = pt_size;
        hd->ar_op = htons(opcode);
        std::memcpy(bytes, hd, sizeof(arphdr));
        std::memcpy(bytes + 8, sender_mac.addr, HwAddr::size);
        std::memcpy(bytes + 14, sender_ip.addr, IpAddr::size);
        std::memcpy(bytes + 18, target_mac.addr, HwAddr::size);
        std::memcpy(bytes + 24, target_ip.addr, IpAddr::size);
        delete (hd);
        return bytes;
    }
}