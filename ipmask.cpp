#include <iostream>
#include "ipmask.h"
#include "ipexcept.h"

using namespace std;

IpMask::IpMask(unsigned int length) {
    if(length > BITS_COUNT)
        throw IpException("Mask length is out of bounds");
    for(unsigned int i=0; i<length; i++)
        set_bit(BITS_COUNT - 1 - i, true);
}

IpMask::IpMask(const IpData &data): IpData(data) {
    // Check whether provided mask is valid
    bool prev_bit = false;
    for(int i=0; i<BITS_COUNT; i++) {
        bool this_bit = get_bit(i);
        if(!this_bit & prev_bit)
            throw IpException("Provided mask has invalid format");
        prev_bit = this_bit;
    }
}

unsigned int IpMask::get_length() const {
    unsigned int length = 0;
    for(int i=0; i<BITS_COUNT; i++) {
        bool set = get_bit(BITS_COUNT-1-i);
        if(set) length++;
        else return length;
    }
    return length;
}

ostream& operator<<(std::ostream &os, const IpMask &address) {
    os << "/" << address.get_length();
    return os;
}