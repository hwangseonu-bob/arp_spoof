cmake_minimum_required(VERSION 3.14)
project(arp_spoof)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_LIST
        includes/arpspoof/Session.h
        includes/arpspoof/ArpSpoof.h
        includes/network/packet/ArpPacket.h
        includes/network/packet/IpPacket.h
        includes/network/pdu/Arp.h
        includes/network/pdu/Ether.h
        includes/network/pdu/IP.h
        includes/network/HwAddr.h
        includes/network/IpAddr.h
        includes/network/utils.h
        includes/types.h

        src/arpspoof/ArpSpoof.cpp
        src/network/packet/ArpPacket.cpp
        src/network/packet/IpPacket.cpp
        src/network/pdu/Arp.cpp
        src/network/pdu/Ether.cpp
        src/network/pdu/IP.cpp
        src/network/HwAddr.cpp
        src/network/IpAddr.cpp
        src/network/utils.cpp

        src/main.cpp)

add_executable(arp_spoof ${SOURCE_LIST})
target_link_libraries(arp_spoof pcap boost_system boost_thread)