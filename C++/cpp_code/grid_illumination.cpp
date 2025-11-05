/*
1001. Grid Illumination

On a N x N grid of cells, each cell (x, y) with 0 <= x < N and 0 <= y < N has a lamp.

Initially, some number of lamps are on.
lamps[i] tells us the location of the i-th lamp that is on.
Each lamp that is on illuminates every square on its x-axis, y-axis, and both diagonals (similar to a Queen in chess).

For the i-th query queries[i] = (x, y),
the answer to the query is 1 if the cell (x, y) is illuminated, else 0.

After each query (x, y) [in the order given by queries],
we turn off any lamps that are at cell (x, y) or are adjacent 8-directionally
(ie., share a corner or edge with cell (x, y).)

Return an array of answers.
Each value answer[i] should be equal to the answer of the i-th query queries[i].

Example 1:
Input: N = 5, lamps = [[0,0],[4,4]], queries = [[1,1],[1,0]]
Output: [1,0]
Explanation:
Before performing the first query we have both lamps [0,0] and [4,4] on.
The grid representing which cells are lit looks like this, where [0,0] is the top left corner, and [4,4] is the bottom right corner:
1 1 1 1 1
1 1 0 0 1
1 0 1 0 1
1 0 0 1 1
1 1 1 1 1
Then the query at [1, 1] returns 1 because the cell is lit.  After this query, the lamp at [0, 0] turns off, and the grid now looks like this:
1 0 0 0 1
0 1 0 0 1
0 0 1 0 1
0 0 0 1 1
1 1 1 1 1
Before performing the second query we have only the lamp [4,4] on.  Now the query at [1,0] returns 0, because the cell is no longer lit.

Note:
1 <= N <= 10^9
0 <= lamps.length <= 20000
0 <= queries.length <= 20000
lamps[i].length == queries[i].length == 2
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

class Solution {
public:
    vector<int> gridIllumination(int N, vector<vector<int> > &lamps, vector<vector<int> > &queries) {
        unordered_map<int, int> row, col, diagonal, antiDiagonal;
        unordered_map<int, unordered_set<int> > onLamps;
        for (vector<int> &lamp: lamps) {
            int r = lamp[0];
            int c = lamp[1];
            row[r] += 1;
            col[c] += 1;
            diagonal[r + c] += 1;
            antiDiagonal[r - c] += 1;
            onLamps[r].insert(c);
        }

        vector<int> result;
        for (vector<int> &query: queries) {
            int r = query[0];
            int c = query[1];
            if (row[r] != 0 or col[c]
            !=
            0
            or diagonal[r + c]
            !=
            0
            or antiDiagonal[r - c]
            !=
            0
            )
            {
                result.push_back(1);
                for (int i = r - 1; i <= r + 1; ++i) {
                    for (int j = c - 1; j <= c + 1; ++j) {
                        if (onLamps[i].erase(j)) {
                            row[i] -= 1;
                            col[j] -= 1;
                            diagonal[i + j] -= 1;
                            antiDiagonal[i - j] -= 1;
                        }
                    }
                }
            }
            else
            {
                result.push_back(0);
            }
        }
        return result;
    }
};

// GET MLE after 4 months
class Solution1 {
public:
    vector<int> gridIllumination(int N, vector<vector<int> > &lamps, vector<vector<int> > &queries) {
        vector<int> lampOn(lamps.size(), 1);
        vector<int> result;
        for (vector<int> &query: queries) {
            int row = query[0];
            int col = query[1];

            int found = 0;
            for (int i = 0; i < lamps.size(); i++) {
                int lRow = lamps[i][0];
                int lCol = lamps[i][1];
                if (lampOn[i] and(lRow == row or lCol == col or abs(lRow - row) == abs(lCol - col))
                )
                {
                    found = 1;
                }
                if (row - 1 <= lRow and lRow
                <=
                row + 1
                and col
                -1 <= lCol
                and lCol
                <=
                col + 1
                )
                {
                    lampOn[i] = 0;
                }
            }
            result.push_back(found);
        }
        return result;
    }
};

// Memory Limit Exceed
class Solution2 {
private:
    vector<int> rDiff = vector<int>({1, -1, 0, 0, 1, 1, -1, -1});
    vector<int> cDiff = vector<int>({0, 0, 1, -1, 1, -1, 1, -1});

    void turnOnOff(int row, int col, vector<vector<int> > &grids, int change) {
        grids[row][col] += change;
        int N = grids.size();
        for (int i = 0; i < rDiff.size(); i++) {
            int r = row + rDiff[i];
            int c = col + cDiff[i];
            while (r >= 0 and c
            >=
            0
            and r<N and c < N
            )
            {
                grids[r][c] += change;
                r += rDiff[i];
                c += cDiff[i];
            }
        }
    }

public:
    vector<int> gridIllumination(int N, vector<vector<int> > &lamps, vector<vector<int> > &queries) {
        vector<vector<int> > grids(N, vector<int>(N, 0));
        unordered_set<int> lampPos;
        for (vector<int> &lamp: lamps) {
            int row = lamp[0];
            int col = lamp[1];
            turnOnOff(row, col, grids, 1);
            lampPos.insert(row * N + col);
        }

        vector<int> result;
        for (vector<int> &query: queries) {
            int row = query[0];
            int col = query[1];
            if (grids[row][col] > 0) {
                result.push_back(1);
            } else {
                result.push_back(0);
            }

            for (int i = 0; i < rDiff.size(); i++) {
                int r = row + rDiff[i];
                int c = col + cDiff[i];
                if (r >= 0 and c
                >=
                0
                and r<N and c < N and lampPos.find(r * N + c) != lampPos.end()
                )
                {
                    turnOnOff(r, c, grids, -1);
                }
            }
        }
        return result;
    }
};