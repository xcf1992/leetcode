/*
https://leetcode.com/problems/find-the-maximum-number-of-fruits-collected/description/
3363. Find the Maximum Number of Fruits Collected

There is a game dungeon comprised of n x n rooms arranged in a grid.

You are given a 2D array fruits of size n x n, where fruits[i][j] represents the number of fruits in the room (i, j).
Three children will play in the game dungeon, with initial positions at the corner rooms (0, 0), (0, n - 1), and (n - 1,
0).

The children will make exactly n - 1 moves according to the following rules to reach the room (n - 1, n - 1):

The child starting from (0, 0) must move from their current room (i, j) to one of the rooms (i + 1, j + 1), (i + 1, j),
and (i, j + 1) if the target room exists. The child starting from (0, n - 1) must move from their current room (i, j) to
one of the rooms (i + 1, j - 1), (i + 1, j), and (i + 1, j + 1) if the target room exists. The child starting from (n -
1, 0) must move from their current room (i, j) to one of the rooms (i - 1, j + 1), (i, j + 1), and (i + 1, j + 1) if the
target room exists. When a child enters a room, they will collect all the fruits there. If two or more children enter
the same room, only one child will collect the fruits, and the room will be emptied after they leave.

Return the maximum number of fruits the children can collect from the dungeon.



Example 1:

Input: fruits = [[1,2,3,4],[5,6,8,7],[9,10,11,12],[13,14,15,16]]

Output: 100

Explanation:



In this example:

The 1st child (green) moves on the path (0,0) -> (1,1) -> (2,2) -> (3, 3).
The 2nd child (red) moves on the path (0,3) -> (1,2) -> (2,3) -> (3, 3).
The 3rd child (blue) moves on the path (3,0) -> (3,1) -> (3,2) -> (3, 3).
In total they collect 1 + 6 + 11 + 16 + 4 + 8 + 12 + 13 + 14 + 15 = 100 fruits.

Example 2:

Input: fruits = [[1,1],[1,1]]

Output: 4

Explanation:

In this example:

The 1st child moves on the path (0,0) -> (1,1).
The 2nd child moves on the path (0,1) -> (1,1).
The 3rd child moves on the path (1,0) -> (1,1).
In total they collect 1 + 1 + 1 + 1 = 4 fruits.



Constraints:

2 <= n == fruits.length == fruits[i].length <= 1000
0 <= fruits[i][j] <= 1000
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
using namespace std;

class Solution {
public:
    int maxCollectedFruits(vector<vector<int>>& fruits) {
        int n = fruits.size();
        int rst = 0;

        // collect fruits for child 1
        for (int i = 0; i < n; i++) {
            rst += fruits[i][i];
            fruits[i][i] = 0;
        }

        // child 2 and child 3 will do collect fruits from their half without intersect
        for (int pass = 0; pass < 2; pass++) {
            // swap the half to align the code
            if (pass == 1) {
                for (int i = 0; i < n; i++) {
                    for (int j = i + 1; j < n; j++) {
                        swap(fruits[i][j], fruits[j][i]);
                    }
                }
            }

            // collect the fruits using dp
            vector<int> prev(n, -1);
            prev[n - 1] = fruits[0][n - 1];
            for (int row = 1; row < n; row++) {
                vector<int> cur(n, -1);
                for (int col = 0; col < n; col++) {
                    if (col > 0 && prev[col - 1] != -1) {
                        cur[col] = max(cur[col], prev[col - 1]);
                    }
                    if (prev[col] != -1) {
                        cur[col] = max(cur[col], prev[col]);
                    }
                    if (col < n - 1 && prev[col + 1] != -1) {
                        cur[col] = max(cur[col], prev[col + 1]);
                    }
                    if (cur[col] != -1) {
                        cur[col] += fruits[row][col];
                    }
                }
                prev = cur;
            }

            rst += prev[n - 1];
        }
        return rst;
    }
};
