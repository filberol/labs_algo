#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int max_colors = 1000;

bool is_bipart(vector<vector<int>>& connections) {
    queue<int> to_color;
    vector<int> colors(connections.size(), 0);

    for (int i = 0; i < connections.size(); i++) {
        // Skip if already colored
        if (colors.at(i)) continue;
        // Paint blank
        colors.at(i) = 1;
        to_color.push(i);
        // Empty queue until all connected coloured
        while (!to_color.empty()) {
            int temp = to_color.front();
            for (int connection: connections.at(temp)) {
                if (!colors.at(connection)){
                    // Paint in opposite
                    colors.at(connection) = -colors.at(temp);
                    to_color.push(connection);
                }
                // One breaks
                else if (colors.at(connection) == colors.at(temp))
                    return false;
            }
            to_color.pop();
        }
    }
    return true;
}

int main() {
    int students_n, pairs;
    cin >> students_n >> pairs;

    // Connections list
    vector<vector<int>> connections;
    connections.resize(students_n);
    for (int i = 0; i < pairs; i++) {
        int f, s;
        cin >> f >> s;
        f--, s--;
        connections.at(f).push_back(s);
        connections.at(s).push_back(f);
    }

    if (is_bipart(connections)) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
    }

    return 0;
}

