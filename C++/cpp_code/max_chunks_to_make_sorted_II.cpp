/*
768. Max Chunks To Make Sorted II

This question is the same as "Max Chunks to Make Sorted"
except the integers of the given array are not necessarily distinct,
the input array could be up to length 2000,
and the elements could be up to 10**8.

Given an array arr of integers (not necessarily distinct),
we split the array into some number of "chunks" (partitions), and individually sort each chunk.
After concatenating them, the result equals the sorted array.

What is the most number of chunks we could have made?

Example 1:
Input: arr = [5,4,3,2,1]
Output: 1
Explanation:
Splitting into two or more chunks will not return the required result.
For example, splitting into [5, 4], [3, 2, 1] will result in [4, 5, 1, 2, 3], which isn't sorted.

Example 2:
Input: arr = [2,1,3,4,4]
Output: 4
Explanation:
We can split into two chunks, such as [2, 1], [3, 4, 4].
However, splitting into [2, 1], [3], [4], [4] is the highest number of chunks possible.

Note:
arr will have length in range [1, 2000].
arr[i] will be an integer in range [0, 10**8].
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

class Solution {
public:
    int maxChunksToSorted(vector<int>& arr) {
        int n = arr.size();
        if (n < 2) {
            return n;
        }

        vector<int> leftMax(n, 0);  // leftMax contains max value from 0...i, inclusive
        leftMax[0] = arr[0];
        vector<int> rightMin(n, 0);  // rightMin contains min value from i...n - 1, inclusive
        rightMin[n - 1] = arr[n - 1];
        for (int i = 1; i < n; i++) {
            leftMax[i] = max(arr[i], leftMax[i - 1]);
            rightMin[n - 1 - i] = min(arr[n - 1 - i], rightMin[n - i]);
        }

        int result = 1;
        for (int i = 1; i < n; i++) {
            if (rightMin[i] >= leftMax[i - 1]) {
                result += 1;
            }
        }
        return result;
    }
};

class Solution1 {
    // sorting
public:
    int maxChunksToSorted(vector<int>& arr) {
        long sum1 = 0, sum2 = 0, ans = 0;
        vector<int> t = arr;
        sort(t.begin(), t.end());
        for (int i = 0; i < arr.size(); i++) {
            sum1 += t[i];
            sum2 += arr[i];
            if (sum1 == sum2)
                ans++;
        }
        return ans;
    }
};