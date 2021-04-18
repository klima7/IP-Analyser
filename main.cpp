#include <iostream>
#include <iomanip>
#include "IpAddr.h"
#include "IpMask.h"
#include "IpCompoundAddr.h"

#define QUIT_INPUT "q"
#define FMT_WIDTH 25

using namespace std;

IpCompoundAddr ask_ip();
void show_result(IpCompoundAddr &address);
bool ask_continue();


int main() {
    IpCompoundAddr address;
    bool should_continue;

    do {
        address = ask_ip();
        show_result(address);
        should_continue = ask_continue();
    } while(should_continue);

    return 0;
}

IpCompoundAddr ask_ip() {
    IpCompoundAddr address;
    cout << "Enter IP >> ";

    while(true)
    {
        try {
            cin >> address;
        } catch(invalid_argument e) {
            cout << "Invalid IP: " << e.what() << endl;
            cout << "Enter IP again >>";
            continue;
        }

        return address;
    }
}

void show_result(IpCompoundAddr &address) {
    cout << setw(FMT_WIDTH) << left << "Network address" << ": " << address.network_addr() << endl;
    cout << setw(FMT_WIDTH) << left << "Broadcast address" << ": " << address.broadcast_addr() << endl;
    cout << setw(FMT_WIDTH) << left << "First host address" << ": " << address.first_host_addr() << endl;
    cout << setw(FMT_WIDTH) << left << "Last host address" << ": " << address.last_host_addr() << endl;
    cout << setw(FMT_WIDTH) << left << "Usable hosts count" << ": " << address.hosts_count() << endl;
}

bool ask_continue() {
    cout << "Press '" << QUIT_INPUT << "' if you want to quit, hit enter otherwise" << endl;
    string input;
    getline(cin, input);
    return input != QUIT_INPUT;
}

