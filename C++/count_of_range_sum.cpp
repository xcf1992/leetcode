/*
 327. Count of Range Sum

 Given an integer array nums, return the number of range sums that lie in [lower, upper] inclusive.
 Range sum S(i, j) is defined as the sum of the elements in nums between indices i and j (i ≤ j), inclusive.

 Note:
 A naive algorithm of O(n2) is trivial. You MUST do better than that.

 Example:

 Input: nums = [-2,5,-1], lower = -2, upper = 2,
 Output: 3
 Explanation: The three ranges are : [0,0], [2,2], [0,2] and their respective sums are: -2, -1, 2.
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
using namespace std;

class Solution {
/*
 merge sort here is just to split the whole problem into two separate parts so there is a
 count =mergeSort(sum,lower,upper,low,mid) +mergeSort(sum,lower,upper,mid,high);

 but the sums that belong to the specified lower and higher can start from the left half to the right half (you must already be very clear about the prefix-sum, right? then this is not tricky for you)

 after the merge sort the left and right parts are sorted, so for each left sum a, what we should do is to search for range that the prefix-sums in the right b can meet the condition lower <= b-a <= higher and then that range is the possible choice we have in the right part for that single index.
 */
private:
    int mergeSort(vector<long>& sum, int lower, int upper, int left, int right) {
        if (right - left <= 1) {
            return 0;
        }
        int mid = left + (right - left) / 2;
        int count = mergeSort(sum, lower, upper, left, mid) + mergeSort(sum, lower, upper, mid, right);
        for (int i = left; i < mid; ++i) {
            auto m = lower_bound(sum.begin() + mid, sum.begin() + right, sum[i] + lower);
            auto n = upper_bound(sum.begin() + mid, sum.begin() + right, sum[i] + upper);
            count += n - m;
        }
        inplace_merge(sum.begin() + left, sum.begin() + mid, sum.begin() + right);
        return count;
    }
public:
    int countRangeSum(vector<int>& nums, int lower, int upper) {
        int len = nums.size();
        vector<long> sum(len + 1, 0);
        for (int i = 0; i < len; ++i) {
            sum[i + 1] = sum[i] + nums[i];
        }
        return mergeSort(sum, lower, upper, 0, len + 1);
    }
};
