/*
719. Find K-th Smallest Pair Distance

Given an integer array, return the k-th smallest distance among all the pairs.
The distance of a pair (A, B) is defined as the absolute difference between A and B.

Example 1:
Input:
nums = [1,3,1]
k = 1
Output: 0
Explanation:
Here are all the pairs:
(1,3) -> 2
(1,1) -> 0
(3,1) -> 2
Then the 1st smallest distance pair is (1,1), and its distance is 0.

Note:
2 <= len(nums) <= 10000.
0 <= nums[i] < 1000000.
1 <= k <= len(nums) * (len(nums) - 1) / 2.
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
We will perform binary search on the range - [0, max element - min element + 1)
Within each search we will examine the middle element med and we will figure out
how many pairs have a distance less than or equal to m.

When we are done counting, we compare the count to k.
If it is less than k, then our med value is too small
and we need to adjust the "start" of our search.

Otherwise, we need to reduce the range of our search from above.
It is important to note that even if our count is exactly k, we continue the search.
Eventually our algorithm will converge when we find a count = K for a given m
and every count between [start,m) will be smaller than k,
forcing start to be incremented to the point where start == m which is our result.
*/
class Solution {
private:
    // return number of pairs with distance <= mi
    int getCount(int mid, vector<int>& nums) {
        int count = 0;
        int left = 0;
        for (int right = 0; right < nums.size(); ++right) {
            while (nums[right] - nums[left] > mid) {
                left += 1;
            }
            count += right - left;
        }
        return count;
    }

public:
    int smallestDistancePair(vector<int>& nums, int k) {
        sort(nums.begin(), nums.end());
        int low = 0;
        int high = nums.back() - nums.front();
        while (low < high) {
            int middle = low + (high - low) / 2;
            int count = getCount(middle, nums);
            if (count >= k) {
                high = middle;
            } else {
                low = middle + 1;
            }
        }
        return low;
    }
};

// TLE
struct myComp {
    bool operator()(vector<int>& a, vector<int>& b) {
        return a[2] - a[0] > b[2] - b[0];
    }
};

class Solution1 {
public:
    int smallestDistancePair(vector<int>& nums, int k) {
        int n = nums.size();
        sort(nums.begin(), nums.end());

        priority_queue<vector<int>, vector<vector<int>>, myComp> minHeap;
        for (int i = 0; i < n - 1; i++) {
            minHeap.push({nums[i], i, nums[i + 1], i + 1});
        }

        vector<int> cur;
        while (k > 0) {
            cur = minHeap.top();
            minHeap.pop();

            k -= 1;
            if (cur[3] + 1 < n) {
                minHeap.push({nums[cur[1]], cur[1], nums[cur[3] + 1], cur[3] + 1});
            }
        }
        return cur[2] - cur[0];
    }
};