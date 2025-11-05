/*
1728. Cat and Mouse II
https://leetcode.com/problems/cat-and-mouse-ii/

A game is played by a cat and a mouse named Cat and Mouse.

The environment is represented by a grid of size rows x cols,
where each element is a wall, floor, player (Cat, Mouse), or food.

Players are represented by the characters 'C'(Cat),'M'(Mouse).
Floors are represented by the character '.' and can be walked on.
Walls are represented by the character '#' and cannot be walked on.
Food is represented by the character 'F' and can be walked on.
There is only one of each character 'C', 'M', and 'F' in grid.
Mouse and Cat play according to the following rules:

Mouse moves first, then they take turns to move.
During each turn, Cat and Mouse can jump in one of the four directions (left, right, up, down). They cannot jump over the wall nor outside of the grid.
catJump, mouseJump are the maximum lengths Cat and Mouse can jump at a time, respectively. Cat and Mouse can jump less than the maximum length.
Staying in the same position is allowed.
Mouse can jump over Cat.
The game can end in 4 ways:

If Cat occupies the same position as Mouse, Cat wins.
If Cat reaches the food first, Cat wins.
If Mouse reaches the food first, Mouse wins.
If Mouse cannot get to the food within 1000 turns, Cat wins.
Given a rows x cols matrix grid and two integers catJump and mouseJump,
return true if Mouse can win the game if both Cat and Mouse play optimally,
otherwise return false.

Example 1:
Input: grid = ["####F","#C...","M...."], catJump = 1, mouseJump = 2
Output: true
Explanation: Cat cannot catch Mouse on its turn nor can it get the food before Mouse.
Example 2:
Input: grid = ["M.C...F"], catJump = 1, mouseJump = 4
Output: true
Example 3:
Input: grid = ["M.C...F"], catJump = 1, mouseJump = 3
Output: false
Example 4:
Input: grid = ["C...#","...#F","....#","M...."], catJump = 2, mouseJump = 5
Output: false
Example 5:
Input: grid = [".M...","..#..","#..#.","C#.#.","...#F"], catJump = 3, mouseJump = 1
Output: true

Constraints:
rows == grid.length
cols = grid[i].length
1 <= rows, cols <= 8
grid[i][j] consist only of characters 'C', 'M', 'F', '.', and '#'.
There is only one of each character 'C', 'M', and 'F' in grid.
1 <= catJump, mouseJump <= 8
*/
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <map>
#include <unordered_set>
#include <algorithm>
#include <cmath>
#include <queue>
#include <stack>
#include <stdio.h>
#include <set>
#include <numeric>
using namespace std;

// https://leetcode.com/problems/cat-and-mouse-ii/discuss/1020573/Game-ends-about-70-moves-C%2B%2B
class Solution {
public:
    int memo[71][8][8][8][8];
    vector<string> v;
    int cj, mj;
    int R, C;
    int di[4] = {-1, 1, 0, 0};
    int dj[4] = {0, 0, 1, -1};

    bool dp(int nturn, int cx, int cy, int mx, int my) {
        if (nturn % 2 == 1) {
            //mouse turn
            if (mx == cx && my == cy) return false; //mouse is caught by the cat, losing position for the mouse
            if (nturn >= 70) return false; //mouse can't win, it used many moves and it couldnt get the food
            if (v[mx][my] == 'F') return true; //winner position, mouse got the food
            if (v[cx][cy] == 'F') return false; //losing position, cat got the food
        } else {
            //cat turn
            if (mx == cx && my == cy) return true; //cat captured the mouse, winner position
            if (nturn >= 70) return true; //winner position for the cat, nice block ;)
            if (v[mx][my] == 'F') return false; // losing position, mouse got the food
            if (v[cx][cy] == 'F') return true; //winner position, cat got the food
        }

        if (memo[nturn][cx][cy][mx][my] != -1) return memo[nturn][cx][cy][mx][my];
        bool win = false;

        if (nturn % 2 == 1) {
            //mouse turn
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j <= mj; j++) {
                    int Mx = mx + j * di[i];
                    int My = my + j * dj[i];
                    if (Mx >= 0 && Mx < R && My >= 0 && My < C && v[Mx][My] != '#') {
                        if (dp(nturn + 1, cx, cy, Mx, My) == 0) {
                            //If there is any move that causes the next player to lose then I am in a winning position.
                            win = true;
                            break;
                        }
                    } else break;
                }
                if (win)break;
            }
        } else {
            //cat turn
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j <= cj; j++) {
                    int Cx = cx + j * di[i];
                    int Cy = cy + j * dj[i];
                    if (Cx >= 0 && Cx < R && Cy >= 0 && Cy < C && v[Cx][Cy] != '#') {
                        if (dp(nturn + 1, Cx, Cy, mx, my) == 0) {
                            //If there is any move that causes the next player to lose then I am in a winning position.
                            win = true;
                            break;
                        }
                    } else break;
                }
                if (win)break;
            }
        }

        memo[nturn][cx][cy][mx][my] = win;
        return win;
    }

    bool canMouseWin(vector<string> &_v, int _cj, int _mj) {
        memset(memo, -1, sizeof(memo));
        v = _v;
        cj = _cj;
        mj = _mj;
        int cx, cy, mx, my;
        R = v.size();
        C = v[0].size();

        for (int i = 0; i < R; i++)
            for (int j = 0; j < C; j++) {
                if (v[i][j] == 'C') {
                    cx = i;
                    cy = j;
                }

                if (v[i][j] == 'M') {
                    mx = i;
                    my = j;
                }
            }
        return dp(1, cx, cy, mx, my);
    }
};