#include <iostream>
#include <stack>
using namespace std;

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