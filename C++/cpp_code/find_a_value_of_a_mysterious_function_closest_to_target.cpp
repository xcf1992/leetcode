/*
1521. Find a Value of a Mysterious Function Closest to Target
https://leetcode.com/problems/find-a-value-of-a-mysterious-function-closest-to-target/

func(arr, l, r) {
    if (r < l) {
        return -100000000
    }

    ans = arr[l]
    for (int i = l + 1; i <= r; ++i) {
        ans = ans & arr[i]
    }
    return ans
}

Winston was given the above mysterious function func.
He has an integer array arr and an integer target
and he wants to find the values l and r that make the value |func(arr, l, r) - target| minimum possible.

Return the minimum possible value of |func(arr, l, r) - target|.

Notice that func should be called with the values l and r where 0 <= l, r < arr.length.

Example 1:
Input: arr = [9,12,3,7,15], target = 5
Output: 2
Explanation: Calling func with all the pairs of [l,r] =
[[0,0],[1,1],[2,2],[3,3],[4,4],[0,1],[1,2],[2,3],[3,4],[0,2],[1,3],[2,4],[0,3],[1,4],[0,4]], Winston got the following
results [9,12,3,7,15,8,0,3,7,0,0,3,0,0,0]. The value closest to 5 is 7 and 3, thus the minimum difference is 2.

Example 2:
Input: arr = [1000000,1000000,1000000], target = 1
Output: 999999
Explanation: Winston called the func with all possible values of [l,r] and he always got 1000000, thus the min
difference is 999999.

Example 3:
Input: arr = [1,2,4,8,16], target = 0
Output: 0

Constraints:
1 <= arr.length <= 10^5
1 <= arr[i] <= 10^6
0 <= target <= 10^7
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
#include <set>
using namespace std;
// https://leetcode.com/problems/find-a-value-of-a-mysterious-function-closest-to-target/discuss/743267/C%2B%2B-O(N)-Algorithm-with-detailed-explanation-improved-from-O(N(log(N))
class Solution {
public:
    int closestToTarget(vector<int>& arr, int target) {
        int len = (int)arr.size();
        vector<vector<int>> tab(30);
        for (int i = 0; i < len; i++)
            for (int j = 0; j < 30; j++)
                if ((arr[i] >> j) & 1)
                    tab[j].push_back(i);

        vector<int> dp(len + 1);
        dp[len] = arr[0];  // dummy value to avoid "index out of range"
        int ans = abs(arr[0] - target);
        int l = len - 1;
        for (int i = len - 1; i >= 0; i--) {
            for (int j = 0; j < 30; j++)
                if (!((arr[i] >> j) & 1))
                    while (!tab[j].empty() && tab[j].back() > i) {
                        dp[tab[j].back()] -= 1 << j;
                        tab[j].pop_back();
                    }
            dp[i] = arr[i];

            while (l > i && dp[l] < target)
                l--;  // After this line, we have dp[l] >= target, dp[l + 1] < target, or l == i and all elements in
                      // this new sequence is smaller than target
            ans = min(ans, min(abs(target - dp[l]), abs(target - dp[l + 1])));
        }
        return ans;
    }
};
