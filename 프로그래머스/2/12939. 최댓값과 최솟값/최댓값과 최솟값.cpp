#include <string>
#include <sstream>
#include <limits>

using namespace std;

string solution(string s) {
    stringstream ss(s);
    int num;
    int mx = numeric_limits<int>::min();
    int mn = numeric_limits<int>::max();

    while (ss >> num) {
        if (num > mx) mx = num;
        if (num < mn) mn = num;
    }

    return to_string(mn) + " " + to_string(mx);
}
