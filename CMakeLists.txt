cmake_minimum_required(VERSION 3.14)
project(arp_spoof)

set(dir ${CMAKE_CURRENT_SOURCE_DIR}/../../bin)
set(EXECUTABLE_OUTPUT_PATH ${dir})

set(CMAKE_CXX_STANDARD 14)
include(FindPCAP.cmake)

add_executable(arp_spoof main.cpp network/HwAddr.cpp network/HwAddr.h network/IpAddr.cpp network/IpAddr.h network/pdu/Ether.cpp network/pdu/Ether.h network/pdu/Arp.cpp network/pdu/Arp.h network/ArpPacket.cpp network/ArpPacket.h network/utils.cpp network/utils.h)
target_link_libraries(arp_spoof ${PCAP_LIBRARY})