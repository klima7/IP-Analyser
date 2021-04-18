#include <algorithm>
#include "IpCompoundAddr.h"

using namespace std;

IpCompoundAddr::IpCompoundAddr(const std::string &addr, unsigned int length): IpAddr(addr) {
    _mask = IpMask(length);
}

IpCompoundAddr::IpCompoundAddr(const IpData &addrData, const IpData &maskData): IpAddr(addrData) {
    _mask = IpMask(maskData);
}

IpCompoundAddr IpCompoundAddr::from_text(const std::string &addr) {
    int slashes_count = count(addr.begin(), addr.end(), '/');
    if(slashes_count != 1)
        throw InvalidAddrException("Unable to determine ip and mask parts");

    int slash_pos = addr.find('/');
    string address = addr.substr(0, slash_pos);
    string length_str = addr.substr(slash_pos+1, addr.length()-slash_pos-1);

    size_t valid_characters;
    int length;
    try {
        length = stoi(length_str, &valid_characters);
    } catch(invalid_argument e) {
        throw IpMask::InvalidMaskException("Mask is not a number");
    }

    if(valid_characters != length_str.length())
        throw IpMask::InvalidMaskException("Mask contains invalid characters");

    return IpCompoundAddr(address, length);
}

IpMask IpCompoundAddr::mask() const {
    return _mask;
}

IpCompoundAddr IpCompoundAddr::network_addr() const {
    return IpCompoundAddr(*this & mask(), mask());
}

IpAddr IpCompoundAddr::broadcast_addr() const {
    return IpAddr(network_addr() | ~mask());
}

IpAddr IpCompoundAddr::first_host_addr() const {
    return IpAddr(network_addr() + 1);
}

IpAddr IpCompoundAddr::last_host_addr() const {
    return IpAddr(broadcast_addr() - 1);
}

unsigned int IpCompoundAddr::hosts_count() const {
    unsigned int length = mask().length();
    if(length>31) return 0;
    unsigned int count = (1 << (32 - length)) - 2;
    return count;
}

ostream& operator<<(std::ostream &os, const IpCompoundAddr &address) {
    os << (IpAddr&)address << address.mask();
    return os;
}

std::istream& operator>>(std::istream &is, IpCompoundAddr &address) {
    string line;
    getline(is, line);
    address = IpCompoundAddr::from_text(line);
    return is;
}