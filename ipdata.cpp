#include <stdexcept>
#include "ipdata.h"

using namespace std;

IpData::IpData(uint32_t data) {
    this->data.full = data;
}

IpData::IpData(const IpData &ipData) {
    this->data = ipData.data;
}

uint8_t IpData::get_octet(unsigned int octet) const {
    validate_octet(octet);
    return data.octets[octet];
}

void IpData::set_octet(unsigned int octet, uint8_t value) {
    validate_octet(octet);
    data.octets[octet] = value;
}

bool IpData::get_bit(unsigned int bit) const {
    validate_bit(bit);
    int octet_no = 3 - bit / OCTET_SIZE;
    int bit_no = bit % OCTET_SIZE;
    bool set = data.octets[octet_no] & (1 << bit_no);
    return set;
}

void IpData::set_bit(unsigned int bit, bool value) {
    validate_bit(bit);
    int octet_no = 3 - bit / OCTET_SIZE;
    int bit_no = bit % OCTET_SIZE;
    uint8_t mask = 1 << bit_no;
    if(value) data.octets[octet_no] |= mask;
    else data.octets[octet_no] &= ~mask;
}

void IpData::validate_octet(unsigned int octet) {
    if(octet > IpData::OCTETS_COUNT)
        throw out_of_range("Octet number is out of range");
}

void IpData::validate_bit(unsigned int bit) {
    if(bit > IpData::BITS_COUNT)
        throw out_of_range("Bit number is out of range");
}

IpData IpData::operator&(const IpData &other) const {
    return IpData(data.full & other.data.full);
}

IpData IpData::operator|(const IpData &other) const {
    return IpData(data.full | other.data.full);
}

IpData IpData::operator~() const {
    return IpData(~data.full);
}

