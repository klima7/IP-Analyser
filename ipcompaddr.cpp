#include <algorithm>
#include "ipcompaddr.h"
#include "ipexcept.h"

using namespace std;

IpCompoundAddr::IpCompoundAddr(const std::string &addr, unsigned int length): IpAddr(addr) {
    mask = IpMask(length);
}

IpCompoundAddr::IpCompoundAddr(const IpData &addrData, const IpData &maskData): IpAddr(addrData) {
    mask = IpMask(maskData);
}

IpCompoundAddr IpCompoundAddr::from_text(const std::string &addr) {
    int slashes_count = count(addr.begin(), addr.end(), '/');
    if(slashes_count != 1)
        throw IpException("Unable to determine ip and get_mask parts");

    int slash_pos = addr.find('/');
    string address = addr.substr(0, slash_pos);
    string length_str = addr.substr(slash_pos+1, addr.length()-slash_pos-1);

    size_t valid_characters;
    int length;
    try {
        length = stoi(length_str, &valid_characters);
    } catch(invalid_argument &e) {
        throw IpException("Mask is not a number");
    }

    if(valid_characters != length_str.length())
        throw IpException("Mask contains invalid characters");

    return IpCompoundAddr(address, length);
}

IpMask IpCompoundAddr::get_mask() const {
    return mask;
}

IpCompoundAddr IpCompoundAddr::get_network_addr() const {
    return IpCompoundAddr(*this & get_mask(), get_mask());
}

IpAddr IpCompoundAddr::get_broadcast_addr() const {
    return IpAddr(get_network_addr() | ~get_mask());
}

IpAddr IpCompoundAddr::get_first_host_addr() const {
    if(get_hosts_count() == 0)
        throw IpException("No usable hosts address");
    return IpAddr(get_network_addr() | IpAddr("0.0.0.1"));
}

IpAddr IpCompoundAddr::get_last_host_addr() const {
    if(get_hosts_count() == 0)
        throw IpException("No usable hosts address");
    return IpAddr(get_broadcast_addr() & ~IpAddr("0.0.0.1"));
}

unsigned int IpCompoundAddr::get_hosts_count() const {
    int length = get_mask().get_length();
    int64_t hosts_count = (1ll << (BITS_COUNT - length));
    hosts_count -= 2;
    if(hosts_count < 0) hosts_count = 0;
    return hosts_count;
}

ostream& operator<<(std::ostream &os, const IpCompoundAddr &address) {
    os << (IpAddr&)address << address.get_mask();
    return os;
}

std::istream& operator>>(std::istream &is, IpCompoundAddr &address) {
    string line;
    getline(is, line);
    address = IpCompoundAddr::from_text(line);
    return is;
}