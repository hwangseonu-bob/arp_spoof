cmake_minimum_required(VERSION 3.14)
project(arp_spoof)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build)

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

#add_executable(arp_spoof src/main.cpp network/HwAddr.cpp network/HwAddr.h network/IpAddr.cpp network/IpAddr.h network/pdu/Ether.cpp network/pdu/Ether.h network/pdu/Arp.cpp network/pdu/Arp.h network/ArpPacket.cpp network/ArpPacket.h network/utils.cpp network/utils.h)