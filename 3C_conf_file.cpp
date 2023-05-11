#include <iostream>
#include <stack>
#include <unordered_map>
#include <vector>

using namespace std;

int main() {
    unordered_map<string, stack<int>> variables;
    stack<vector<string>> changes;
    vector<string> curChanges;
    string line;
    while (getline(cin, line)) {
        if (line == "{") {
            changes.push(curChanges);
            curChanges = vector<string>();
        } else if (line == "}") {
            for(const string& el: curChanges) {
                variables[el].pop();
            }
            curChanges = changes.top();
            changes.pop();
        } else {
            string left = line.substr(0, line.find('='));
            size_t ind = line.find('=') + 1;
            size_t len = line.size() - ind;
            string right = line.substr(ind, len);
            if (variables.find(left) == variables.end()) {
                variables.insert( {left, stack<int>({0})} );
            }
            if ((right.find_first_not_of( "-0123456789" ) == string::npos)) {
                curChanges.push_back(left);
                variables[left].push(stoi(right));
            } else if (left == right) {
                cout << variables[left].top() << "\n";
            } else {
                if (variables.find(right) == variables.end()) {
                    variables.insert( {right, stack<int>({0})} );
                }
                // Find element with layer less or equal than current (first guaranteed)
                int val = variables[right].top();
                variables[left].push(val);
                curChanges.push_back(left);
                cout << val << "\n";
            }
        }
    }
    return 0;
}