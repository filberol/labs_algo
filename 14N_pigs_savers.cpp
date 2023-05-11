#include <iostream>
#include <vector>
using namespace std;

int open_all_inner(const vector<vector<int>>& graph, vector<bool>& opened, vector<bool>& inner_opens, int j_opened) {
    inner_opens[j_opened] = true;
    for (int key_in : graph[j_opened]) {
        if (opened[key_in]) return 0;
        if (inner_opens[key_in]) return 1;
        return open_all_inner(graph, opened, inner_opens, key_in);
    }
}

int main() {
    int pigs;
    cin >> pigs;
    vector<vector<int>> keys;
    vector<bool> opened;

    int index;
    keys.resize(pigs);
    opened.resize(pigs, false);
    for (int i = 0; i < pigs; i++) {
        cin >> index;
        keys[i].push_back(index - 1);
    }

    int smashed_count = 0;
    vector<bool> inner_opens;
    for (int pig_i = 0; pig_i < pigs; pig_i++) {
        inner_opens.clear();
        inner_opens.resize(pigs, false);
        smashed_count += open_all_inner(keys, opened, inner_opens, pig_i);
        for (int i = 0; i < inner_opens.size(); i++) {
            if (inner_opens[i]) opened[i] = true;
        }
    }

    cout << smashed_count;
    return 0;
}