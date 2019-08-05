cmake_minimum_required(VERSION 3.14)
project(arp_spoof)

set(CMAKE_CXX_STANDARD 14)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/includes)
include(FindPCAP.cmake)

set(SOURCE_LIST
        src/main.cpp
        src/network/HwAddr.cpp
        src/network/IpAddr.cpp
        src/network/pdu/Ether.cpp
        src/network/pdu/Arp.cpp
        src/network/ArpPacket.cpp
        src/network/utils.cpp
        )
add_executable(arp_spoof ${SOURCE_LIST})
target_link_libraries(arp_spoof ${PCAP_LIBRARY})