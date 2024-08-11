#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

void print_in_format(vector<int>& matrix) {
    for (int i = 0; i < 9; i++) {
        if (i % 3 == 0 && i > 0) {
            cout << endl;
        }
        cout << matrix[i] << " ";
    }
    cout << endl;
}

vector<vector<int>> convert(vector<int>& s) {
    vector<vector<int>> mat(3, vector<int>(3));
    for (int i = 0; i < 9; i++) {
        if (i < 3) {
            mat[0][i] = s[i];
        } else if (i >= 3 && i <= 5) {
            mat[1][i - 3] = s[i];
        } else {
            mat[2][i - 6] = s[i];
        }
    }
    return mat;
}

pair<int, int> ideal_distFind(int val) {
    int x1 = 999, y1 = 999;
    vector<vector<int>> ideal = {{1, 2, 3},
                                 {4, 5, 6},
                                 {7, 8, 0}};
    
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (ideal[i][j] == val) {
                x1 = i;
                y1 = j;
                break;
            }
        }
    }
    return make_pair(x1, y1);
}

int count(vector<int>& initial_state) {
    vector<int> inits = initial_state;
    vector<vector<int>> inicon = convert(inits);
    int total_h = 0;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            pair<int, int> ideal_pos = ideal_distFind(inicon[i][j]);
            int x1 = ideal_pos.first;
            int y1 = ideal_pos.second;
            int x2 = i, y2 = j;
            total_h += abs(x1 - x2) + abs(y1 - y2);
        }
    }

    return total_h;
}

pair<vector<int>, int> move(vector<int>& ar, int p, vector<int>& st) {
    int rh = 9999;
    vector<int> store_st = st;

    for (int i = 0; i < ar.size(); i++) {
        vector<int> dupl_st = st;

        swap(dupl_st[p], dupl_st[ar[i]]);

        int trh = count(dupl_st);

        if (trh < rh) {
            rh = trh;
            store_st = dupl_st;
        }
    }

    return make_pair(store_st, rh);
}

int main() {
    vector<int> state = {0,1,3,4,2,5,7,8,6};

    int h = count(state);
    int Level = 1;

    cout << "\n------ Level " << Level << " ------\n";
    print_in_format(state);
    cout << "\nHeuristic Value(Manhattan Distance) : " << h << endl;

    while (h > 0) {
        int pos = find(state.begin(), state.end(), 0) - state.begin();

        Level++;

        vector<int> arr;
        if (pos == 0) {
            arr = {1, 3};
        } else if (pos == 1) {
            arr = {0, 2, 4};
        } else if (pos == 2) {
            arr = {1, 5};
        } else if (pos == 3) {
            arr = {0, 4, 6};
        } else if (pos == 4) {
            arr = {1, 3, 5, 7};
        } else if (pos == 5) {
            arr = {2, 4, 8};
        } else if (pos == 6) {
            arr = {3, 7};
        } else if (pos == 7) {
            arr = {4, 6, 8};
        } else if (pos == 8) {
            arr = {5, 7};
        }

        pair<vector<int>, int> result = move(arr, pos, state);
        state = result.first;
        h = result.second;

        cout << "\n------ Level " << Level << " ------\n";
        print_in_format(state);
        cout << "\nHeuristic Value(Manhattan Distance) : " << h << endl<<endl;
        
    }
    cout<<"Total Moves :   "<<Level;

    return 0;
}
