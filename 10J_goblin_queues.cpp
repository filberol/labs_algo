#include <iostream>
#include <deque>

using namespace std;

int main() {
    int actions_count;
    cin >> actions_count;

    deque<int> first_half;
    deque<int> second_half;

    for (int action_n = 0; action_n < actions_count; action_n++) {
        char op;
        cin >> op;
        if (op == '-') {
            cout << first_half.front() << "\n";
            first_half.pop_front();
        } else {
            int goblin_n;
            cin >> goblin_n;
//            cout << goblin_n << "\n";
            if (op == '+') {
                second_half.push_back(goblin_n);
            } else {
                second_half.push_front(goblin_n);
            }
        }

        size_t diff = first_half.size() - second_half.size();
        if (diff == -1) { // add one in end or middle
            first_half.push_back(second_half.front());
            second_half.pop_front();
        }
    }
    return 0;
}
