/*
1138. Alphabet Board Path

On an alphabet board, we start at position (0, 0),
corresponding to character board[0][0].
Here, board = ["abcde", "fghij", "klmno", "pqrst", "uvwxy", "z"],
as shown in the diagram below.
a b c d e
f g h i j
k l m n o
p q r s t
u v w x y
z
We may make the following moves:
'U' moves our position up one row, if the position exists on the board;
'D' moves our position down one row, if the position exists on the board;
'L' moves our position left one column, if the position exists on the board;
'R' moves our position right one column, if the position exists on the board;
'!' adds the character board[r][c] at our current position (r, c) to the answer.
(Here, the only positions that exist on the board are positions with letters on them.)

Return a sequence of moves that makes our answer equal to target in the minimum number of moves.
You may return any path that does so.

Example 1:
Input: target = "leet"
Output: "DDR!UURRR!!DDD!"

Example 2:
Input: target = "code"
Output: "RR!DDRR!UUL!R!"

Constraints:
1 <= target.length <= 100
target consists only of English lowercase letters.
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
using namespace std;
/*
* special case of letter z
* special case of zz
*/
class Solution {
private:
    unordered_map<int, char> rMove = unordered_map<int, char>({{1, 'D'}, {-1, 'U'}});
    unordered_map<int, char> cMove = unordered_map<int, char>({{1, 'R'}, {-1, 'L'}});

    void moveTo(int &curR, int &curC, char letter, string &result) {
        int nextR = (letter - 'a') / 5;
        int nextC = (letter - 'a') % 5;
        if (curR != nextR) {
            int rDiff = nextR - curR;
            result += string(abs(rDiff), rMove[rDiff / abs(rDiff)]);
        }
        if (curC != nextC) {
            int cDiff = nextC - curC;
            result += string(abs(cDiff), cMove[cDiff / abs(cDiff)]);
        }
        curR = nextR;
        curC = nextC;
    }

public:
    string alphabetBoardPath(string target) {
        string result = "";
        int curR = 0;
        int curC = 0;
        char curLetter = 'a';
        for (char letter: target) {
            if (curLetter == 'z' ^ letter == 'z') {
                // we should only move to u first if either of cur or next letter is 'z'
                moveTo(curR, curC, 'u', result);
            }
            moveTo(curR, curC, letter, result);
            result.push_back('!');
            curLetter = letter;
        }
        return result;
    }
};