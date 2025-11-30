/*
1240. Tiling a Rectangle with the Fewest Squares
https://leetcode.com/problems/tiling-a-rectangle-with-the-fewest-squares/

Given a rectangle of size n x m, find the minimum number of integer-sided squares that tile the rectangle.

Example 1:
Input: n = 2, m = 3
Output: 3
Explanation: 3 squares are necessary to cover the rectangle.
2 (squares of 1x1)
1 (square of 2x2)

Example 2:
Input: n = 5, m = 8
Output: 5

Example 3:
Input: n = 11, m = 13
Output: 6

Constraints:
1 <= n <= 13
1 <= m <= 13
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
/*
The basic idea is to fill the entire block bottom up.
In every step, find the lowest left unfilled square first,
and select a square with different possible sizes to fill it.
We maintain a height array (skyline) with length n while dfs.
This skyline is the identity of the state.
The final result we ask for is the minimum number of squares for the state [m, m, m, m, m, m, m] (The length of this
array is n). Of course, backtrack without optimization will have a huge time complexity, but it can be pruned or
optimized by the following three methods.

When the current cnt (that is, the number of squares) of this skyline has exceeded the value of the current global
optimal solution, then return directly.

When the current skyline has been traversed,
and the previous cnt is smaller than the current cnt, then return directly.

When we find the empty square in the lowest left corner,
we pick larger size for the next square first.
This can make the program converge quickly. (It is a very important optimization)
*/
typedef long long Key;

class Solution {
private:
    unordered_map<Key, int> memo;
    int maxDepth;

    Key getKey(vector<int>& nums) {
        Key key = 0;
        for (int num : nums) {
            key = (key << 4LL) + num;
        }
        return key;
    }

    void dfs(vector<int>& height, int curDepth) {
        Key hkey = getKey(height);
        if (hkey == 0) {
            maxDepth = min(maxDepth, curDepth);
            return;
        }

        if (curDepth >= maxDepth or memo.find(hkey) != memo.end()) {
            return;
        }

        auto topLeft = max_element(height.begin(), height.end());
        int width = 1;
        for (auto top = topLeft + 1; top != height.end() and *top == *topLeft; ++top) {
            width += 1;
        }

        for (int w = min(width, *topLeft); w > 0; --w) {
            for (int i = 0; i < w; ++i) {
                *(topLeft + i) -= w;
            }
            dfs(height, curDepth + 1);
            for (int i = 0; i < w; ++i) {
                *(topLeft + i) += w;
            }
        }
    }

public:
    int tilingRectangle(int n, int m) {
        if (n > m) {
            swap(n, m);
        }
        vector<int> height;
        for (int i = 0; i < n; ++i) {
            height.push_back(m);
        }

        maxDepth = m;
        dfs(height, 0);
        return maxDepth;
    }
};
