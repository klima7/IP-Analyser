#ifndef IPANALYSER_MAIN_H
#define IPANALYSER_MAIN_H

#include <iostream>
#include "ipcompaddr.h"

#define QUIT_INPUT "q"
#define FMT_WIDTH 25
#define DEFAULT_FILENAME "output.txt"

IpCompoundAddr ask_ip();
void write_results(std::ostream &os, const IpCompoundAddr &address);
bool ask_continue();

#endif
