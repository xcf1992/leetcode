/*
https://leetcode.com/problems/number-of-divisible-triplet-sums/description/
2964. Number of Divisible Triplet Sums

Given a 0-indexed integer array nums and an integer d, return the number of triplets (i, j, k) such that i < j < k and
(nums[i] + nums[j] + nums[k]) % d == 0.


Example 1:

Input: nums = [3,3,4,7,8], d = 5
Output: 3
Explanation: The triplets which are divisible by 5 are: (0, 1, 2), (0, 2, 4), (1, 2, 4).
It can be shown that no other triplet is divisible by 5. Hence, the answer is 3.
Example 2:

Input: nums = [3,3,3,3], d = 3
Output: 4
Explanation: Any triplet chosen here has a sum of 9, which is divisible by 3. Hence, the answer is the total number of
triplets which is 4. Example 3:

Input: nums = [3,3,3,3], d = 6
Output: 0
Explanation: Any triplet chosen here has a sum of 9, which is not divisible by 6. Hence, the answer is 0.


Constraints:

1 <= nums.length <= 1000
1 <= nums[i] <= 109
1 <= d <= 109
*/
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <cmath>
#include <map>
#include <queue>
#include <stack>
#include <climits>
using namespace std;

class Solution {
public:
    int divisibleTripletCount(vector<int>& nums, int d) {
        int n = nums.size();
        if (n <= 2) {
            return 0;
        }

        int rst = 0;
        unordered_map<int, int> mod_cnt;
        mod_cnt[nums[0] % d] += 1;
        for (int mid = 1; mid < n; mid++) {
            for (int right = mid + 1; right < n; right++) {
                int mod = (d - (nums[mid] % d + nums[right] % d) % d) % d;
                if (mod_cnt.find(mod) == mod_cnt.end()) {
                    continue;
                }
                rst += mod_cnt[mod];
            }
            mod_cnt[nums[mid] % d] += 1;
        }
        return rst;
    }
};
