#include <iostream>
#include "IpMask.h"
#include "IpException.h"

using namespace std;

IpMask::IpMask(unsigned int length) {
    data = cvt_length2binary(length);
    validate_binmask(this->data);
}

IpMask::IpMask(const IpData &data): IpData(data) {
    validate_binmask(this->data);
}

uint32_t IpMask::cvt_length2binary(unsigned int length) {
    if(length > 32)
        throw IpException("Mask length is out of bounds");
    if(length == 0) return 0;
    uint32_t mask = 0;
    for(uint32_t one=1<<(32-length); one; one<<=1)
        mask |= one;
    return mask;
}

unsigned int IpMask::length() const {
    unsigned int length = 0;
    uint32_t one = 1 << 31;
    while(one & data) {
        length++;
        one >>= 1;
    }
    return length;
}

void IpMask::validate_binmask(uint32_t mask) {
    bool prev_set = false;
    for(uint32_t one = 1; one>0; one<<=1) {
        bool this_set = mask & one;
        if(!this_set & prev_set)
            throw IpException("Provided get_mask has invalid format");
        prev_set = this_set;
    }
}

ostream& operator<<(std::ostream &os, const IpMask &address) {
    os << "/" << address.length();
    return os;
}