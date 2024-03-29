#include <iostream>
#include <boost/thread.hpp>
#include "../includes/arpspoof/ArpSpoof.h"

using namespace std;
using namespace arpspoof;
using namespace network;

void usage(const char *cmd) {
    std::cout << "usage: " << cmd << " <sender ip>" << " <target ip>" << std::endl;
    std::cout << "example: " << cmd << " 192.168.0.1 192.168.0.101" << std::endl;
}

int main(int argc, char *argv[]) {
    if (argc < 4 or argc % 2 != 0) {
        usage(argv[0]);
        return -1;
    }
    char *dev = argv[1];
    boost::thread_group tg;
    for (int i = 2; i < argc; i += 2) {
        IpAddr sip(argv[i]), tip(argv[i+1]);
        auto *th1 = new boost::thread([dev, sip, tip] {
            ArpSpoof spoof(dev, sip, tip);
            spoof.spoof();
        });
        auto *th2 = new boost::thread([dev, sip, tip] {
            ArpSpoof spoof(dev, sip, tip);
            spoof.spoofed_relay();
        });
        tg.add_thread(th1);
        tg.add_thread(th2);
    }
    tg.join_all();
    return 0;
}