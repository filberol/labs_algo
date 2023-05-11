#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct string_int_greater
{
    inline bool operator() (const string& str1, const string& str2)
    {
        string f_pair = str1 + str2;
        string s_pair = str2 + str1;
        return f_pair > s_pair;
    }
};

int main() {
    vector<string> parts;
    string input;
    while (cin >> input) {
        parts.push_back(input);
    }
    sort(parts.begin(), parts.end(), string_int_greater());
    for (const auto & part : parts) {
        cout << part;
    }
    return 0;
}
