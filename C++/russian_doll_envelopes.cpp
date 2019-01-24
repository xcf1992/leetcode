/*
 354. Russian Doll Envelopes

 You have a number of envelopes with widths and heights given as a pair of integers (w, h). One envelope can fit into another if and only if both the width and height of one envelope is greater than the width and height of the other envelope.

 What is the maximum number of envelopes can you Russian doll? (put one inside other)

 Note:
 Rotation is not allowed.

 Example:

 Input: [[5,4],[6,4],[6,7],[2,3]]
 Output: 3
 Explanation: The maximum number of envelopes you can Russian doll is 3 ([2,3] => [5,4] => [6,7]).
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

class Solution {
public:
    int maxEnvelopes(vector<pair<int, int>>& envelopes) {
        int n = envelopes.size();
        if (n <= 1) {
            return n;
        }
        sort(envelopes.begin(), envelopes.end(), [](pair<int, int>& a, pair<int, int>& b) {
            return a.first < b.first or (a.first == b.first and a.second < b.second);
        });

        vector<int> dp(n, 1);
        int result = 1;
        for (int i = 1; i < n; i++) {
            for (int j = 0; j < i; j++) {
                if (envelopes[i].first > envelopes[j].first and envelopes[i].second > envelopes[j].second) {
                    dp[i] = max(dp[i], dp[j] + 1);
                }
            }
            result = max(result, dp[i]);
        }
        return result;
    }
};
