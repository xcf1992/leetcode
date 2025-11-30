/*
1144. Decrease Elements To Make Array Zigzag
https://leetcode.com/problems/decrease-elements-to-make-array-zigzag/

Given an array nums of integers,
a move consists of choosing any element and decreasing it by 1.
An array A is a zigzag array if either:
Every even-indexed element is greater than adjacent elements,
ie. A[0] > A[1] < A[2] > A[3] < A[4] > ...
OR, every odd-indexed element is greater than adjacent elements,
ie. A[0] < A[1] > A[2] < A[3] > A[4] < ...
Return the minimum number of moves to transform the given array nums into a zigzag array.

Example 1:
Input: nums = [1,2,3]
Output: 2
Explanation: We can decrease 2 to 0 or 3 to 1.

Example 2:
Input: nums = [9,6,1,6,2]
Output: 4

Constraints:
1 <= nums.length <= 1000
1 <= nums[i] <= 1000
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
/*
Explanation
Two options, either make A[even] smaller or make A[odd] smaller.
Loop on the whole array A,
find the min(A[i - 1],A[i + 1]),
calculate that the moves need to make smaller than both side.
If it's negative, it means it's already smaller than both side, no moved needed.
Add the moves need to res[i % 2].
In the end return the smaller option.

Complexity
Time O(N) for one pass
Space O(2) for two options
https://leetcode.com/problems/decrease-elements-to-make-array-zigzag/discuss/350576/JavaC%2B%2BPython-Easy-and-concise
*/
class Solution {
public:
    int movesToMakeZigzag(vector<int>& nums) {
        vector<int> result(2, 0);
        int n = nums.size();
        for (int i = 0; i < n; ++i) {
            int left = i > 0 ? nums[i - 1] : 1001;
            int right = i + 1 < n ? nums[i + 1] : 1001;
            result[i % 2] += max(0, nums[i] - min(left, right) + 1);
        }
        return min(result[0], result[1]);
    }
};

class Solution1 {
private:
    void getCount(vector<int> nums, int& count, int start) {
        int n = nums.size();
        for (int i = start; i < n; i += 2) {
            if (i > 0 and nums[i - 1] >= nums[i]) {
                count += nums[i - 1] - nums[i] + 1;
                nums[i - 1] = nums[i] - 1;
            }
            if (i < n - 1 and nums[i + 1] >= nums[i]) {
                count += nums[i + 1] - nums[i] + 1;
                nums[i + 1] = nums[i] - 1;
            }
        }
    }

public:
    int movesToMakeZigzag(vector<int>& nums) {
        int n = nums.size();
        if (n <= 1) {
            return 0;
        }

        int count1 = 0;
        getCount(nums, count1, 0);
        int count2 = 0;
        getCount(nums, count2, 1);
        return min(count1, count2);
    }
};