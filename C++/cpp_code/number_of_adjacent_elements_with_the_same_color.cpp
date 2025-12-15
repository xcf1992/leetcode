/*
https://leetcode.com/problems/number-of-adjacent-elements-with-the-same-color/description/
2672. Number of Adjacent Elements With the Same Color

You are given an integer n representing an array colors of length n where all elements are set to 0's meaning uncolored.
You are also given a 2D integer array queries where queries[i] = [indexi, colori]. For the ith query:

Set colors[indexi] to colori.
Count the number of adjacent pairs in colors which have the same color (regardless of colori).
Return an array answer of the same length as queries where answer[i] is the answer to the ith query.



Example 1:

Input: n = 4, queries = [[0,2],[1,2],[3,1],[1,1],[2,1]]

Output: [0,1,1,0,2]

Explanation:

Initially array colors = [0,0,0,0], where 0 denotes uncolored elements of the array.
After the 1st query colors = [2,0,0,0]. The count of adjacent pairs with the same color is 0.
After the 2nd query colors = [2,2,0,0]. The count of adjacent pairs with the same color is 1.
After the 3rd query colors = [2,2,0,1]. The count of adjacent pairs with the same color is 1.
After the 4th query colors = [2,1,0,1]. The count of adjacent pairs with the same color is 0.
After the 5th query colors = [2,1,1,1]. The count of adjacent pairs with the same color is 2.
Example 2:

Input: n = 1, queries = [[0,100000]]

Output: [0]

Explanation:

After the 1st query colors = [100000]. The count of adjacent pairs with the same color is 0.



Constraints:

1 <= n <= 105
1 <= queries.length <= 105
queries[i].length == 2
0 <= indexi <= n - 1
1 <=  colori <= 105
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
#include <set>
using namespace std;

class Solution {
public:
    vector<int> colorTheArray(int n, vector<vector<int>>& queries) {
        int query_len = queries.size();
        vector<int> rst(query_len, 0);
        int cnt = 0;
        vector<int> cur_color(n, 0);
        for (int i = 0; i < query_len; i++) {
            int idx = queries[i][0];
            int new_color = queries[i][1];
            if (cur_color[idx] == 0) {
                if (idx != 0) {
                    cnt += cur_color[idx - 1] == new_color ? 1 : 0;
                }
                if (idx != n - 1) {
                    cnt += cur_color[idx + 1] == new_color ? 1 : 0;
                }
            } else {
                if (idx != 0) {
                    cnt += cur_color[idx - 1] == new_color ? 1 : 0;
                    cnt += cur_color[idx - 1] == cur_color[idx] ? -1 : 0;
                }
                if (idx != n - 1) {
                    cnt += cur_color[idx + 1] == new_color ? 1 : 0;
                    cnt += cur_color[idx + 1] == cur_color[idx] ? -1 : 0;
                }
            }

            rst[i] = cnt;
            cur_color[idx] = new_color;
        }
        return rst;
    }
};
