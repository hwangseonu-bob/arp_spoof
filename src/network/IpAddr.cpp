#include <regex>
#include "../../includes/network/HwAddr.h"

using namespace std;

namespace network {
    HwAddr::HwAddr(const string &mac) {
        regex reg("^(([0-9A-Fa-f]{2})[:-]){5}([0-9A-Fa-f]{2})$");
        string fmt = "%02x%02x%02x%02x%02x%02x";
        if (regex_match(mac, reg)) {
            if (mac.find(':') != string::npos) fmt = "%02x:%02x:%02x:%02x:%02x:%02x";
            if (mac.find('-') != string::npos) fmt = "%02x-%02x-%02x-%02x-%02x-%02x";
        }
        sscanf(mac.c_str(), fmt.c_str(), &addr[0], &addr[1], &addr[2], &addr[3], &addr[4], &addr[5]);
    }

    string HwAddr::to_string() const {
        char str[18];
        sprintf(str, "%02x:%02x:%02x:%02x:%02x:%02x", addr[0], addr[1], addr[2], addr[3], addr[4], addr[5]);
        return string(str);
    }

    bytes HwAddr::to_bytes() const {
        return bytes(addr.begin(), addr.begin() + size);
    }

    std::ostream& operator<<(std::ostream& o, const HwAddr& mac) {
        return o << mac.to_string(); 
    }
}

