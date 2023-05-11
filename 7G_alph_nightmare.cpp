#include <iostream>
#include <algorithm>
#include <cstdint>
#include <vector>
#include <set>
using namespace std;

int main() {
    string input;
    cin >> input;
    uint32_t weights[26];
    basic_string<char> temp;
//  Load weights
    for (uint32_t & weight : weights) {
        cin >> temp;
        weight = stoul(temp);
    }
//  Count times
    size_t counts[26] = {0};
    for (char ch : input) {
        counts[ch - 'a']++;
    }
//  Sorted unique char pairs to insert
    set<char> uniq_char_pairs;
    for (auto el: input) {
        if (counts[el - 'a'] >= 2 && weights[el - 'a'] > 0) {
            uniq_char_pairs.insert(el);
        }
    }
    vector<char> un_ch_pa(uniq_char_pairs.begin(), uniq_char_pairs.end());
    sort(un_ch_pa.begin(), un_ch_pa.end(),
         [&weights] (const char a, const char b) -> bool {return weights[a - 'a'] > weights[b - 'a'];}
    );
//    for (auto el: un_ch_pa) {
//        cout << el;
//    }
//    cout << "\n";

    size_t left = 0;
    size_t right = input.size() - 1;
    for (char el : un_ch_pa) {
        swap(input[input.find(el)], input[right]);
//        cout << input << "\n";
        swap(input[input.find(el)], input[left]);
//        cout << input << "\n";
        left++;
        right--;
    }

    cout << input;

    return 0;
}
