/*
https://leetcode.com/problems/number-of-unique-flavors-after-sharing-k-candies/
2107. Number of Unique Flavors After Sharing K Candies

You are given a 0-indexed integer array candies, where candies[i] represents the flavor of the ith candy. Your mom wants
you to share these candies with your little sister by giving her k consecutive candies, but you want to keep as many
flavors of candies as possible.

Return the maximum number of unique flavors of candy you can keep after sharing with your sister.



Example 1:

Input: candies = [1,2,2,3,4,3], k = 3
Output: 3
Explanation:
Give the candies in the range [1, 3] (inclusive) with flavors [2,2,3].
You can eat candies with flavors [1,4,3].
There are 3 unique flavors, so return 3.
Example 2:

Input: candies = [2,2,2,2,3,3], k = 2
Output: 2
Explanation:
Give the candies in the range [3, 4] (inclusive) with flavors [2,3].
You can eat candies with flavors [2,2,2,3].
There are 2 unique flavors, so return 2.
Note that you can also share the candies with flavors [2,2] and eat the candies with flavors [2,2,3,3].
Example 3:

Input: candies = [2,4,5], k = 0
Output: 3
Explanation:
You do not have to give any candies.
You can eat the candies with flavors [2,4,5].
There are 3 unique flavors, so return 3.


Constraints:

0 <= candies.length <= 105
1 <= candies[i] <= 105
0 <= k <= candies.length
*/
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <map>
#include <unordered_set>
#include <algorithm>
#include <cmath>
#include <queue>
#include <stack>
#include <climits>
#include <set>
#include <numeric>
using namespace std;

class Solution {
public:
    int shareCandies(vector<int>& candies, int k) {
        int n = candies.size();
        if (k >= n) {
            return 0;
        }

        unordered_map<int, int> candy_cnt;
        for (int c : candies) {
            candy_cnt[c] += 1;
        }
        int type_cnt = candy_cnt.size();

        for (int i = 0; i < k; i++) {
            int cur_type = candies[i];
            if (candy_cnt[cur_type] == 1) {
                type_cnt -= 1;
            }
            candy_cnt[cur_type] -= 1;
        }
        int rst = type_cnt;

        for (int i = k; i < n; i++) {
            int cur_type = candies[i];
            if (candy_cnt[cur_type] == 1) {
                type_cnt -= 1;
            }
            candy_cnt[cur_type] -= 1;

            int j = i - k;
            int add_type = candies[j];
            if (candy_cnt.find(add_type) == candy_cnt.end() || candy_cnt[add_type] == 0) {
                type_cnt += 1;
            }
            candy_cnt[add_type] += 1;

            rst = max(rst, type_cnt);
        }
        return rst;
    }
};
