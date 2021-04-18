#ifndef IPANALYSER_IPCOMPOUNDADDR_H
#define IPANALYSER_IPCOMPOUNDADDR_H

#include <string>
#include "IpAddr.h"
#include "IpMask.h"

class IpCompoundAddr: public IpAddr {
public:
    IpCompoundAddr(const std::string &addr="0.0.0.0", unsigned int length=0);
    IpCompoundAddr(const IpData &addrData, const IpData &maskData);
    static IpCompoundAddr from_text(const std::string &addr);
    IpMask mask() const;
    IpCompoundAddr network_addr() const;
    IpAddr broadcast_addr() const;
    IpAddr first_host_addr() const;
    IpAddr last_host_addr() const;
    unsigned int hosts_count() const;
private:
    IpMask _mask;
};

std::istream& operator>>(std::istream &is, IpCompoundAddr &address);
std::ostream& operator<<(std::ostream &os, const IpCompoundAddr &address);

#endif