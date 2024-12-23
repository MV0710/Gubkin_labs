#include <iostream>
#include <string>
#include "Logging.h"

using namespace std;

inline string get_str() {
    string str;
    cin >> ws;
    getline(cin, str);
    return str;
}
template <typename T>
T get_correct_value(T min, T max) {
    T value;
    cin >> value;
    while (cin.fail() || cin.peek() != '\n' || value < min || value > max) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "ERROR: Enter a valid value: ";
        cin >> value;
    }
    return value;
}