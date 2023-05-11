#include <iostream>
#include <vector>
#include <map>
using namespace std;

map<int, int> index_size_map;
multimap<int, int> size_index_map;

void emplace(int first, int second) {
    index_size_map.emplace(first, second);
    size_index_map.emplace(second, first);
}

void find_and_remove(const map<int, int>::iterator &pos) {
    auto in_size = size_index_map.find(pos->second);
    while (in_size->second != pos->first) in_size++;
    index_size_map.erase(pos);
    size_index_map.erase(in_size);
}

int main() {
    int regions, orders;
    cin >> regions >> orders;
    vector<pair<int, int>> history(orders);
    index_size_map.emplace(1, regions);
    size_index_map.emplace(regions, 1);
    int order;
    for (int i = 0; i < orders; i++) {
        cin >> order;
        int index = 0;
        int size;
        if (order > 0) {
            auto to_take = size_index_map.lower_bound(order);
            if (to_take != size_index_map.end()) {
                index = to_take->second;
                index_size_map.erase(index);
                size = to_take->first - order;
                size_index_map.erase(to_take);
                if (size > 0) emplace(index + order, size);
            } else {
                index = -1;
            }
            cout << index << "\n";
        } else {
            int h_index = history.at(-order - 1).second;
            int h_size = history.at(-order - 1).first;
            if (h_index == -1) continue;
            else {
                auto next = index_size_map.lower_bound(h_index);
                auto previous = next;
                if (next == index_size_map.begin()) {
                    previous = index_size_map.end();
                } else {
                    previous = prev(next);
                }

                // Concat free segments
                if (next != index_size_map.end() && next->first == h_index + h_size) {
                    // Concat with both
                    if (previous != index_size_map.end() && previous->first + previous->second == h_index) {
                        index = previous->first;
                        size = previous->second + next->second;
                        find_and_remove(previous); find_and_remove(next);
                        emplace(index, size + h_size);
                    // Concat with next
                    } else {
                        size = next->second;
                        find_and_remove(next);
                        emplace(h_index, size + h_size);
                    }
                } else {
                    // Concat with previous
                    if (previous != index_size_map.end() && previous->first + previous->second == h_index) {
                        index = previous->first;
                        size = previous->second;
                        find_and_remove(previous);
                        emplace(index, size + h_size);
                    } else {
                    // Insert as is
                        emplace(h_index, h_size);
                    }
                }
            }
        }
        // Remember last op
        history[i] = {order, index};
    }

    return 0;
}