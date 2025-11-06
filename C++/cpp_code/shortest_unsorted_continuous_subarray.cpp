/*
581. Shortest Unsorted Continuous Subarray

Given an integer array,
you need to find one continuous subarray that if you only sort this subarray in ascending order,
then the whole array will be sorted in ascending order, too.

You need to find the shortest such subarray and output its length.

Example 1:
Input: [2, 6, 4, 8, 10, 9, 15]
Output: 5
Explanation: You need to sort [6, 4, 8, 10, 9] in ascending order to make the whole array sorted in ascending order.

Note:
Then length of the input array is in range [1, 10,000].
The input array may contain duplicates, so ascending order here means <=.
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
/*
III -- O(n) time one-pass solution

To understand this one-pass solution,
we need to introduce some equivalent mathematical models for describing a sorted array (assuming in ascending order).
Suppose the given array is nums with length n, these models are as follows:

nums[k] <= nums[k + 1] for all 0 <= k < n - 1.

nums[k] == max[k] for all 0 <= k <= n - 1, where max[k] is the maximum value of subarray nums[0, k].

nums[k] == min[k] for all 0 <= k <= n - 1, where min[k] is the minimum value of subarray nums[k, n - 1].

The first model is the most common one
(and probably the most familiar one) while the last two are less common.
It’s easy to show that the second model is equivalent to the first by noting that for any index k < n - 1,
we have max[k] <= max[k + 1], then nums[k] = max[k] <= max[k + 1] = nums[k + 1].
Similar results hold for the third model: nums[k] = min[k] <= min[k + 1] = nums[k + 1].

With these models in place,
we can show that if indices i and j satisfy the following conditions,
then nums[i, j] will be the shortest subarray we are looking for:

i is the smallest index such that nums[i] != min[i];
j is the largest index such that nums[j] != max[j].
The proof proceeds by showing that the two conditions above are equivalent to the three properties in part II.

Firstly we will show that the first property in part II is held true.
From condition 1, we have nums[k] == min[k] for all 0 <= k < i.
Then nums[k] = min[k] <= min[k + 1] = nums[k + 1] for all k < i - 1.
By definition, nums[0, i - 1] is sorted.
Similarly from condition 2, nums[k] == max[k] for all j < k <= n - 1.
Then nums[k] = max[k] <= max[k + 1] = nums[k + 1] for all j < k < n - 1.
By definition, nums[j + 1, n - 1] is sorted.

Then we will show the third property is satisfied.
Let min_m and max_m be the minimum and maximum values of subarray nums[i, j], respectively,
then we have min_m >= min[i] >= min[i - 1] = nums[i - 1] and max_m <= max[j] <= max[j + 1] = nums[j + 1].

Lastly we will show that the second property is also valid.
Note that if the first and third properties are both true,
then we know the subarray nums[0, i - 1] will be exactly the same as subarray nums_sorted[0, i - 1],
and the subarray nums[j + 1, n - 1] exactly the same as nums_sorted[j + 1, n - 1].
In this case just suppose we have nums[i] == nums_sorted[i] and nums[j] == nums_sorted[j],
let’s see what will happen.
Since the subarrays nums[i, n - 1] and nums_sorted[i, n - 1] contain exactly the same elements (though the order may be
different), then the minimum element of the former will be the same as the latter. Since nums_sorted[i, n - 1] is sorted
in ascending order, we will have min[i] = nums_sorted[i] = nums[i], which contradicts the assumption that nums[i] !=
min[i]. Similarly we can show that nums[j] == nums_sorted[j] implies nums[j] == max[j], which contradicts the assumption
that nums[j] != max[j].

Finding the smallest index i such that nums[i] != min[i] and the largest index j such that nums[j] != max[j] can be done
in one-pass, as shown below. Note that we don’t really need arrays to hold values for min[r] and max[l], by taking
advantage of the recurrence relation min[r] = Math.min(min[r + 1], nums[r]) and max[l] = Math.max(max[l - 1], nums[l]).
Also we initialized the indices i and j such that correct results will be returned even if the input array is already
sorted (which requires initially j - i + 1 = 0).
*/
class Solution {
public:
    int findUnsortedSubarray(vector<int>& nums) {
        int n = nums.size();
        if (n <= 1) {
            return 0;
        }

        int curMax = nums.front();
        int curMin = nums.back();
        int left = 0;
        int right = -1;
        for (int i = 1; i < n; i++) {
            if (nums[i] < curMax) {
                right = i;
            } else {
                curMax = nums[i];
            }
            if (nums[n - i - 1] > curMin) {
                left = n - i - 1;
            } else {
                curMin = nums[n - i - 1];
            }
        }
        return right - left + 1;
    }
};

class Solution1 {
public:
    int findUnsortedSubarray(vector<int>& nums) {
        if (nums.size() <= 1) {
            return 0;
        }

        vector<int> temp(nums);
        sort(temp.begin(), temp.end());
        int start = -1;
        int end = -1;
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] != temp[i]) {
                if (start == -1) {
                    start = i;
                } else {
                    end = i;
                }
            }
        }

        return start == -1 ? 0 : end - start + 1;
    }
};