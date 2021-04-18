#ifndef IPANALYSER_IPDATA_H
#define IPANALYSER_IPDATA_H

#include <cstdint>

class IpData {
public:
    IpData(): IpData(0) {};
    IpData(const IpData &ipData);
    IpData operator&(const IpData &other) const;
    IpData operator|(const IpData &other) const;
    IpData operator~() const;
private:
    IpData(uint32_t data);
    uint32_t data;
};

#endif