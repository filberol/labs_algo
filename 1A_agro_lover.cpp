#include <iostream>
using namespace std;

int main() {
    // Read Array
    int count;
    cin >> count;
    int nums[count];
    for (int i = 0; i < count; i++) {
        cin >> nums[i];
    }



    // Check for short arrays
    if (count < 3) {
        cout << 1 << " " << count;
        return 0;
    }

    // Start iteration
    int start = 0;
    int stop = 2;
    int maxStart = 0;
    int maxStop = 2;
    int maxLength = 0;

    while (stop < count) {
        // Many numbers can only appear at the end
        if (nums[stop] == nums[stop-1] && nums[stop-1] == nums[stop-2]) {
            // If many nums right at the end break manually
            if (stop + 1 == count) break;
            // Else shorten range to 3, including 2 prev without first
            start = stop - 1;
        } else {
            // Remembering max range
            int length = stop - start;
            if (length > maxLength) {
                maxStart = start;
                maxStop = stop;
                maxLength = length;
            }
        }
        //else checking for max length and widing from end
        ++stop;
    }

    cout << maxStart + 1 << " " << maxStop + 1;

    return 0;
}
