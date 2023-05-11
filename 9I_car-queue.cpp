#include <iostream>
#include <queue>
#include <set>
using namespace std;

int main() {
    int types, cache_size, count;
    cin >> types; cin >> cache_size; cin >> count;
    vector<int> orders;
    vector<queue<uint32_t>> positions(types);
    int temp;
    for (uint32_t ind = 0; ind < count; ind++) {
        cin >> temp;
        temp--;
        orders.push_back(temp);
        positions[temp].push(ind);
    }

    size_t cache_op = 0;
    set<int> cache;
    priority_queue<pair<int, int>> last_car_pos_queue;
    for (int order_n = 0; order_n < count; order_n++) {
        int order = orders.at(order_n);
        positions[order].pop();

        if (cache.find(order) == cache.end()) {
            if (cache.size() >= cache_size) {
                cache.erase(last_car_pos_queue.top().second);
                last_car_pos_queue.pop();
            }
            cache_op++;
            cache.insert(order);
        }

        if (positions[order].empty()) {
            last_car_pos_queue.emplace(600000, order);
        } else {
            last_car_pos_queue.emplace(positions[order].front(), order);
        }
    }
    cout << cache_op;
    return 0;
}