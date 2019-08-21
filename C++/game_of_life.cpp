/*
289. Game of Life
According to the Wikipedia's article:
"The Game of Life, also known simply as Life, is a cellular automaton devised by the British mathematician John Horton Conway in 1970."

Given a board with m by n cells,
each cell has an initial state live (1) or dead (0).
Each cell interacts with its eight neighbors (horizontal, vertical, diagonal) using the following four rules
(taken from the above Wikipedia article):

Any live cell with fewer than two live neighbors dies, as if caused by under-population.
Any live cell with two or three live neighbors lives on to the next generation.
Any live cell with more than three live neighbors dies, as if by over-population..
Any dead cell with exactly three live neighbors becomes a live cell, as if by reproduction.

Write a function to compute the next state (after one update) of the board given its current state.
The next state is created by applying the above rules simultaneously to every cell in the current state,
where births and deaths occur simultaneously.

Example:

Input:
[
  [0,1,0],
  [0,0,1],
  [1,1,1],
  [0,0,0]
]
Output:
[
  [0,0,0],
  [1,0,1],
  [0,1,1],
  [0,1,0]
]

Follow up:
Could you solve it in-place? Remember that the board needs to be updated at the same time:
You cannot update some cells first and then use their updated values to update other cells.

In this question, we represent the board using a 2D array.
 In principle, the board is infinite, which would cause problems when the active area encroaches the border of the array.
 How would you address these problems?
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
Essentially, the second follow-up asks us to address the scalability aspect of the problem.
What would happen if the board is infinitely large?
Can we still use the same solution that we saw earlier or is there something else we will have to do different?
If the board becomes infinitely large, there are multiple problems our current solution would run into:

It would be computationally impossible to iterate a matrix that large.
It would not be possible to store that big a matrix entirely in memory.
We have huge memory capacities these days i.e. of the order of hundreds of GBs.
However, it still wouldn't be enough to store such a large matrix in memory.

We would be wasting a lot of space if such a huge board only has a few live cells and the rest of them are all dead.
In such a case, we have an extremely sparse matrix and it wouldn't make sense to save the board as a "matrix".

Such open ended problems are better suited to design discussions during programming interviews
and it's a good habit to take into consideration the scalability aspect of the problem
since your interviewer might be interested in talking about such problems.
The discussion section already does a great job at addressing this specific portion of the problem.
We will briefly go over two different solutions that have been provided in the discussion sections,
as they broadly cover two main scenarios of this problem.

One aspect of the problem is addressed by a great solution provided by Stefan Pochmann.
So as mentioned before, it's quite possible that we have a gigantic matrix with a very few live cells.
In that case it would be stupidity to save the entire board as is.

If we have an extremely sparse matrix, it would make much more sense to actually save the location of only the live cells
and then apply the 4 rules accordingly using only these live cells.

Essentially, we obtain only the live cells from the entire board
and then apply the different rules using only the live cells
and finally we update the board in-place.

The only problem with this solution would be when the entire board cannot fit into memory.
If that is indeed the case, then we would have to approach this problem in a different way.
For that scenario, we assume that the contents of the matrix are stored in a file, one row at a time.

In order for us to update a particular cell, we only have to look at its 8 neighbors which essentially lie in the row above and below it.
So, for updating the cells of a row, we just need the row above and the row below.
Thus, we read one row at a time from the file and at max we will have 3 rows in memory.
We will keep discarding rows that are processed and then we will keep reading new rows from the file, one at a time.

@beagle's solution revolves around this idea and you can refer to the code in the discussion section for the same.
It's important to note that there is no single solution for solving this problem.
Everybody might have a different viewpoint for addressing the scalability aspect of the problem
and these two solutions just address the most basic problems with handling matrix based problems at scale.

https://leetcode.com/problems/game-of-life/discuss/73217/Infinite-board-solution/201780
*/
class Solution {
public:
    void gameOfLife(vector<vector<int>>& board) {
        int m = board.size();
        int n = board[0].size();
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                int count = 0;
                for (int x = max(i - 1, 0); x < min(i + 2, m); ++x) {
                    for (int y = max(j - 1, 0); y < min(j + 2, n); ++y) {
                        count += board[x][y] & 1;
                    }
                }
                if (count == 3 or count - board[i][j] == 3) {
                    board[i][j] |= 2;
                }
            }
        }

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                board[i][j] >>= 1;
            }
        }
    }
};
