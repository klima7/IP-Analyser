#ifndef IPANALYSER_IPADDR_H
#define IPANALYSER_IPADDR_H

#include <string>
#include <stdexcept>
#include "IpData.h"

class IpAddr: public IpData {
    friend std::ostream& operator<<(std::ostream &os, const IpAddr &address);
public:
    class InvalidAddrException;
    IpAddr(const std::string &addr = "0.0.0.0");
    IpAddr(const IpData &data): IpData(data) {}
private:
    static void validate_roughly(const std::string &address);
    static void cvt_str2octets(const std::string &address, uint8_t *octets);
    static void cvt_binary2octets(const uint32_t binary, uint8_t *octets);
    static uint32_t cvt_octets2binary(uint8_t *octets);
    std::string addrstr() const;
};

class IpAddr::InvalidAddrException : public std::invalid_argument {
public:
    InvalidAddrException(const char *msg=""): invalid_argument(msg) {};
};

#endif
