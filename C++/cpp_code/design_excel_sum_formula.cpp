/*
631. Design Excel Sum Formula

Your task is to design the basic function of Excel and implement the function of sum formula.
Specifically, you need to implement the following functions:

Excel(int H, char W): This is the constructor.
The inputs represents the height and width of the Excel form.
H is a positive integer, range from 1 to 26.
It represents the height.
W is a character range from 'A' to 'Z'.
It represents that the width is the number of characters from 'A' to W.

The Excel form content is represented by a height * width 2D integer array C,
it should be initialized to zero.
You should assume that the first row of C starts from 1,
and the first column of C starts from 'A'.

void Set(int row, char column, int val):
Change the value at C(row, column) to be val.

int Get(int row, char column):
Return the value at C(row, column).

int Sum(int row, char column, List of Strings : numbers):
This function calculate and set the value at C(row, column),
where the value should be the sum of cells represented by numbers.
This function return the sum result at C(row, column).
This sum formula should exist until this cell is overlapped by another value or another sum formula.

numbers is a list of strings that each string represent a cell or a range of cells.
If the string represent a single cell, then it has the following format : ColRow.
For example, "F7" represents the cell at (7, F).

If the string represent a range of cells,
then it has the following format : ColRow1:ColRow2.
The range will always be a rectangle,
and ColRow1 represent the position of the top-left cell,
and ColRow2 represents the position of the bottom-right cell.

Example 1:
Excel(3,"C");
// construct a 3*3 2D array with all zero.
//   A B C
// 1 0 0 0
// 2 0 0 0
// 3 0 0 0

Set(1, "A", 2);
// set C(1,"A") to be 2.
//   A B C
// 1 2 0 0
// 2 0 0 0
// 3 0 0 0

Sum(3, "C", ["A1", "A1:B2"]);
// set C(3,"C") to be the sum of value at C(1,"A") and the values sum of the rectangle range whose top-left cell is
C(1,"A") and bottom-right cell is C(2,"B"). Return 4.
//   A B C
// 1 2 0 0
// 2 0 0 0
// 3 0 0 4

Set(2, "B", 2);
// set C(2,"B") to be 2. Note C(3, "C") should also be changed.
//   A B C
// 1 2 0 0
// 2 0 2 0
// 3 0 0 6

Note:
You could assume that there won't be any circular sum reference. For example, A1 = sum(B1) and B1 = sum(A1).
The test cases are using double-quotes to represent a character.
Please remember to RESET your class variables declared in class Excel, as static/class variables are persisted across
multiple test cases. Please see here for more details.
*/
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <cmath>
#include <queue>
#include <stack>
#include <climits>
#include <map>
#include <set>
#include <numeric>
using namespace std;

struct Formula {
    unordered_map<string, int> cells;  // dependency → multiplicity
    int val = 0;
};

class Excel {
private:
    vector<vector<Formula>> grid_;
    int height_;
    int width_;
    stack<pair<int, int>> stk_;

    // Convert ["A1", "A1:B2"] into a map: cellName → count
    unordered_map<string, int> convert(const vector<string>& strs) {
        unordered_map<string, int> rst;
        for (auto& pos : strs) {
            size_t colon = pos.find(':');
            if (colon == string::npos) {
                rst[pos] += 1;
                continue;
            }

            char start_col = pos[0];
            char end_col = pos[colon + 1];
            int start_row = stoi(pos.substr(1, colon - 1));
            int end_row = stoi(pos.substr(colon + 2));
            for (int i = start_row; i <= end_row; i++) {
                for (char j = start_col; j <= end_col; j++) {
                    rst[string(1, j) + to_string(i)] += 1;
                }
            }
        }
        return rst;
    }

    // Compute sum for cell (r,c) using its dependency map, update cached val
    int calc_sum(int r, int c, unordered_map<string, int>& cells) {
        int sum = 0;
        for (auto& [name, cnt] : cells) {
            int x = stoi(name.substr(1)) - 1;  // row (0-indexed)
            int y = name[0] - 'A';             // col (0-indexed)
            sum += grid_[x][y].val * cnt;
        }
        grid_[r][c] = {cells, sum};
        return sum;
    }

    // DFS: find all cells that (transitively) depend on (r,c),
    // push them onto stack in topological order (deepest dependents first)
    void topo_sort(int r, int c) {
        string key = string(1, (char)('A' + c)) + to_string(r + 1);
        for (int i = 0; i < height_; i++) {
            for (int j = 0; j < width_; j++) {
                if (grid_[i][j].cells.find(key) != grid_[i][j].cells.end()) {
                    topo_sort(i, j);
                }
            }
        }
        stk_.push({r, c});
    }

    // Pop stack and recompute every formula cell
    void execute_stk() {
        while (!stk_.empty()) {
            auto [r, c] = stk_.top();
            stk_.pop();

            if (!grid_[r][c].cells.empty()) {
                calc_sum(r, c, grid_[r][c].cells);
            }
        }
    }

public:
    Excel(int height, char width) {
        height_ = height;
        width_ = width - 'A' + 1;
        grid_.clear();
        grid_.resize(height_, vector<Formula>(width_));
    }

    int get(int row, char column) {
        return grid_[row - 1][column - 'A'].val;
    }

    void set(int row, char column, int val) { // set means to wipe out all formula
        int r = row - 1;
        int c = column - 'A';
        // plain value, no formula
        grid_[r][c] = {{}, val};

        // find all dependents
        topo_sort(r, c);

        // recompute them in order
        execute_stk();
    }

    int sum(int row, char column, vector<string> numbers) {
        int r = row - 1;
        int c = column - 'A';
        unordered_map<string, int> cells = convert(numbers);
        int sum = calc_sum(r, c, cells);
        set(row, column, sum);      // propagate as plain value
        grid_[r][c] = {cells, sum};  // then restore the formula
        return sum;
    }
};

struct Cell {
    bool is_formula = false;
    int value = 0;
    unordered_map<int, int> formula;

    Cell() {
        is_formula = false;
        value = 0;
    }

    Cell(bool is_formula_, int val_) : is_formula(is_formula_), value(val_) {
    }
};

class Excel1 {
private:
    vector<vector<Cell*>> sheet_;
    int m_ = 0;
    int n_ = 0;

    int pos_to_int(string pos) {
        int col = pos[0] - 'A';
        int row = 0;
        for (int i = 1; i < pos.size(); ++i) {
            row = row * 10 + (pos[i] - '0');
        }
        return (row - 1) * n_ + col;
    }

    void add_pos_to_formula(unordered_map<int, int>& formula, string pos) {
        int top_left_pos = pos_to_int(pos.substr(0, pos.find(':')));
        int bot_right_pos = pos_to_int(pos.substr(pos.find(':') + 1));

        int top_left_row = top_left_pos / n_;
        int top_left_col = top_left_pos % n_;
        int bot_right_row = bot_right_pos / n_;
        int bot_right_col = bot_right_pos % n_;
        for (int i = top_left_row; i <= bot_right_row; ++i) {
            for (int j = top_left_col; j <= bot_right_col; ++j) {
                formula[i * n_ + j] += 1;
            }
        }
    }

public:
    Excel(int H, char W) {
        sheet_.clear();
        m_ = H;
        n_ = W - 'A' + 1;
        sheet_.resize(m_, vector<Cell*>(n_, nullptr));
    }

    void set(int r, char c, int v) {
        int row = r - 1;
        int col = c - 'A';
        if (row < 0 || row >= m_ || col < 0 || col >= n_) {
            return;
        }

        if (sheet_[row][col] == nullptr) {
            sheet_[row][col] = new Cell();
        }
        sheet_[row][col]->is_formula = false;
        sheet_[row][col]->value = v;
    }

    int get(int r, char c) {
        int row = r - 1;
        int col = c - 'A';
        if (row < 0 || row >= m_ || col < 0 || col >= n_ || sheet_[row][col] == nullptr) {
            return 0;
        }

        if (!sheet_[row][col]->is_formula) {
            return sheet_[row][col]->value;
        }

        int sum = 0;
        for (auto& form : sheet_[row][col]->formula) {
            int pos = form.first;
            int times = form.second;
            sum += times * get(1 + pos / n_, 'A' + pos % n_);
        }
        return sum;
    }

    int sum(int r, char c, vector<string> strs) {
        int row = r - 1;
        int col = c - 'A';
        if (row < 0 || row >= m_ || col < 0 || col >= n_) {
            return 0;
        }

        if (sheet_[row][col] == nullptr) {
            sheet_[row][col] = new Cell();
        }

        sheet_[row][col]->is_formula = true;
        sheet_[row][col]->formula.clear();
        for (string& str : strs) {
            if (str.find(':') == string::npos) {
                int pos = pos_to_int(str);
                sheet_[row][col]->formula[pos] += 1;
            } else {
                add_pos_to_formula(sheet_[row][col]->formula, str);
            }
        }
        return get(r, c);
    }
};

/*
 * Your Excel object will be instantiated and called as such:
 * Excel* obj = new Excel(H, W);
 * obj->set(r,c,v);
 * int param_2 = obj->get(r,c);
 * int param_3 = obj->sum(r,c,strs);
 */