/*
632. Smallest Range

You have k lists of sorted integers in ascending order.
Find the smallest range that includes at least one number from each of the k lists.

We define the range [a,b] is smaller than range [c,d] if b-a < d-c or a < c if b-a == d-c.

Example 1:
Input:[[4,10,15,24,26], [0,9,12,20], [5,18,22,30]]
Output: [20,24]
Explanation:
List 1: [4, 10, 15, 24,26], 24 is in range [20,24].
List 2: [0, 9, 12, 20], 20 is in range [20,24].
List 3: [5, 18, 22, 30], 22 is in range [20,24].

Note:
The given list may contain duplicates, so ascending order means >= here.
1 <= k <= 3500
-105 <= value of elements <= 105.
For Java users, please note that the input type has been changed to List<List<Integer>>.
And after you reset the code template, you'll see this point.
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
using namespace std;

struct myComp {
    bool operator ()(vector<int> &a, vector<int> &b) {
        return a[2] > b[2];
    }
};

class Solution {
public:
    vector<int> smallestRange(vector<vector<int> > &nums) {
        int n = nums.size();
        int large = INT_MIN;
        priority_queue<vector<int>, vector<vector<int> >, myComp> pq;
        for (int i = 0; i < n; i++) {
            large = max(large, nums[i][0]);
            pq.push({i, 0, nums[i][0]});
        }

        int maxLen = INT_MAX;
        vector<int> result(2, 0);
        while (pq.size() == n) {
            int row = pq.top()[0];
            int index = pq.top()[1];
            int num = pq.top()[2];
            pq.pop();

            if (large - num < maxLen) {
                maxLen = large - num;
                result[0] = num;
                result[1] = large;
            }

            if (index + 1 < nums[row].size()) {
                index += 1;
                pq.push({row, index, nums[row][index]});
                large = max(large, nums[row][index]);
            }
        }
        return result;
    }
};