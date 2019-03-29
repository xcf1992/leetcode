/*
 321. Create Maximum Number
 Given two arrays of length m and n with digits 0-9 representing two numbers. Create the maximum number of length k <= m + n from digits of the two. The relative order of the digits from the same array must be preserved. Return an array of the k digits.

 Note: You should try to optimize your time and space complexity.

 Example 1:

 Input:
 nums1 = [3, 4, 6, 5]
 nums2 = [9, 1, 2, 5, 8, 3]
 k = 5
 Output:
 [9, 8, 6, 5, 3]
 Example 2:

 Input:
 nums1 = [6, 7]
 nums2 = [6, 0, 4]
 k = 5
 Output:
 [6, 7, 6, 0, 4]
 Example 3:

 Input:
 nums1 = [3, 9]
 nums2 = [8, 9]
 k = 3
 Output:
 [9, 8, 9]
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

/*
it is easy to solve problem if nums1.size() + nums2.size() == k
 so we split the problem into 3 subproblems:
 1. get max sub array from nums1 of length i
 2. get max sub array from nums2 of length k - i
 3. get max merge arrary from maxsub1 and maxsub2
 4. get max merge array of length k
 */
class Solution {
private:
    vector<int> mergeArray(vector<int>& nums1, vector<int>& nums2, int k) {
        vector<int> result(k);
        int idx1 = 0;
        int idx2 = 0;
        for (int i = 0; i < k; ++i) {
            if (compareArray(nums1, nums2, idx1, idx2)) {
                result[i] = nums1[idx1];
                idx1 += 1;
            }
            else {
                result[i] = nums2[idx2];
                idx2 += 1;
            }
        }
        return result;
    }

    bool compareArray(vector<int>& nums1, vector<int>& nums2, int index1, int index2) {
        int len1 = nums1.size() - index1;
        if (len1 <= 0) {
            return false;
        }
        int len2 = nums2.size() - index2;
        if (len2 <= 0) {
            return true;
        }

        int len = max(len1, len2);
        for (int i = 0; i < len; ++i) {
            int d1 = index1 + i < nums1.size() ? nums1[index1 + i] : 0;
            int d2 = index2 + i < nums2.size() ? nums2[index2 + i] : 0;
            if (d1 != d2) {
                return d1 > d2;
            }
        }
        return true;
    }

    //get the largest k numbers when keeping the relative order
    vector<int> maxSubArray(vector<int>& nums, int k) {
        vector<int> result(k, 0);
        if (k == 0) {
            return result;
        }
        int n = nums.size();
        int index = 0;
        for (int i = 0; i < n; i++) {
            while (n - i + index > k and index > 0 and nums[i] > result[index - 1]) {
                index -= 1;
            }
            if (index < k) {
                result[index] = nums[i];
                index += 1;
            }
        }
        return result;
    }
public:
    vector<int> maxNumber(vector<int>& nums1, vector<int>& nums2, int k) {
        int n1 = nums1.size();
        int n2 = nums2.size();
        if (k == n1 + n2) {
            return mergeArray(nums1, nums2, k);
        }

        vector<int> result(k, 0);
        for (int i = 0; i <= k; i++) {
            if (i <= n1 and k - i <= n2) {
                vector<int> maxNums1 = maxSubArray(nums1, i);
                vector<int> maxNums2 = maxSubArray(nums2, k - i);
                vector<int> temp = mergeArray(maxNums1, maxNums2, k);
                if (compareArray(temp, result, 0, 0)) {
                    result = temp;
                }
            }
        }
        return result;
    }
};
