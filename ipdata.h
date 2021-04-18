#ifndef IPANALYSER_IPDATA_H
#define IPANALYSER_IPDATA_H

#include <cstdint>

class IpData {
public:
    static const int OCTETS_COUNT = 4;
    static const int OCTET_SIZE = 8;
    static const int BITS_COUNT = OCTETS_COUNT * OCTET_SIZE;

    IpData(): IpData(0) {};
    IpData(const IpData &ipData);

    uint8_t get_octet(unsigned int octet) const;
    void set_octet(unsigned int octet, uint8_t value);
    bool get_bit(unsigned int bit) const;
    void set_bit(unsigned int bit, bool value);

    IpData operator&(const IpData &other) const;
    IpData operator|(const IpData &other) const;
    IpData operator~() const;
private:
    union {
        uint32_t full;
        uint8_t octets[4]; // octet 0 - most significant
    } data;

    IpData(uint32_t data);
    static void validate_octet(unsigned int octet);
    static void validate_bit(unsigned int bit);
};

#endif