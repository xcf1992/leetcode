/*
 1060. Missing Element in Sorted Array
 Given a sorted array A of unique numbers, find the K-th missing number starting from the leftmost number of the array.
 Example 1:
 
 Input: A = [4,7,9,10], K = 1
 Output: 5
 Explanation:
 The first missing number is 5.
 Example 2:
 
 Input: A = [4,7,9,10], K = 3
 Output: 8
 Explanation:
 The missing numbers are [5,6,8,...], hence the third missing number is 8.
 Example 3:
 
 Input: A = [1,2,4], K = 3
 Output: 6
 Explanation:
 The missing numbers are [3,5,6,7,...], hence the third missing number is 6.
 
 
 Note:
 
 1 <= A.length <= 50000
 1 <= A[i] <= 1e7
 1 <= K <= 1e8
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
#include <set>
#include <numeric>
using namespace std;

/*
 Let missingNum be amount of missing number in the array. Two cases that need to be handled:
 
 missingNum < k, then return nums[n - 1] + k - missingNum
 missingNum >= k, then use binary search(during the search k will be updated) to find the index in the array, where the kth missing number will be located in (nums[index], nums[index + 1]), return nums[index] + k
 */
class Solution {
public:
    int missingElement(vector<int>& nums, int k) {
        int n = nums.size();
        int left = 0;
        int right = n - 1;
        int count = nums[right] - nums[left] - n + 1;
        if (count < k) {
            return nums[right] + k - count;
        }
        
        while (left < right - 1) {
            int mid = left + (right - left) / 2;
            count = nums[mid] - nums[left] - mid + left;
            
            if (count >= k) {
                right = mid;
            }
            else {
                left = mid;
                k -= count;
            }
        }
        return nums[left] + k;
    }
};
