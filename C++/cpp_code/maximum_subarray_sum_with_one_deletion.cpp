/*
1186. Maximum Subarray Sum with One Deletion
https://leetcode.com/problems/maximum-subarray-sum-with-one-deletion/

Given an array of integers,
return the maximum sum for a non-empty subarray (contiguous elements) with at most one element deletion.
In other words, you want to choose a subarray and optionally delete one element from it
so that there is still at least one element left and the sum of the remaining elements is maximum possible.

Note that the subarray needs to be non-empty after deleting one element.

Example 1:
Input: arr = [1,-2,0,3]
Output: 4
Explanation: Because we can choose [1, -2, 0, 3] and drop -2, thus the subarray [1, 0, 3] becomes the maximum value.

Example 2:
Input: arr = [1,-2,-2,3]
Output: 3
Explanation: We just choose [3] and it's the maximum sum.

Example 3:
Input: arr = [-1,-1,-1,-1]
Output: -1
Explanation: The final subarray needs to be non-empty.
You can't choose [-1] and delete -1 from it,
then get an empty subarray to make the sum equals to 0.

Constraints:

1 <= arr.length <= 10^5
-10^4 <= arr[i] <= 10^4
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
#include "extra_data_types.hpp"
using namespace std;
/*
Idea
Compute maxEndHere and maxStartHere arrays and also find overall max along with them.
Now, evaluate the case where 1-element can be eliminated,
that is at each index, we can make use of maxEndHere[i-1]+maxStartHere[i+1]

Thought process
This approach is a slight improvisation on the idea of https://leetcode.com/problems/maximum-subarray/.
Basically, the difference here is we can eliminate 1 number and still can continue with expanding our subarray.
So imagine a subarray where you removed 1 element,
then it forms two subarrays ending at prev index and starting at next index.
We know how to get maxEndHere from the max sum subarray problem for each index.
If we reverse our thinking to follow the same logic to solve for subarray at next index,
we should be able to see computing maxStartHere is just backwards of maxEndHere.
So now at each index, it is just about looking at prev and next numbers from the respective arrays to get overall max.
*/
class Solution {
public:
    int maximumSum(vector<int>& arr) {
        int n = arr.size();
        if (n == 1) {
            return arr[0];
        }

        vector<int> maxEndAt(n, 0);
        maxEndAt[0] = arr[0];
        int result = arr[0];
        vector<int> maxStartFrom(n, 0);
        maxStartFrom[n - 1] = arr[n - 1];
        for (int i = 1; i < n; ++i) {
            maxEndAt[i] = max(maxEndAt[i - 1] + arr[i], arr[i]);
            result = max(result, maxEndAt[i]);

            int j = n - 1 - i;
            maxStartFrom[j] = max(maxStartFrom[j + 1] + arr[j], arr[j]);
        }

        for (int i = 1; i < n - 1; ++i) {
            result = max(result, maxEndAt[i - 1] + maxStartFrom[i + 1]);
        }
        return result;
    }
};