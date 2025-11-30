/*
321. Create Maximum Number

Given two arrays of length m and n with digits 0-9 representing two numbers.
Create the maximum number of length k <= m + n from digits of the two.
The relative order of the digits from the same array must be preserved.
Return an array of the k digits.

Note:
You should try to optimize your time and space complexity.

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
#include <climits>
#include <map>
using namespace std;
/*
Suppose nums1 = [3, 4, 6, 5],
nums2 = [9, 1, 2, 5, 8, 3],
the maximum number you can create from nums1 is [6, 5] with length 2.
For nums2, it's [9, 8, 3] with length 3.
Merging the two sequence, we have [9, 8, 6, 5, 3],
which is the max number we can create from two arrays without length constraint.
If the required length k<=5, we can simply trim the result to required length from front.
For instance, if k=3, then [9, 8, 6] is the result.

Suppose we need to create max number with length 2 from num = [4, 5, 3, 2, 1, 6, 0, 8].
The simple way is to use a stack,
first we push 4 and have stack [4],
then comes 5 > 4, we pop 4 and push 5,
stack becomes [5], 3 < 5, we push 3, stack becomes [5, 3].
Now we have the required length 2,
but we need to keep going through the array in case a larger number comes, 2 < 3,
we discard it instead of pushing it because the stack already grows to required size 2. 1 < 3,
we discard it. 6 > 3, we pop 3, since 6 > 5 and there are still elements left,
we can continue to pop 5 and push 6, the stack becomes [6], since 0 < 6,
we push 0, the stack becomes [6, 0], the stack grows to required length again.
Since 8 > 0, we pop 0, although 8 > 6, we can't continue to pop 6 since there is only one number,
which is 8, left, if we pop 6 and push 8, we can't get to length 2, so we push 8 directly, the stack becomes [6, 8].

In the basic idea, we mentioned trying all possible length i.
If we create max number for different i from scratch each time,
that would be a waste of time. Suppose num = [4, 9, 3, 2, 1, 8, 7, 6],
we need to create max number with length from 1 to 8. For i==8,
result is the original array. For i==7, we need to drop 1 number from array,
since 9 > 4, we drop 4, the result is [9, 3, 2, 1, 8, 7, 6]. For i==6,
we need to drop 1 more number, 3 < 9, skip, 2 < 3, skip, 1 < 2, skip, 8 > 1,
we drop 1, the result is [9, 3, 2, 8, 7, 6]. For i==5, we need to drop 1 more,
but this time, we needn't check from beginning, during last scan,
we already know [9, 3, 2] is monotonically non-increasing, so we check 8 directly,
since 8 > 2, we drop 2, the result is [9, 3, 8, 7, 6]. For i==4, we start with 8, 8 > 3,
we drop 3, the result is [9, 8, 7, 6]. For i==3, we start with 8, 8 < 9, skip, 7 < 8, skip, 6 < 7, skip,
by now, we've got maximum number we can create from num without length constraint.
So from now on, we can drop a number from the end each time. The result is [9, 8, 7],
For i==2, we drop last number 7 and have [9, 8]. For i==1, we drop last number 8 and have [9].
*/
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
            } else {
                result[i] = nums2[idx2];
                idx2 += 1;
            }
        }
        return result;
    }

    // return true if array1 >= array2
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

    // get the largest k numbers when keeping the relative order
    vector<int> maxSubArray(vector<int>& nums, int k) {
        if (k == 0) {
            return {};
        }

        vector<int> result;
        int n = nums.size();
        for (int i = 0; i < n; i++) {
            while (!result.empty() and nums[i] > result.back() and n - i + result.size() > k) {
                result.pop_back();
            }
            if (result.size() < k) {
                result.push_back(nums[i]);
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
        for (int i = 0; i <= k; i++)
            if (i <= n1 and k - i <= n2) {
                vector<int> maxNums1 = maxSubArray(nums1, i);
                vector<int> maxNums2 = maxSubArray(nums2, k - i);
                vector<int> temp = mergeArray(maxNums1, maxNums2, k);
                if (compareArray(temp, result, 0, 0)) {
                    result = temp;
                }
            }
        return result;
    }
};