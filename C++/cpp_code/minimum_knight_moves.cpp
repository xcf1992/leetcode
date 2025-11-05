/*
1197. Minimum Knight Moves
https://leetcode.com/problems/minimum-knight-moves/

In an infinite chess board with coordinates from -infinity to +infinity,
you have a knight at square [0, 0].

A knight has 8 possible moves it can make,
as illustrated below.
Each move is two squares in a cardinal direction,
then one square in an orthogonal direction.

Return the minimum number of steps needed to move the knight to the square [x, y].
It is guaranteed the answer exists.

Example 1:
Input: x = 2, y = 1
Output: 1
Explanation: [0, 0] → [2, 1]

Example 2:
Input: x = 5, y = 5
Output: 4
Explanation: [0, 0] → [2, 1] → [4, 2] → [3, 4] → [5, 5]

Constraints:
|x| + |y| <= 300
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
using namespace std;
/*
While the O(1) math solution is impressive,
it is unlikely that you will come up with such solution on a real interview unless you knew it beforehand.

Here's an iterative solution divided into 2 zones:
"near zone" (within 2 squares distance for both coordinates),
and "far zone", (greater than 2 squares distance for at least one coordinate).

While in the "far" zone,
jump to reduce the coordinate with the greater value.

In the "near" zone, since the square {0,0} is black,
you can jump to it from a white square in 1 move,
and from a black square in 2 moves.
The symmetry makes conditionals shorter if you take the absolute value.

There are 2 edge cases: the same square (0 moves),
and an adjacent square (3 moves).
https://leetcode.com/problems/minimum-knight-moves/discuss/387297/C%2B%2B-Clear-Code-Terse-Solution-with-Explanation
*/
class Solution {
    // math
public:
    int minKnightMoves(int x, int y) {
        if (x == 0 and y
        ==
        0
        )
        {
            // edge case - the same square
            return 0;
        }
        if (abs(x + y) == 1) {
            // edge case - adjacent square
            return 3;
        }

        x = abs(x);
        y = abs(y);
        /*
        * When we reached distance <= 2,
        * we can jump to 0 from white square in 1 move
        * and from black square in 2 moves.
        * While we are more than 2 squares away in both direction, we should reduce
        * the longest coordinate by 2.
        */
        int res = 0;
        while (x > 2 or y
        >
        2
        )
        {
            if (x > y) {
                x = abs(x - 2);
                y = abs(y - 1);
            } else {
                x = abs(x - 1);
                y = abs(y - 2);
            }
            res += 1;
        }
        // now we are within 1 or 2 jumps from goal
        return (x + y) % 2 == 0 ? res + 2 : res + 1;
    }
};

class Solution1 {
    // bfs
public:
    int minKnightMoves(int x, int y) {
        vector<vector<int> > move({{-2, -1}, {-2, 1}, {2, -1}, {2, 1}, {1, 2}, {1, -2}, {-1, 2}, {-1, -2}});
        unordered_map<int, unordered_map<int, int> > visited;
        visited[0][0] = true;
        queue<pair<int, int> > bfs;
        bfs.push({0, 0});
        int result = 0;
        while (!bfs.empty()) {
            int curSize = bfs.size();
            for (int i = 0; i < curSize; ++i) {
                int curX = bfs.front().first;
                int curY = bfs.front().second;
                bfs.pop();

                if (x == curX and y
                ==
                curY
                )
                {
                    return result;
                }
                for (int j = 0; j < move.size(); ++j) {
                    int nexX = curX + move[j][0];
                    int nexY = curY + move[j][1];
                    /*
                    * the nexX * x >= 0 and nexY * y >= 0 is important here, otherwise it will TLE
                    */
                    if (abs(nexX) <= 300 and abs(nexY)
                    <=
                    300
                    and nexX *x
                    >=
                    0
                    and nexY *y
                    >=
                    0
                    and
                    !visited[nexX][nexY]
                    )
                    {
                        visited[nexX][nexY] = true;
                        bfs.push({nexX, nexY});
                    }
                }
            }
            result += 1;
        }
        return result;
    }
};