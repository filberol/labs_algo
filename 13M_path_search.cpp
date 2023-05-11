    #include <iostream>
    #include <vector>
    #include <algorithm>
    using namespace std;

    int get_time(char cell_t) {
        switch (cell_t) {
            case '#': return -1;
            case '.': return 1;
            case 'W': return 2;
            default:  return 0;
        }
    }

    class place {
        public: int index;
        public: int x;
        public: int y;
        public: place* upper;
        public: place* lower;
        public: place* left_s;
        public: place* right_s;
        public: int length;
        public: bool marked;

        place(int index, int x, int y, int length, bool marked) {
            this->index = index;
            this->x = x; this->y = y;
            this->upper = nullptr;
            this->lower = nullptr;
            this->left_s = nullptr;
            this->right_s = nullptr;
            this->length = length;
            this->marked = marked;
        }
    };

    int rows, columns;
    int x_0, y_0;
    int xf, yf;

    bool place_priority(place* a, place* b) {
        if (a->marked || b->marked) {
            return a->marked && !b->marked;
        } else {
            return a->length > b->length;
        }
    }

    void siftdown(place** heap, int n, int i) {
        int j = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        if (left < n && place_priority(heap[j], heap[left])) {
            j = left;
        }
        if (right < n && place_priority(heap[j], heap[right])) {
            j = right;
        }
        if (i != j) {
            swap(heap[i]->index, heap[j]->index);
            swap(heap[i], heap[j]);
            siftdown(heap, n, j);
        }
    }

    int parent(int i) { return (i - 1) / 2; }
    void siftup(place** heap, int i) {
        while (i > 0 && place_priority(heap[parent(i)], heap[i])) {
            swap(heap[i]->index, heap[parent(i)]->index);
            swap(heap[i], heap[parent(i)]);
            i = parent(i);
        }
    }

    int main() {
        cin >> rows >> columns;
        cin >> x_0 >> y_0;
        cin >> xf >> yf;
        x_0--, y_0--;
        xf--, yf--;

        int heap_c = 0;
        auto** heap_pl = new place*[1000000];

        vector<vector<char>> map;
        vector<vector<bool>> marked;
        string temp;
        for (int row = 0; row < rows; row++) {
            cin >> temp;
            map.push_back(vector<char> {});
            marked.push_back(vector<bool> {});
            for (int col = 0; col < columns; col++) {
                map.at(row).push_back(temp[col]);
                marked.at(row).push_back(false);
            }
        }

        place* start_place = nullptr;
        place* end_place = nullptr;
        for (int row = 0; row < rows; row++) {
            for (int col = 0; col < columns; col++) {
                heap_pl[heap_c] = new place(heap_c, row, col, 100000000, false);
                // Mark impossible at glance
                if (get_time(map[row][col]) == -1) { heap_pl[heap_c]->marked = true; }
                // Check edges
                if (row == x_0 && col == y_0) { start_place = heap_pl[heap_c]; }
                if (row == xf && col == yf) { end_place = heap_pl[heap_c]; }

                // Place connections
                if (row > 0) {
                    heap_pl[heap_c]->upper = heap_pl[heap_c - columns];
                    heap_pl[heap_c - columns]->lower = heap_pl[heap_c];
                }
                if (col > 0) {
                    heap_pl[heap_c]->left_s = heap_pl[heap_c - 1];
                    heap_pl[heap_c - 1]->right_s = heap_pl[heap_c];
                }
                heap_c++;
            }
        }

        // Init branches and balance them
        start_place->length = 0;
        siftup(heap_pl, start_place->index);
        for (int i = heap_c / 2 - 1; i >= 0; i--) {
            siftdown(heap_pl, heap_c, i);
        }

        while (true) {
            place* min_p = heap_pl[0];
            if (min_p->marked) { break; }
            min_p->marked = true;

            siftdown(heap_pl, heap_c, min_p->index);

            // Values needed
            place* low = min_p->lower;
            place* upp = min_p->upper;
            place* lef = min_p->left_s;
            place* rig = min_p->right_s;
            int mpx = min_p->x;
            int mpy = min_p->y;

            // Cover all close places
            if (mpx > 0 && !upp->marked) {
                upp->length = min(upp->length, min_p->length + get_time(map[mpx - 1][mpy]));
                siftup(heap_pl, upp->index);
            }
            if (mpx < rows - 1 && !low->marked) {
                low->length = min(low->length, min_p->length + get_time(map[mpx + 1][mpy]));
                siftup(heap_pl, low->index);
            }
            if (mpy > 0 && !lef->marked) {
                lef->length = min(lef->length, min_p->length + get_time(map[mpx][mpy - 1]));
                siftup(heap_pl, lef->index);
            }
            if (mpy < columns - 1 && !rig->marked) {
                rig->length = min(rig->length, min_p->length + get_time(map[mpx][mpy + 1]));
                siftup(heap_pl, rig->index);
            }
        }

        int result = end_place->length;
        if (result == 100000000) {
            cout << -1 << "\n";
            return 0;
        }

        vector<char> path;
        place* prev_pl = end_place;

        while (prev_pl->x != x_0 || prev_pl->y != y_0) {
            if (prev_pl->upper && prev_pl->length - get_time(map[prev_pl->x][prev_pl->y]) == prev_pl->upper->length) {
                path.push_back('S');
                prev_pl = prev_pl->upper;
            } else if (prev_pl->lower && prev_pl->length - get_time(map[prev_pl->x][prev_pl->y]) == prev_pl->lower->length) {
                path.push_back('N');
                prev_pl = prev_pl->lower;
            } else if (prev_pl->left_s && prev_pl->length - get_time(map[prev_pl->x][prev_pl->y]) == prev_pl->left_s->length) {
                path.push_back('E');
                prev_pl = prev_pl->left_s;
            } else if (prev_pl->right_s && prev_pl->length - get_time(map[prev_pl->x][prev_pl->y]) == prev_pl->right_s->length) {
                path.push_back('W');
                prev_pl = prev_pl->right_s;
            }
        }

        cout << result << "\n";
        for (int i = path.size() - 1; i >= 0; i--) {
            cout << path[i];
        }

        return 0;
    }
