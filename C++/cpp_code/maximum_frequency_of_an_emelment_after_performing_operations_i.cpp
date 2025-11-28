/*
https://leetcode.com/problems/maximum-frequency-of-an-element-after-performing-operations-i/description/
3346. Maximum Frequency of an Element After Performing Operations I

You are given an integer array nums and two integers k and numOperations.

You must perform an operation numOperations times on nums, where in each operation you:

Select an index i that was not selected in any previous operations.
Add an integer in the range [-k, k] to nums[i].
Return the maximum possible frequency of any element in nums after performing the operations.



Example 1:

Input: nums = [1,4,5], k = 1, numOperations = 2

Output: 2

Explanation:

We can achieve a maximum frequency of two by:

Adding 0 to nums[1]. nums becomes [1, 4, 5].
Adding -1 to nums[2]. nums becomes [1, 4, 4].
Example 2:

Input: nums = [5,11,20,20], k = 5, numOperations = 1

Output: 2

Explanation:

We can achieve a maximum frequency of two by:

Adding 0 to nums[1].


Constraints:

1 <= nums.length <= 105
1 <= nums[i] <= 105
0 <= k <= 105
0 <= numOperations <= nums.length
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
We want to maximize the frequency of a target value target, to do that, we can transform elements in the range
[target−k,target+k] to become target by adding appropriate values.

For example, if target=5 and k=2:

Element 3 can become 5 by adding +2
Element 7 can become 5 by adding −2
Element 4 can become 5 by adding +1
Instead of trying all possible transformations, we use a frequency counting approach combined with prefix sums to
efficiently compute how many elements can be transformed to each possible target value.

First, we track how many times each value appears in the original array
Next, Create a prefix sum array for range queries
Then, For each potential target value, calculate how many elements can be transformed to it
he answer is the maximum achievable frequency across all targets
For a target value i, we can calculate:

total=count[i+k]−count[i−k−1]
​

This gives us the total number of elements that can be transformed to i.

The maximum frequency for target i is:

res=freq+min(numOps,total−freq)
​

Where:

freq = elements already equal to i
total−freq = elements in range that can become i (excluding those already equal)
Try all possible target values:

For each potential target i from 0 to maxVal−1:
 */
class Solution {
public:
    int maxFrequency(vector<int>& nums, int k, int numOperations) {
        int max_val = *max_element(nums.begin(), nums.end()) + k + 2;
        vector<int> count(max_val, 0);

        for (int v : nums) {
            count[v]++;
        }

        for (int i = 1; i < max_val; i++) {
            count[i] += count[i - 1];
        }

        int rst = 0;
        for (int i = 0; i < max_val; i++) {
            int left = max(0, i - k);
            int right = min(max_val - 1, i + k);
            int total = count[right] - (left != 0 ? count[left - 1] : 0);
            int freq = count[i] - (i != 0 ? count[i - 1] : 0);
            rst = max(rst, freq + min(numOperations, total - freq));
        }
        return rst;
    }
};
