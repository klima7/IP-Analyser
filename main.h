#ifndef IPANALYSER_MAIN_H
#define IPANALYSER_MAIN_H

#include <iostream>
#include "ipcompaddr.h"

#define QUIT_INPUT "e"
#define DEFAULT_FILENAME "output.txt"
#define THOUSANDS_SEPARATOR ","
#define FMT_WIDTH 25

IpCompoundAddr ask_ip();
void write_results(std::ostream &os, const IpCompoundAddr &address);
bool ask_continue();
std::string format_with_commas(unsigned int num);

#endif
