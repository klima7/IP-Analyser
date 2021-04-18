#include <iostream>
#include "ipaddr.h"
#include "ipexcept.h"

using namespace std;

IpAddr::IpAddr(const string &address) {
    validate_roughly(address);
    init_from_string(address);
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

    if(dotsCount != OCTETS_COUNT - 1)
        throw IpException("Address contains invalid number of octets");
}

void IpAddr::init_from_string(const string &address) {
    int octetStart = 0;
    for(int i = 0; i < OCTETS_COUNT; i++) {
        if(address.at(octetStart) == '.')
            throw IpException("Address contains empty octet");

        int octetEnd = address.find('.', octetStart + 1);
        if(octetEnd == string::npos)
            octetEnd = address.length();

        string octet = string(address, octetStart, octetEnd-octetStart);
        if(octet.length() > 1 && octet[0] == '0')
            throw IpException("Address contains octet starting with zero");

        int numeralOctet = stoi(octet);
        if(numeralOctet < OCTET_MIN_VAL || numeralOctet > OCTET_MAX_VAL)
            throw IpException("Value of one of the octets is out of bounds");

        set_octet(i, numeralOctet);
        octetStart = octetEnd + 1;
    }
}

ostream& operator<<(ostream &os, const IpAddr &address) {
    for(int i=0; i<IpAddr::OCTETS_COUNT; i++) {
        os << (int)address.get_octet(i);
        if(i!=IpAddr::OCTETS_COUNT-1) os << ".";
    }
    return os;
}