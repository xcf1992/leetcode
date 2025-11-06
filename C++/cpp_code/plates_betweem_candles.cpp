/*
https://leetcode.com/problems/plates-between-candles/description/
2055. Plates Between Candles

There is a long table with a line of plates and candles arranged on top of it. You are given a 0-indexed string s
consisting of characters '*' and '|' only, where a '*' represents a plate and a '|' represents a candle.

You are also given a 0-indexed 2D integer array queries where queries[i] = [lefti, righti] denotes the substring
s[lefti...righti] (inclusive). For each query, you need to find the number of plates between candles that are in the
substring. A plate is considered between candles if there is at least one candle to its left and at least one candle to
its right in the substring.

For example, s = "||**||**|*", and a query [3, 8] denotes the substring "*||**|". The number of plates between candles
in this substring is 2, as each of the two plates has at least one candle in the substring to its left and right. Return
an integer array answer where answer[i] is the answer to the ith query.



Example 1:

ex-1
Input: s = "**|**|***|", queries = [[2,5],[5,9]]
Output: [2,3]
Explanation:
- queries[0] has two plates between candles.
- queries[1] has three plates between candles.
Example 2:

ex-2
Input: s = "***|**|*****|**||**|*", queries = [[1,17],[4,5],[14,17],[5,11],[15,16]]
Output: [9,0,0,0,0]
Explanation:
- queries[0] has nine plates between candles.
- The other queries have zero plates between candles.


Constraints:

3 <= s.length <= 105
s consists of '*' and '|' characters.
1 <= queries.length <= 105
queries[i].length == 2
0 <= lefti <= righti < s.length
*/
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include "extra_data_types.hpp"
using namespace std;

class Solution {
public:
    vector<int> platesBetweenCandles(string s, vector<vector<int>>& queries) {
        int n = s.size();
        vector<int> left(n, -1);
        int left_candle = -1;
        vector<int> right(n, n);
        int right_candle = n;
        vector<int> candle_cnt(n, 0);
        int cnt = 0;
        for (int i = 0; i < n; i++) {
            if (s[i] == '|') {
                left_candle = i;
                cnt += 1;
            }
            left[i] = left_candle;
            candle_cnt[i] = cnt;

            int j = n - 1 - i;
            if (s[j] == '|') {
                right_candle = j;
            }
            right[j] = right_candle;
        }

        vector<int> result;
        for (const vector<int>& q : queries) {
            int left_idx = right[q[0]];
            int right_idx = left[q[1]];
            if (left_idx >= right_idx) {
                result.push_back(0);
            } else {
                result.push_back(right_idx - left_idx + 1 - (candle_cnt[right_idx] - candle_cnt[left_idx] + 1));
            }
        }
        return result;
    }
};