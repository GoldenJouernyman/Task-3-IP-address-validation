#include <iostream>
using namespace std;

static bool check_address_part(string addressPart) {
    int i = 0;
    for (i; i < addressPart.length(); i++) {
        if (addressPart[i] < '0' || addressPart[i] > '9') return false;
    }
    if (addressPart.length() < 1 || addressPart.length() > 3) return false;
    if (addressPart[0] == '0' && addressPart.length() > 1) return false;
    int number = 0;
    if (i == 1) {
        number = addressPart[0] - '0';
    } else if (i == 2) {
        number = (10 * (addressPart[0] - '0')) + (addressPart[1] - '0');
    } else if (i == 3) {
        number = (100 * (addressPart[0] - '0')) + (10 * (addressPart[1] - '0')) + (addressPart[2] - '0');
    }
    if (number > 255) return false;
    return true;
}

static string get_address_part(string ip,int octet) {
    int count = octet - 1;
    int count1 = 0;
    int count2 = 0;
    string addressPart;
    for (int i = 0; i < ip.length(); i++) {
        if (octet == 0) {
            if (count != octet && ip[i] != '.') addressPart += ip[i];
            if (ip[i] == '.') return addressPart;
        } else if (octet == 1) {
            if (count == octet && ip[i] != '.') addressPart += ip[i];
            if (ip[i] == '.') count++;
            if (count > octet) return addressPart;
        } else if (octet == 2) {
            if (count1 == octet && ip[i] != '.') addressPart += ip[i];
            if (ip[i] == '.') count1++;
            if (count1 > octet) return addressPart;
        } else if (octet == 3) {
            if (count2 == octet && ip[i] != '.') addressPart += ip[i];
            if (ip[i] == '.' && count < 3) count2++;
        }
    }
    return addressPart;
}

int main() {
    int point = 0;
    string ip;
    string octet;
    cout << "Enter the IP-address to verify it -->\n\n";
    cin >> ip;

    for (int i = 0; i < ip.length(); i++) {
        if (ip[i] == '.') ++point;
        if (point > 3) {
            cout << "\nInvalid\n";
            return 0;
        }
    }

    for (int i = 0; i < 4; i++) {
        if (check_address_part(get_address_part(ip, i)) == false) break;
        if (i == 3) {
            cout << "\nValid\n";
            return 0;
        }
    }

    cout << "\nInvalid\n";

    return 0;
}
