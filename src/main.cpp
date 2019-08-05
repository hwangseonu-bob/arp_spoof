#include <iostream>

#include "network/utils.h"

using namespace std;

void usage(const char *cmd) {
    cout << "usage: " << cmd << " <sender ip>" << " <target ip>" << endl;
    cout << "example: " << cmd << " 192.168.0.1 192.168.0.101" << endl;
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        usage(argv[0]);
        return -1;
    }
    char *dev = argv[1];
    arp_spoof(dev, argv[2], argv[3]);
    return 0;
}