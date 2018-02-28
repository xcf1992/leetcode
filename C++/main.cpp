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
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class TicTacToe {
private:
    vector<vector<int>> rowCount;
    vector<vector<int>> colCount;
    vector<int> diagnal;
    vector<int> antiDiagnal;
    int size;
public:
    /** Initialize your data structure here. */
    TicTacToe(int n) {
        rowCount.resize(2, vector<int>(n, 0));
        colCount.resize(2, vector<int>(n, 0));
        diagnal.resize(2, 0);
        antiDiagnal.resize(2, 0);
        size = n;
    }
    
    /** Player {player} makes a move at ({row}, {col}).
     @param row The row of the board.
     @param col The column of the board.
     @param player The player, can be either 1 or 2.
     @return The current winning condition, can be either:
     0: No one wins.
     1: Player 1 wins.
     2: Player 2 wins. */
    int move(int row, int col, int player) {
        rowCount[player - 1][row] += 1;
        colCount[player - 1][col] += 1;
        if (row == col) {
            diagnal[player - 1] += 1;
        }
        if (row + col == size) {
            antiDiagnal[player - 1] += 1;
        }
        
        if (rowCount[player - 1][row] == size ||
            colCount[player - 1][col] == size ||
            diagnal[player - 1] == size ||
            antiDiagnal[player - 1] == size) {
            return player;
        }
        return 0;
    }
};

int main() {
    //Solution s;
    vector<string> v({"ABD","BCE","DEF","FFF"});
    vector<int> v2({2,2,2,2,2});
    vector<char> chars({'a','a','a','a','a','b','b','c'});
    vector<vector<int>> matrix({{78,16,94,36},{87,93,50,22},{63,28,91,60},{64,27,41,27},{73,37,12,69},{68,30,83,31},{63,24,68,36}});
    
    //s.numberToWords(323452345);
    
    TicTacToe t(2);
    t.move(0,1,1);
    t.move(1,1,2);
    t.move(1,0,1);
}
