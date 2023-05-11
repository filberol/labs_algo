#include <iostream>
using namespace std;

int main() {
    size_t n; size_t k;
    cin >> n; cin >> k;
    if (n + k < 4 || k > n) {
        return 0;
    }
    int cords[n];
    for (size_t i = 0; i < n; i++) {
        cin >> cords[i];
    }

    int left_b = 1;
    int right_b = cords[n-1] - cords[0];

    while (right_b - left_b > 1) {
        int new_dist = (left_b + right_b) / 2;
        int cow_co = 1;
        int prev_cord = cords[0];
        for (int i = 1; i < n; i++) {
            if (cords[i] - prev_cord >= new_dist) {
                cow_co++;
                prev_cord = cords[i];
                if (cow_co == k) {
                    break;
                }
            }
        }
        if (cow_co == k) {
            left_b = new_dist;
        } else {
            right_b = new_dist;
        }
    }
    cout << left_b;
    return 0;
}