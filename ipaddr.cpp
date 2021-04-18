#include <sstream>
#include <iostream>
#include "ipaddr.h"
#include "ipexcept.h"

using namespace std;

IpAddr::IpAddr(const string &address) {
    validate_roughly(address);
    uint8_t octets[4];
    cvt_str2octets(address, octets);
    data = cvt_octets2binary(octets);
}

void IpAddr::validate_roughly(const string &address) {
    if(address.length() == 0)
        throw IpException("Address is empty");

    int dotsCount = 0;
    for(char c : address) {
        if(c == '.')
            dotsCount++;
        else if(!isdigit(c))
            throw IpException("Address contains invalid character");
    }

    if(dotsCount != 3)
        throw IpException("Address contains invalid number of octets");
}

void IpAddr::cvt_str2octets(const string &address, uint8_t *octets) {
    int octetStart = 0;
    for(int i = 0; i < 4; i++) {
        if(address.at(octetStart) == '.')
            throw IpException("Address contains empty octet");

        int octetEnd = address.find('.', octetStart + 1);
        if(octetEnd == string::npos)
            octetEnd = address.length();

        string octet = string(address, octetStart, octetEnd-octetStart);
        if(octet.length() > 1 && octet[0] == '0')
            throw IpException("Address contains octet starting with zero");

        int numeralOctet = stoi(octet);
        if(numeralOctet < 0 || numeralOctet > 255)
            throw IpException("Value of one of the octets is out of bounds");

        octets[i] = (uint8_t)numeralOctet;
        octetStart = octetEnd + 1;
    }
}

uint32_t IpAddr::cvt_octets2binary(uint8_t *octets) {
    uint32_t result = 0;
    for(int i=0; i<4; i++) {
        result |= octets[3 - i] << i * 8;
    }
    return result;
}

void IpAddr::cvt_binary2octets(const uint32_t binary, uint8_t *octets) {
    uint32_t mask = 255;
    for(int i=0; i<4; i++) {
        uint32_t octet = (binary & mask << (i * 8)) >> i*8;
        octets[3-i] = octet;
    }
}

ostream& operator<<(ostream &os, const IpAddr &address) {
    uint8_t octets[4];
    IpAddr::cvt_binary2octets(address.data, octets);
    for(int i=0; i<4; i++) {
        os << (int)octets[i];
        if(i!=3) os << ".";
    }
    return os;
}