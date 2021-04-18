/*
 * Author : Lukasz Klimkiewicz
 * Mail   : ukasz.klimkiewicz@gmail.com
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include "main.h"
#include "ipexcept.h"

using namespace std;

int main(int argc, char **argv) {
    string filename = DEFAULT_FILENAME;
    if(argc > 1)
        filename = argv[1];

    ofstream file;
    file.open(filename, std::ios_base::app);
    if(!file.is_open())
        cout << "Unable to open file, program will continue without writing to file";

    IpCompoundAddr address;
    bool should_continue;

    do {
        address = ask_ip();
        write_results(cout, address);

        if(file.is_open()) {
            write_results(file, address);
            file << endl;
            if (!file.good()) {
                cout << "Error occured while writing to file" << endl;
                file.clear();
            }
        }

        should_continue = ask_continue();
    } while(should_continue);

    if(file.is_open())
        file.close();
    return 0;
}

IpCompoundAddr ask_ip() {
    IpCompoundAddr address;
    cout << "Enter IP >> ";

    while(true)
    {
        try {
            cin >> address;
        }
        catch(IpException &e) {
            cout << "Invalid IP: " << e.what() << endl;
            cout << "Enter IP again >>";
            continue;
        }

        return address;
    }
}

void write_results(ostream &os, const IpCompoundAddr &address) {
    os << setw(FMT_WIDTH) << left << "1) Network address" << ": " << address.get_network_addr() << endl;

    os << setw(FMT_WIDTH) << left << "2) Hosts addresses" << ": ";
    if(address.get_hosts_count() > 0) os << address.get_first_host_addr() << " - " << address.get_last_host_addr() << endl;
    else os << "NaN" << endl;

    string hosts_count = format_with_commas(address.get_hosts_count());
    os << setw(FMT_WIDTH) << left << "3) Hosts count" << ": " << hosts_count << endl;

    os << setw(FMT_WIDTH) << left << "4) Broadcast address" << ": " << address.get_broadcast_addr() << endl;
}

bool ask_continue() {
    cout << "Press '" << QUIT_INPUT << "' if you want to quit, hit enter otherwise" << endl;
    string input;
    getline(cin, input);
    return input != QUIT_INPUT;
}

string format_with_commas(unsigned int num) {
    string str = to_string(num);
    int n = str.length() - 3;
    while (n > 0) {
        str.insert(n, ",");
        n -= 3;
    }
    return str;
}
