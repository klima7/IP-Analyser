#ifndef IPANALYSER_IPMASK_H
#define IPANALYSER_IPMASK_H

#include <iostream>
#include "ipdata.h"

class IpMask: public IpData {
public:
    IpMask(unsigned int length = 0);
    IpMask(const IpData &data);
    unsigned int length() const;
private:
    static uint32_t cvt_length2binary(unsigned int length);
    static void validate_binmask(uint32_t mask);
};

std::ostream& operator<<(std::ostream &os, const IpMask &address);

#endif
