#include <iostream>
#include <stack>
using namespace std;

//int main() {
//    string positions;
//    vector<char> alphabet;
//    // Read and transform string
//    cin >> positions;
//    if (positions.length() > 100000) return 0;
//    vector<char> pos;
//    for (char position: positions) {
//        if (isupper(position)) {
//            //cout << "Pushed " << position << "\n";
//            alphabet.push_back(tolower(position));
//        }
//        pos.push_back(tolower(position));
//    }
//    //cout << string(alphabet.begin(), alphabet.end()) << "\n";
//
//    size_t oldLength = 100001;
//    size_t length = positions.length();
//    vector<int> solution;
//    while (length < oldLength && length > 0) {
//        oldLength = length;
//        for (int i = 0; i < pos.size() - 1; i++) {
//            if (pos[i] == pos[i + 1]) {
//                int dis = distance(alphabet.begin(), find(alphabet.begin(), alphabet.end(),pos[i]));
//                //cout << "found " << pos[i] << "\n";
//                solution.push_back(dis);
//                length -= 2;
//                if (length == 0) {
//                    pos.clear();
//                    break;
//                }
//                pos.erase(pos.begin() + i, pos.begin() + i + 2);
//                i -= 1;
//            }
//        }
//    }
//    if (pos.empty()) {
//        cout << "Possible\n";
//        for (int i : solution) {
//            cout << i+1 << " ";
//        }
//
//    } else {
//        cout << "Impossible\n";
//    }
//    return 0;
//}

int main() {
    string input;
    stack<int> cagesIndex;
    stack<int> animalNumber;
    //Read input
    cin >> input;
    int solution[input.size() / 2];
    int cageCount = 0; // count of animals/cages
    int animalCount = 0;
    stack<char> uncaught; // stack for not closed pairs

    for (char el : input) {
        // Add number of animal or index of cage
        // to parallel stacks,
        if (isupper(el)) {
            cagesIndex.push(cageCount);
            cageCount++;
        } else {
            animalCount++;
            animalNumber.push(animalCount);
        }

        // If pair cannot be closed add el to stack
        if (uncaught.empty() || el == uncaught.top()) {
            uncaught.push(el);
        } else {
            // if current el closes pair(lies on stack top)
            if (tolower(el) == tolower(uncaught.top())) {
                solution[cagesIndex.top()] = animalNumber.top();
                cagesIndex.pop();
                animalNumber.pop();
                uncaught.pop();
            } else {
                uncaught.push(el);
            }
        }
    }

    if (uncaught.empty()) {
        cout << "Possible\n";
        for (int i : solution) {
            cout << i << ' ';
        }
    } else {
        cout << "Impossible\n";
    }
}