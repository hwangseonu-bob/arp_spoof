cmake_minimum_required(VERSION 3.14)
project(arp_sender)

set(CMAKE_CXX_STANDARD 14)

add_executable(arp_sender main.cpp network/HwAddr.cpp network/HwAddr.h network/IpAddr.cpp network/IpAddr.h network/pdu/Ether.cpp network/pdu/Ether.h network/pdu/Ip.cpp network/pdu/Ip.h network/pdu/Arp.cpp network/pdu/Arp.h)