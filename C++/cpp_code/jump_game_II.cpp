/*
45. Jump Game II
https://leetcode.com/problems/jump-game-ii/

Given an array of non-negative integers,
you are initially positioned at the first index of the array.

Each element in the array represents your maximum jump length at that position.
Your goal is to reach the last index in the minimum number of jumps.

Example:
Input: [2,3,1,1,4]
Output: 2
Explanation: The minimum number of jumps to reach the last index is 2.
Jump 1 step from index 0 to 1, then 3 steps to the last index.

Note:
You can assume that you can always reach the last index.
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
Intuition of the problem

We want to reach the end with the fewest jumps.

Each nums[i] tells us how far we can reach from i.

We can think of this as a breadth-first search (BFS) over array indices:

Each jump is like moving to the next layer in BFS.

Each layer covers all positions reachable with the same number of jumps.

But instead of literally running BFS (which is O(n²)), we can simulate it greedily in O(n).

🔍 Meaning of the variables
Variable	Meaning
result	How many jumps we have taken so far
curMax	The farthest index we can reach from all positions seen so far
lastMax	The end boundary of the current jump — i.e. the farthest we can go with the current number of jumps
 */
class Solution {
public:
    int jump(vector<int>& nums) {
        int n = nums.size();
        if (n <= 1) {
            return 0;
        }

        int result = 1;
        int curMax = nums[0];
        int lastMax = nums[0];
        for (int i = 1; i < n; ++i) {
            if (i > lastMax) {
                lastMax = curMax;
                result += 1;
            }
            curMax = max(curMax, i + nums[i]);
        }
        return result;
    }
};