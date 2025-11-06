/*
354. Russian Doll Envelopes

You have a number of envelopes with widths and heights given as a pair of integers (w, h).
One envelope can fit into another if and only if both the width and height of one envelope
is greater than the width and height of the other envelope.

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
/*
Based on the width of each envelopes we will divide all the envelopes into several groups,
each group will be ordered in increasing order of width,
and in each group will sort the envelop in decreasing order of the height.

So it will be something like: W1 < W2 < ... < Wi
.........W1............. | .........W2............   |  .........Wi.............
[H1, H1-1, H1-2...H1-k1], [H2, H2-1, H2-2...H2-k2],..., [Hi, Hi-1, Hi-2...Hi-ki]

Then the question becomes find the longest increasing sequence by picking one element from each group.
300. Longest Increasing Subsequenc
*/
class Solution {
public:
    int maxEnvelopes(vector<vector<int>>& envelopes) {
        int n = envelopes.size();
        if (n <= 1) {
            return n;
        }
        /*
         * Since the width is increasing, we only need to consider height.
         * [3, 4] cannot contains [3, 3], so we need to put [3, 4] before [3, 3]
         * when sorting otherwise it will be counted as an increasing number if the order is [3, 3], [3, 4]
         */
        sort(envelopes.begin(), envelopes.end(),
             [](vector<int>& a, vector<int>& b) { return a[0] < b[0] or (a[0] == b[0] and a[1] > b[1]); });
        /*
         * as we sort the envelopes to a increasing array based on width
         * but for the envelopes with the same width we put envelope with biggest height first
         * thus we need to find the length of longest increasing subsequnce from this array based on height
         */
        vector<int> result;
        for (int i = 0; i < n; i++) {
            auto it = lower_bound(result.begin(), result.end(), envelopes[i][1]);
            if (it != result.end()) {
                *it = envelopes[i][1];
            } else {
                result.push_back(envelopes[i][1]);
            }
        }
        return result.size();
    }
};

class Solution1 {
public:
    int maxEnvelopes(vector<vector<int>>& envelopes) {
        int n = envelopes.size();
        if (n <= 1) {
            return n;
        }

        sort(envelopes.begin(), envelopes.end(),
             [](vector<int>& a, vector<int>& b) { return a[0] < b[0] or (a[0] == b[0] and a[1] < b[1]); });

        vector<int> dp(n, 1);
        int result = 1;
        for (int i = 1; i < n; i++) {
            for (int j = 0; j < i; j++) {
                if (envelopes[i][0] > envelopes[j][0] and envelopes[i][1] > envelopes[j][1]) {
                    dp[i] = max(dp[i], dp[j] + 1);
                }
            }
            result = max(result, dp[i]);
        }
        return result;
    }
};