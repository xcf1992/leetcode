/*
https://leetcode.com/problems/minimum-size-subarray-sum/
209. Minimum Size Subarray Sum

Given an array of n positive integers and a positive integer s,
find the minimal length of a contiguous subarray of which the sum ≥ s.
If there isn't one, return 0 instead.

Example:
Input: s = 7, nums = [2,3,1,2,4,3]
Output: 2
Explanation: the subarray [4,3] has the minimal length under the problem constraint.

Follow up:
If you have figured out the O(n) solution, try coding another solution of which the time complexity is O(n log n).
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
#include <numeric>
using namespace std;

class Solution {
    // O(nlogn)
public:
    int minSubArrayLen(int s, vector<int>& nums) {
        int n = nums.size();
        vector<int> preSum(n + 1, 0);
        for (int i = 0; i < n; i++) {
            preSum[i + 1] = preSum[i] + nums[i];
        }

        int result = n + 1;
        for (int i = 0; i <= n; ++i) {
            int target = preSum[i] + s;
            auto it = lower_bound(preSum.begin(), preSum.end(), target);
            if (it != preSum.end()) {
                int index = it - preSum.begin();
                result = min(result, index - i);
            } else {
                break;
            }
        }
        return result == n + 1 ? 0 : result;
    }
};

/*
The O(n) solution is to use two pointers: l and r.
First we move r until we get a sum >= s,
then we move l to the right until sum < s.
In this process, store the minimum length between l and r.
Since each element in nums will be visited by l and r for at most once.
This algorithm is of O(n) time.
*/
class Solution1 {
    // O(n)
public:
    int minSubArrayLen(int s, vector<int>& nums) {
        int n = nums.size();
        int result = n + 1;
        int left = 0;
        int sum = 0;
        for (int i = 0; i < n; ++i) {
            sum += nums[i];
            while (sum >= s) {
                result = min(result, i - left + 1);
                sum -= nums[left];
                left += 1;
            }
        }
        return result == n + 1 ? 0 : result;
    }
};

class Solution2 {
public:
    int minSubArrayLen(int s, vector<int>& nums) {
        int n = nums.size();
        vector<int> preSum(n + 1, 0);
        for (int i = 0; i < n; i++) {
            preSum[i + 1] = preSum[i] + nums[i];
        }

        int result = n;
        if (preSum.back() < s) {
            return 0;
        }

        queue<int> que;
        for (int i = 1; i <= n; ++i) {
            if (preSum[i] >= s) {
                result = min(result, i);
                while (!que.empty() and preSum[i] - preSum[que.front()] >= s) {
                    result = min(result, i - que.front());
                    que.pop();
                }
            }
            que.push(i);
        }
        return result;
    }
};