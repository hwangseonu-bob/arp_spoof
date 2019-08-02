#include "network/utils.h"

int main(int argc, char *argv[]) {
    char *dev = argv[1];
    arp_spoof(dev, argv[2], argv[3]);
    return 0;
}