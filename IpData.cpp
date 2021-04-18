#include "IpData.h"

IpData::IpData(uint32_t data) {
    this->data = data;
}

IpData::IpData(const IpData &ipData) {
    this->data = ipData.data;
}

IpData IpData::operator&(const IpData &other) const {
    return IpData(data & other.data);
}

IpData IpData::operator|(const IpData &other) const {
    return IpData(data | other.data);
}

IpData IpData::operator~() const {
    return IpData(~data);
}

