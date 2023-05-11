#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

int main() {
    int count;
    int every_free;
    cin >> count;
    cin >> every_free;
    vector<int> items;
    string temp;
    for (int i = 0; i < count; i++) {
        cin >> temp;
        items.push_back(stoi(temp));
    }
    size_t sum = accumulate(items.begin(), items.end(), 0);
    if (every_free > count) {
        cout << sum;
        return 0;
    }
    sort(items.begin(), items.end(), greater<int>());
    for (int ind = every_free - 1; ind < count; ind += every_free) {
        sum -= items[ind];
    }
    cout << sum;
    return 0;
}