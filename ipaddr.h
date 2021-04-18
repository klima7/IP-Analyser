#ifndef IPANALYSER_IPADDR_H
#define IPANALYSER_IPADDR_H

#include <string>
#include <stdexcept>
#include "ipdata.h"

class IpAddr: public IpData {
    friend std::ostream& operator<<(std::ostream &os, const IpAddr &address);
public:
    static const int OCTET_MIN_VAL = 0;
    static const int OCTET_MAX_VAL = 255;

    IpAddr(const std::string &addr = "0.0.0.0");
    IpAddr(const IpData &data): IpData(data) {}
private:
    void validate_roughly(const std::string &address);
    void init_from_string(const std::string &address);
};

#endif
