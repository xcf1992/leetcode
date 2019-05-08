/*
 644. Maximum Average Subarray II

 Given an array consisting of n integers, find the contiguous subarray whose length is greater than or equal to k that has the maximum average value. And you need to output the maximum average value.

 Example 1:
 Input: [1,12,-5,-6,50,3], k = 4
 Output: 12.75
 Explanation:
 when length is 5, maximum average value is 10.8,
 when length is 6, maximum average value is 9.16667.
 Thus return 12.75.
 Note:
 1 <= k <= n <= 10,000.
 Elements of the given array will be in range [-10,000, 10,000].
 The answer with the calculation error less than 10-5 will be accepted.
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
 To understand the idea behind this method, let's look at the following points.

 Firstly, we know that the value of the average could lie between the range (min, max)(min,max). Here, minmin and maxmax refer to the minimum and the maximum values out of the given numsnums array. This is because, the average can't be lesser than the minimum value and can't be larger than the maximum value.

 But, in this case, we need to find the maximum average of a subarray with atleast kk elements. The idea in this method is to try to approximate(guess) the solution and to try to find if this solution really exists.

 If it exists, we can continue trying to approximate the solution even to a further precise value, but choosing a larger number as the next approximation. But, if the initial guess is wrong, and the initial maximum average value(guessed) isn't possible, we need to try with a smaller number as the next approximate.

 Now, instead of doing the guesses randomly, we can make use of Binary Search. With minmin and maxmax as the initial numbers to begin with, we can find out the midmid of these two numbers given by (min+max)/2(min+max)/2. Now, we need to find if a subarray with length greater than or equal to kk is possible with an average sum greater than this midmid value.

 To determine if this is possible in a single scan, let's look at an observation. Suppose, there exist jj elements, a_1, a_2, a_3, ...
 a_j in a subarray within numsnums such that their average is greater than midmid. In this case, we can say that

 (a_1+a_2+ a_3...+a_j)/j ≥ mid or

 (a_1+a_2+ a_3...+a_j) ≥ j*mid or

 (a_1-mid) +(a_2-mid)+ (a_3-mid) ...+(a_j-mid) ≥ 0

 Thus, we can see that if after subtracting the midmid number from the elements of a subarray with more than k-1k−1 elements, within numsnums, if the sum of elements of this reduced subarray is greater than 0, we can achieve an average value greater than midmid. Thus, in this case, we need to set the midmid as the new minimum element and continue the process.

 Otherwise, if this reduced sum is lesser than 0 for all subarrays with greater than or equal to kk elements, we can't achieve midmid as the average. Thus, we need to set midmid as the new maximum element and continue the process.

 In order to determine if such a subarray exists in a linear manner, we keep on adding nums[i]-midnums[i]−mid to the sumsum obtained till the i^{th}i
 th
 element while traversing over the numsnums array. If on traversing the first kk elements, the sumsum becomes greater than or equal to 0, we can directly determine that we can increase the average beyond midmid. Otherwise, we continue making additions to sumsum for elements beyond the k^{th}k
 th
 element, making use of the following idea.

 If we know the cumulative sum upto indices ii and jj, say sum_isum
 i

 and sum_jsum
 j

 respectively, we can determine the sum of the subarray between these indices(including jj) as sum_j - sum_isum
 j

 −sum
 i

 . In our case, we want this difference between the cumulative sums to be greater than or equal to 0 as discusssed above.

 Further, for sum_isum
 i

 as the cumulative sum upto the current(i^{th}i
 th
 ) index, all we need is sum_j - sum_i ≥ 0 such that j - i ≥ k.

 To achive this, instead of checking with all possible values of sum_isum
 i

 , we can just consider the minimum cumulative sum upto the index j - kj−k. This is because if the required condition can't be sastisfied with the minimum sum_isum
 i

 , it can never be satisfied with a larger value.

 To fulfil this, we make use of a prevprev variable which again stores the cumulative sums but, its current index(for cumulative sum) lies behind the current index for sumsum at an offset of kk units. Thus, by finding the minimum out of prevprev and the last minimum value, we can easily find out the required minimum sum value.

 Every time after checking the possiblility with a new midmid value, at the end, we need to settle at some value as the average. But, we can observe that eventually, we'll reach a point, where we'll keep moving near some same value with very small changes. In order to keep our precision in control, we limit this process to 10^-510
 −
 5 precision, by making use of errorerror and continuing the process till errorerror becomes lesser than 0.00001 .
 */
class Solution {
private:
    bool check(vector<int>& nums, double mid, int k) {
        double sum = 0.0;
        double prev = 0.0;
        double minSum = 0.0; // min_sum represent the min prefix sum of the array. When there is no element, the prefix sum is 0.
        for (int i = 0; i < k; ++i) {
            sum += nums[i] - mid;
        }
        if (sum >= 0) {
            return true;
        }

        for (int i = k; i < nums.size(); ++i) {
            /*
             We enter this for-loop only if the cumulative sum of ( sum[i] - mid) for the first k elements ( i from 0 to k-1 ) is less than 0. That is, we need to check for cumulative sum of subarrays that do not necessarily start from 0 and do not necessarily have length = k (the length can be >= k)
             When we enter this for-loop, we are atleast at position k+1. To determine the answer we need to check cumulative sum of range 0 to k (k+1 elements) or 1 to k (k elements).
             i.e we need to check if sum(0..k) >= 0 or sum(0..k) - sum(0...0) >=0 ..
             if we can determine the minimum cumulative sum upto a position which is atleast k away from our current position , then checking if sum(upto current position) - minimum >= 0 is a sufficient condition to determine whether it is possible to find a subarray whose average is mid.
             */
            sum += nums[i] - mid;
            prev += nums[i - k] - mid;
            minSum = min(prev, minSum);
            if (sum >= minSum) {
                return true;
            }
        }
        return false;
    }
public:
    double findMaxAverage(vector<int>& nums, int k) {
        double max_val = INT_MIN;
        double min_val = INT_MAX;
        for (int n: nums) {
            max_val = max((int)max_val, n);
            min_val = min((int)min_val, n);
        }

        double prev_mid = max_val;
        double gap = INT_MAX;
        while (gap > 0.00001) {
            double mid = min_val + (max_val - min_val) * 0.5;
            if (check(nums, mid, k)) {
                min_val = mid;
            }
            else {
                max_val = mid;
            }
            gap = abs(prev_mid - mid);
            prev_mid = mid;
        }
        return min_val;
    }
};
