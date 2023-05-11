#include <iostream>
using namespace std;

int main() {
    int bacteria_start, multiplier, use_count, max_space, day_count; // a b c d k
    cin >> bacteria_start, cin >> multiplier, cin >> use_count, cin >> max_space, cin >> day_count;
    for (int day_n = 1; day_n <= day_count; day_n++) {
        int bacteria = bacteria_start;
        bacteria *= multiplier;
        bacteria -= use_count;
        if (bacteria <= 0) {
            cout << 0;
            return 0;
        }
        if (bacteria > max_space) {
            bacteria = max_space;
        }
        // If bacteria count is constant no reason to calculate further
        if (bacteria == bacteria_start) {
            cout << bacteria;
            return 0;
        }
        bacteria_start = bacteria;
    }
    cout << bacteria_start;
    return 0;
}
