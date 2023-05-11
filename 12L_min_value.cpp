#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

int find_min(vector<int> *tree, int left_b, int right_b, int node_i, int node_fr, int node_to) {
    if (left_b > node_to || right_b < node_fr) return 100001;
    if (node_fr >= left_b && node_to <= right_b) return tree->at(node_i);
    int split_node = (node_fr + node_to) / 2;
    int min_left = find_min(tree, left_b, right_b, 2 * node_i + 1, node_fr, split_node);
    int min_right = find_min(tree, left_b, right_b, 2 * node_i + 2, split_node + 1, node_to);
    return min(min_left, min_right);
}

int main() {
    int nums_c, window;
    cin >> nums_c; cin >> window;

    // Read nums
    vector<int> reducing;
    int temp;
    for (int ind = 0; ind < nums_c; ind++) {
        cin >> temp;
        reducing.push_back(temp);
    }

    // Calc tree array
    int array_size = (int)pow(2, ceil(log2(nums_c)));
    int tree_size = 0;
    for (int dyn_size = array_size; dyn_size >= 1; dyn_size /= 2) {
        tree_size += dyn_size;
    }

    // Create tree array and fill it with 0 lvl
    vector<int> reduced(tree_size);
    int ptr = 0;
    for (int i = tree_size - array_size; i < tree_size; i++) {
        if (ptr >= nums_c) {
            reduced.at(i) = 100001;
        } else {
            reduced.at(i) = reducing.at(ptr);
            ptr++;
        }
    }

    // Fill tree elements
    int lvl_ind = tree_size - array_size;
    int el_ind = lvl_ind;
    int dyn_size = tree_size;
    while (el_ind > 0) {
        int node_ind = (el_ind - 1) / 2;
        reduced.at(node_ind) = std::min(reduced.at(el_ind), reduced.at(el_ind + 1));
        if (el_ind + 2 >= dyn_size) {
            dyn_size /= 2;
            el_ind = (lvl_ind - 1) / 2;
            lvl_ind = el_ind;
        } else {
            el_ind += 2;
        }
    }

    // Print mins
    int start = tree_size - array_size;
    int left = 0;
    int right = window;
    for (int i = 0; i < nums_c - window + 1; i++) {
        cout << find_min(&reduced, tree_size - array_size + left, start + right - 1, 0, start, tree_size - 1) << " ";
        left++;
        right++;
    }

    return 0;
}


