#ifndef ARP_SENDER_IPADDR_H
#define ARP_SENDER_IPADDR_H

#include <cstdint>
#include <string>

using byte=uint8_t;

namespace network {
    class IpAddr {
    public:
        static const int size = 4;
        byte addr[size] {};
    public:
        IpAddr() = default;
        IpAddr(const IpAddr &ip) = default;
        explicit IpAddr(const byte ip[size]);
        explicit IpAddr(uint32_t ip);
        explicit IpAddr(const char *ip) noexcept(false);
        explicit IpAddr(const std::string &ip) noexcept(false);
    public:
        std::string to_string() const;
        void parse_string(const std::string &ip) noexcept(false);
    public:
        bool operator==(const IpAddr &ip);
        IpAddr &operator=(const std::string &ip);
    };
}

std::ostream &operator<<(std::ostream &o, const network::IpAddr &addr);

#endif //ARP_SENDER_IPADDR_H
