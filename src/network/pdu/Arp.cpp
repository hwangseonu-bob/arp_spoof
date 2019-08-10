#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <net/if_arp.h>
#include <variant>

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

    bytes Arp::to_bytes() const {
        bytes result;

        auto *arp_hd = new arphdr;
        arp_hd->ar_hrd = htons(hw_type);
        arp_hd->ar_pro = htons(pt_type);
        arp_hd->ar_hln = hw_size;
        arp_hd->ar_pln = pt_size;
        arp_hd->ar_op = htons(opcode);

        byte tmp[sizeof(arphdr)];
        memcpy(tmp, arp_hd, sizeof(arphdr));
        delete (arp_hd);
        for(byte b : tmp) result.push_back(b);

        bytes smac = sender_mac.to_bytes();
        result.insert(result.end(), smac.begin(), smac.end());
        bytes sip = sender_ip.to_bytes();
        result.insert(result.end(), sip.begin(), sip.end());
        bytes tmac = target_mac.to_bytes();
        result.insert(result.end(), tmac.begin(), tmac.end());
        bytes tip = target_ip.to_bytes();
        result.insert(result.end(), tip.begin(), tip.end());
        return result;
    }

}