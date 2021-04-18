#ifndef IPANALYSER_IPDATA_H
#define IPANALYSER_IPDATA_H

#include <cstdint>

class IpData {
public:
    IpData(const IpData &ipData);
    IpData operator&(const IpData &other) const;
    IpData operator|(const IpData &other) const;
    IpData operator~() const;
    IpData operator+(int num) const;
    IpData operator-(int num) const;
protected:
    IpData(uint32_t data=0);
    uint32_t data;
};

#endif