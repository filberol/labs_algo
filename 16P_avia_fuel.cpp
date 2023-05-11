#include <iostream>
#include <vector>
using namespace std;

int vertical_counter;
int horizontal_counter;
int dim;

void vertical_check(vector<vector<bool>>& matrix, vector<bool>& visited, int j_visit) {
    vertical_counter++;
    visited.at(j_visit) = true;
    for (int i = 0; i < dim; i++) {
        if (!visited.at(i) && matrix.at(j_visit).at(i)) {
            vertical_check(matrix, visited, i);
        }
    }
}

void horizontal_check(vector<vector<bool>>& matrix, vector<bool>& visited, int j_visit) {
    horizontal_counter++;
    visited.at(j_visit) = true;
    for (int i = 0; i < dim; i++) {
        if (!visited.at(i) && matrix.at(i).at(j_visit)) {
            horizontal_check(matrix, visited, i);
        }
    }
}

int main() {
    cin >> dim;

    vector<vector<int>> matrix;
    vector<vector<bool>> search_matrix;

    matrix.resize(dim);
    int temp;
    for (int i = 0; i < dim; i++) {
        for (int j = 0; j < dim; j++) {
            cin >> temp;
            matrix.at(i).push_back(temp);
        }
    }

    // Apply binomial search
    auto left = 0;
    auto right = 2000000000;
    vector<bool> visited;
    while (left < right) {
        int m = (left + right) / 2;
        search_matrix.clear();
        search_matrix.resize(dim);
        for (int i = 0; i < dim; i++) {
            for (int j = 0; j < dim; j++) {
                // Is possible to fly there
                search_matrix.at(i).push_back(matrix.at(i).at(j) <= m);
            }
        }

        vertical_counter = 0;
        horizontal_counter = 0;
        // Checking from every city to every city

        visited.clear();
        visited.resize(dim, false);
        vertical_check(search_matrix, visited, 0);
        visited.clear();
        visited.resize(dim, false);
        horizontal_check(search_matrix, visited, 0);
        if (vertical_counter == dim && horizontal_counter == dim) {
            right = m;
        } else {
            left = m + 1;
        }
    }

    cout << left;

}