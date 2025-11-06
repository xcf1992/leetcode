/*
699. Falling Squares

On an infinite number line (x-axis),
we drop given squares in the order they are given.

The i-th square dropped (positions[i] = (left, side_length))
is a square with the left-most point being positions[i][0] and sidelength positions[i][1].

The square is dropped with the bottom edge parallel to the number line,
and from a higher height than all currently landed squares.
We wait for each square to stick before dropping the next.

The squares are infinitely sticky on their bottom edge,
and will remain fixed to any positive length surface they touch
(either the number line or another square).
Squares dropped adjacent to each other will not stick together prematurely.

Return a list ans of heights.
Each height ans[i] represents the current highest height of any square we have dropped,
after dropping squares represented by positions[0], positions[1], ..., positions[i].

Example 1:
Input: [[1, 2], [2, 3], [6, 1]]
Output: [2, 5, 5]
Explanation:

After the first drop of positions[0] = [1, 2]:
_aa
_aa
-------
The maximum height of any square is 2.

After the second drop of positions[1] = [2, 3]:
__aaa
__aaa
__aaa
_aa__
_aa__
--------------
The maximum height of any square is 5.
The larger square stays on top of the smaller square despite where its center
of gravity is, because squares are infinitely sticky on their bottom edge.

After the third drop of positions[1] = [6, 1]:
__aaa
__aaa
__aaa
_aa
_aa___a
--------------
The maximum height of any square is still 5.
Thus, we return an answer of [2, 5, 5].

Example 2:
Input: [[100, 100], [200, 100]]
Output: [100, 100]
Explanation: Adjacent squares don't get stuck prematurely - only their bottom edge can stick to surfaces.

Note:
1 <= positions.length <= 1000.
1 <= positions[i][0] <= 10^8.
1 <= positions[i][1] <= 10^6.
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
#include <numeric>
using namespace std;
/*
1. first get sorted coordinates from all squares.
2. index the sorted coordinates from left to right.
3. for each droped square we need to update height from index[pos[0]] to index[pos[0] + pos[1] - 1],
   while index is a map from coordinate to the index of this coordinate in sorted coordinates.
   The new height = current height + the length of dropped square.
4. then we need to update new height from index[pos[0]] to index[pos[0] + pos[1] - 1].

The key point of this solution is we first get all sorted coordinates of droped squares,
and map the coordinates to index.
So we can easily update and query height.
*/
class Solution {
private:
    int query(int left, int right, vector<int>& heights) {
        int height = 0;
        for (int i = left; i <= right; i++) {
            height = max(height, heights[i]);
        }
        return height;
    }

    void update(int left, int right, int height, vector<int>& heights) {
        for (int i = left; i <= right; i++) {
            heights[i] = height;
        }
    }

public:
    vector<int> fallingSquares(vector<vector<int>>& positions) {
        unordered_set<int> coords;
        for (vector<int>& pos : positions) {
            coords.insert(pos[0]);
            coords.insert(pos[0] + pos[1] - 1);
        }

        vector<int> sortedCoords(coords.begin(), coords.end());
        sort(sortedCoords.begin(), sortedCoords.end());

        unordered_map<int, int> index;
        for (int i = 0; i < sortedCoords.size(); i++) {
            index[sortedCoords[i]] = i;
        }

        vector<int> heights(sortedCoords.size(), 0);
        vector<int> result;
        int current = 0;
        for (vector<int>& pos : positions) {
            int left = index[pos[0]];
            int right = index[pos[0] + pos[1] - 1];

            int height = query(left, right, heights) + pos[1];
            update(left, right, height, heights);

            current = max(current, height);
            result.push_back(current);
        }
        return result;
    }
};