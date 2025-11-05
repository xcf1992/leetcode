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
// set C(3,"C") to be the sum of value at C(1,"A") and the values sum of the rectangle range whose top-left cell is C(1,"A") and bottom-right cell is C(2,"B"). Return 4.
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
Please remember to RESET your class variables declared in class Excel, as static/class variables are persisted across multiple test cases. Please see here for more details.
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
#include <stdio.h>
#include <map>
#include <set>
#include <numeric>
using namespace std;

struct Cell {
    bool isFormula = false;
    int value = 0;
    unordered_map<int, int> formula;
};

class Excel {
private:
    vector<vector<Cell *> > sheet;
    int M = 0;
    int N = 0;

    int posToInt(string pos) {
        int col = pos[0] - 'A';
        int row = 0;
        for (int i = 1; i < pos.size(); ++i) {
            row = row * 10 + (pos[i] - '0');
        }
        return (row - 1) * N + col;
    }

    void addPosToFormula(unordered_map<int, int> &formula, string pos) {
        int topLeft = posToInt(pos.substr(0, pos.find(':')));
        int botRight = posToInt(pos.substr(pos.find(':') + 1));

        int topLeftRow = topLeft / N;
        int topLeftCol = topLeft % N;
        int botRightRow = botRight / N;
        int botRightCol = botRight % N;
        for (int i = topLeftRow; i <= botRightRow; ++i) {
            for (int j = topLeftCol; j <= botRightCol; ++j) {
                formula[i * N + j] += 1;
            }
        }
    }

public:
    Excel(int H, char W) {
        sheet.clear();
        M = H;
        N = W - 'A' + 1;
        sheet.resize(M, vector<Cell *>(N, nullptr));
    }

    void set(int r, char c, int v) {
        int row = r - 1;
        int col = c - 'A';
        if (row < 0 or row
        >=
        M or col<0 or col >= N
        )
        {
            return;
        }

        if (sheet[row][col] == nullptr) {
            sheet[row][col] = new Cell();
        }
        sheet[row][col]->isFormula = false;
        sheet[row][col]->value = v;
    }

    int get(int r, char c) {
        int row = r - 1;
        int col = c - 'A';
        if (row < 0 or row
        >=
        M or col<0 or col >= N or sheet[row][col] == nullptr
        )
        {
            return 0;
        }

        if (!sheet[row][col]->isFormula) {
            return sheet[row][col]->value;
        }

        int sum = 0;
        for (auto &form: sheet[row][col]->formula) {
            int pos = form.first;
            int times = form.second;
            sum += times * get(1 + pos / N, 'A' + pos % N);
        }
        return sum;
    }

    int sum(int r, char c, vector<string> strs) {
        int row = r - 1;
        int col = c - 'A';
        if (row < 0 or row
        >=
        M or col<0 or col >= N
        )
        {
            return 0;
        }

        if (sheet[row][col] == nullptr) {
            sheet[row][col] = new Cell();
        }

        sheet[row][col]->isFormula = true;
        sheet[row][col]->formula.clear();
        for (string &str: strs) {
            if (str.find(':') == string::npos) {
                int pos = posToInt(str);
                sheet[row][col]->formula[pos] += 1;
            } else {
                addPosToFormula(sheet[row][col]->formula, str);
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