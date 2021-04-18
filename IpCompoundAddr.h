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
    IpMask get_mask() const;
    IpCompoundAddr get_network_addr() const;
    IpAddr get_broadcast_addr() const;
    IpAddr get_first_host_addr() const;
    IpAddr get_last_host_addr() const;
    unsigned int get_hosts_count() const;
private:
    IpMask mask;
};

std::istream& operator>>(std::istream &is, IpCompoundAddr &address);
std::ostream& operator<<(std::ostream &os, const IpCompoundAddr &address);

#endif