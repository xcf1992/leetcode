/*
377. Combination Sum IV
https://leetcode.com/problems/combination-sum-iv/

Given an integer array with all positive numbers and no duplicates,
find the number of possible combinations that add up to a positive integer target.

Example:
nums = [1, 2, 3]
target = 4
The possible combination ways are:
(1, 1, 1, 1)
(1, 1, 2)
(1, 2, 1)
(1, 3)
(2, 1, 1)
(2, 2)
(3, 1)

Note that different sequences are counted as different combinations.

Therefore the output is 7.

Follow up:
What if negative numbers are allowed in the given array?
How does it change the problem?
What limitation we need to add to the question to allow negative numbers?

Credits:
Special thanks to @pbrother for adding this problem and creating all test cases.
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
using namespace std;
/*
https://leetcode.com/problems/combination-sum-iv/discuss/85074/6-lines-C%2B%2B-DP-solution
some interesting discussions around test case
[3,33,333]
10000

The problem with negative numbers is that now the combinations could be potentially of infinite length.
Think about nums = [-1, 1] and target = 1.
We can have all sequences of arbitrary length that follow the patterns -1, 1, -1, 1, ..., -1, 1, 1
and 1, -1, 1, -1, ..., 1, -1, 1 (there are also others, of course, just to give an example).
So we should limit the length of the combination sequence,
so as to give a bound to the problem.
*/
class Solution { // bottom up
public:
    int combinationSum4(vector<int>& nums, int target) {
        int n = nums.size();
        if (n <= 0) {
            return 0;
        }

        vector<unsigned int> dp(target + 1, 0);
        dp[0] = 1;
        for (int i = 1; i <= target; ++i) {
            for (int num : nums) if (i >= num) {
                dp[i] += dp[i - num];
            }
        }
        return dp[target];
    }
};

class Solution1 { // top down
private:
    unordered_map<int, int> combination;
public:
    int combinationSum4(vector<int>& nums, int target) {
        if (target == 0) {
            return 1;
        }

        if (target < 0) {
            return 0;
        }

        if (combination.find(target) != combination.end()) {
            return combination[target];
        }

        combination[target] = 0;
        for (int i = 0; i < nums.size(); i++) {
            combination[target] += combinationSum4(nums, target - nums[i]);
        }
        return combination[target];
    }
};
