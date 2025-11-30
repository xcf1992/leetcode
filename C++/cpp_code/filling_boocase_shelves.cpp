/*
1105. Filling Bookcase Shelves
https://leetcode.com/problems/filling-bookcase-shelves/

We have a sequence of books:
the i-th book has thickness books[i][0] and height books[i][1].
We want to place these books in order onto bookcase shelves that have total width shelf_width.

We choose some of the books to place on this shelf
(such that the sum of their thickness is <= shelf_width),
then build another level of shelf of the bookcase
so that the total height of the bookcase has increased by the maximum height of the books we just put down.
We repeat this process until there are no more books to place.

Note again that at each step of the above process,
the order of the books we place is the same order as the given sequence of books.
For example, if we have an ordered list of 5 books,
we might place the first and second book onto the first shelf,
the third book on the second shelf,
and the fourth and fifth book on the last shelf.

Return the minimum possible height that the total bookshelf can be after placing shelves in this manner.

Example 1:
Input: books = [[1,1],[2,3],[2,3],[1,1],[1,1],[1,1],[1,2]], shelf_width = 4
Output: 6
Explanation:
The sum of the heights of the 3 shelves are 1 + 3 + 2 = 6.
Notice that book number 2 does not have to be on the first shelf.

Constraints:
1 <= books.length <= 1000
1 <= books[i][0] <= shelf_width <= 1000
1 <= books[i][1] <= 1000
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
定义dp[i]为前i本书能够到达的最小高度。
则对于第i+1本书，有若干选择。
如自己单独一层，则状态转移为dp[i+1] = dp[i] + h[i+1]

如果和前面的书放在一起，则状态转移方程式dp[i+1] = min(dp[j] + max[h[j+1] ~ h[i+1])),
其中需要满足sum(w[j+1] ~ w[i+1]) <= shelf_width，含义是前j本书组成若干层，
第j+1到第i+1本书组成一层。
对于这些选择，取最小值。
*/
class Solution {
    // dp
public:
    int minHeightShelves(vector<vector<int>>& books, int shelf_width) {
        int n = books.size();
        vector<int> dp(n + 1, 1000 * 1000);
        dp[0] = 0;
        for (int i = 1; i <= n; ++i) {
            int w = books[i - 1][0];
            int h = books[i - 1][1];

            dp[i] = dp[i - 1] + h;
            for (int j = i - 1; j > 0; --j) {
                w += books[j - 1][0];
                h = max(h, books[j - 1][1]);
                if (w > shelf_width) {
                    break;
                }
                dp[i] = min(dp[i], dp[j - 1] + h);
            }
        }
        return dp[n];
    }
};

class Solution1 {
    // dfs with memo
private:
    unordered_map<int, int> memo;  // memo[i] means the min height needed to store books from i ~ n - 1
    int n = 0;

    int dfs(vector<vector<int>>& books, int index, int shelf_width) {
        if (index == n) {
            return 0;
        }

        if (memo.find(index) != memo.end()) {
            return memo[index];
        }

        int curWidth = books[index][0];
        int height = books[index][1];
        memo[index] = height + dfs(books, index + 1, shelf_width);
        for (int i = index + 1; i < n; ++i) {
            if (curWidth + books[i][0] > shelf_width) {
                break;
            }
            height = max(height, books[i][1]);
            memo[index] = min(memo[index], height + dfs(books, i + 1, shelf_width));
            curWidth += books[i][0];
        }
        return memo[index];
    }

public:
    int minHeightShelves(vector<vector<int>>& books, int shelf_width) {
        n = books.size();
        return dfs(books, 0, shelf_width);
    }
};