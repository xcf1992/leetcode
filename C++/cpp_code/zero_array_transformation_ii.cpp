/*
https://leetcode.com/problems/zero-array-transformation-ii/description/
3356. Zero Array Transformation II

You are given an integer array nums of length n and a 2D array queries where queries[i] = [li, ri, vali].

Each queries[i] represents the following action on nums:

Decrement the value at each index in the range [li, ri] in nums by at most vali.
The amount by which each value is decremented can be chosen independently for each index.
A Zero Array is an array with all its elements equal to 0.

Return the minimum possible non-negative value of k, such that after processing the first k queries in sequence, nums
becomes a Zero Array. If no such k exists, return -1.



Example 1:

Input: nums = [2,0,2], queries = [[0,2,1],[0,2,1],[1,1,3]]

Output: 2

Explanation:

For i = 0 (l = 0, r = 2, val = 1):
Decrement values at indices [0, 1, 2] by [1, 0, 1] respectively.
The array will become [1, 0, 1].
For i = 1 (l = 0, r = 2, val = 1):
Decrement values at indices [0, 1, 2] by [1, 0, 1] respectively.
The array will become [0, 0, 0], which is a Zero Array. Therefore, the minimum value of k is 2.
Example 2:

Input: nums = [4,3,2,1], queries = [[1,3,2],[0,2,1]]

Output: -1

Explanation:

For i = 0 (l = 1, r = 3, val = 2):
Decrement values at indices [1, 2, 3] by [2, 2, 1] respectively.
The array will become [4, 1, 0, 0].
For i = 1 (l = 0, r = 2, val = 1):
Decrement values at indices [0, 1, 2] by [1, 1, 0] respectively.
The array will become [3, 0, 0, 0], which is not a Zero Array.


Constraints:

1 <= nums.length <= 105
0 <= nums[i] <= 5 * 105
1 <= queries.length <= 105
queries[i].length == 3
0 <= li <= ri < nums.length
1 <= vali <= 5
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
Intuition
In our previous approach, we used binary search to determine how many queries were needed to turn nums into a zero
array. This allowed us to efficiently process a subset of queries, applying them to a difference array, and then
checking if nums had become all zeros. While this was an improvement over a naive approach, there was still an
inefficiency: we were iterating over queries twice: once for binary search and again while applying updates.

To optimize further, we can change our perspective on how we traverse the data. Instead of iterating through queries, we
can iterate directly through nums, using it as the main loop. This means that as we process each element in nums, we
dynamically apply only the necessary queries at the right moment. The key challenge, then, is finding an efficient way
to apply queries while moving through nums.

This is where a line sweep approach comes into play. Line sweeping is a technique that processes an array incrementally,
maintaining only the relevant updates at each step. Instead of processing all queries upfront, we maintain an active set
of queries and update nums only when necessary. Here, the difference array helps us track how nums is being modified,
while queries provide the updates at specific points.

We start at index 0 of nums and check if it can be turned into 0 with the queries we have processed so far. If it cannot
be zeroed out, we process additional queries to apply their effects. The key observation is that at any index i in nums,
a query [left, right, val] can fall into three possible cases:

If i < left, the query affects a later part of nums, so we store it for later processing.
If left ≤ i ≤ right, the query is immediately relevant and should be applied.
If right < i, the query is no longer useful for the current index and can be ignored.
For example, if we're at index 4 in nums and the current query accesses the range [0,2], we do not need to process that
query and can simply move on to the next query.

Otherwise, we continue to the next element of nums. We repeat this process until we reach the end of either nums or
queries, where we then return either k or -1, respectively.

Through this process, we only have to iterate through both nums and queries at most once each while skipping over
unnecessary queries.

Algorithm
Initialize:
n to the size of nums.
sum to 0 to track the cumulative sum of updates applied up to a given index
k to 0 to represent the number of queries used.
differenceArray as a vector of integers set to size n + 1 to apply range updates.
Iterate through nums. For each index:
If sum + differenceArray[index] is less than nums[index], meaning more operations need to be applied at the current
index: Increase k by 1. If k is greater than the size of queries, return -1, since we processed all the queries without
reaching a zero array. Initialize left, right, and val to the respective values of the current query. If right is
greater than or equal to index: Increment differenceArray[max(left, index)] by val to update the start of the range.
Decrement differenceArray[right + 1] by val to update the end of the range.
Increment sum by differenceArray[index].
Return k.
 */
class Solution {
public:
    int minZeroArray(vector<int>& nums, vector<vector<int>>& queries) {
        int n = nums.size();
        int sum = 0;
        int res = 0;
        vector<int> prefix(n + 1, 0);
        for (int i = 0; i < n; i++) {
            while (sum + prefix[i] < nums[i]) {
                res += 1;
                if (res > queries.size()) {
                    return -1;
                }

                int left = queries[res - 1][0];
                int right = queries[res - 1][1];
                int val = queries[res - 1][2];
                if (right >= i) {
                    prefix[max(left, i)] += val;
                    prefix[right + 1] -= val;
                }
            }
            sum += prefix[i];
        }
        return res;
    }
};

class Solution1 {
private:
    bool valid(vector<int>& nums, vector<int>& prefix_sum) {
        int sum = 0;
        for (int i = 0; i < nums.size(); i++) {
            sum += prefix_sum[i];
            if (sum < nums[i]) {
                return false;
            }
        }
        return true;
    }

    vector<int> build_prefix_sum(vector<int>& nums, vector<vector<int>>& queries, int cnt) {
        int n = nums.size();
        vector<int> prefix_sum(n + 1, 0);
        for (int j = 0; j < cnt; j++) {
            prefix_sum[queries[j][0]] += queries[j][2];
            prefix_sum[queries[j][1] + 1] -= queries[j][2];
        }
        return prefix_sum;
    }

public:
    int minZeroArray(vector<int>& nums, vector<vector<int>>& queries) {
        int left = 0;
        int right = queries.size();

        vector<int> prefix_sum = build_prefix_sum(nums, queries, right);
        if (!valid(nums, prefix_sum)) {
            return -1;
        }

        while (left <= right) {
            int mid = left + (right - left) / 2;
            prefix_sum = build_prefix_sum(nums, queries, mid);
            if (valid(nums, prefix_sum)) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        return left;
    }
};