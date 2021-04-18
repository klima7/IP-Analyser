#ifndef IPANALYSER_IPEXCEPTION_H
#define IPANALYSER_IPEXCEPTION_H

#include <exception>
#include <string>

class IpException: std::exception {
public:
    IpException(const std::string message) {
        this->message = message;
    }
    const char * what() const noexcept override {
        return message.c_str();
    }
private:
    std::string message;
};


#endif
