/*
 * Author : Lukasz Klimkiewicz
 * Mail   : ukasz.klimkiewicz@gmail.com
 */

#include <iostream>
#include <iomanip>
#include "ipcompaddr.h"
#include "ipexcept.h"

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
        }
        catch(IpException e) {
            cout << "Invalid IP: " << e.what() << endl;
            cout << "Enter IP again >>";
            continue;
        }

        return address;
    }
}

void show_result(IpCompoundAddr &address) {
    cout << setw(FMT_WIDTH) << left << "Network address" << ": " << address.get_network_addr() << endl;
    cout << setw(FMT_WIDTH) << left << "Broadcast address" << ": " << address.get_broadcast_addr() << endl;
    cout << setw(FMT_WIDTH) << left << "Usable hosts addresses" << ": ";
    if(address.get_hosts_count() > 0) cout << address.get_first_host_addr() << " - " << address.get_last_host_addr() << endl;
    else cout << "NaN" << endl;
    cout << setw(FMT_WIDTH) << left << "Usable hosts addresses" << ": " << address.get_hosts_count() << endl;
}

bool ask_continue() {
    cout << "Press '" << QUIT_INPUT << "' if you want to quit, hit enter otherwise" << endl;
    string input;
    getline(cin, input);
    return input != QUIT_INPUT;
}
