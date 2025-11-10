/*
https://leetcode.com/problems/maximum-bags-with-full-capacity-of-rocks/description/
2279. Maximum Bags With Full Capacity of Rocks

You have n bags numbered from 0 to n - 1. You are given two 0-indexed integer arrays capacity and rocks. The ith bag can
hold a maximum of capacity[i] rocks and currently contains rocks[i] rocks. You are also given an integer
additionalRocks, the number of additional rocks you can place in any of the bags.

Return the maximum number of bags that could have full capacity after placing the additional rocks in some bags.



Example 1:

Input: capacity = [2,3,4,5], rocks = [1,2,4,4], additionalRocks = 2
Output: 3
Explanation:
Place 1 rock in bag 0 and 1 rock in bag 1.
The number of rocks in each bag are now [2,3,4,4].
Bags 0, 1, and 2 have full capacity.
There are 3 bags at full capacity, so we return 3.
It can be shown that it is not possible to have more than 3 bags at full capacity.
Note that there may be other ways of placing the rocks that result in an answer of 3.
Example 2:

Input: capacity = [10,2,2], rocks = [2,2,0], additionalRocks = 100
Output: 3
Explanation:
Place 8 rocks in bag 0 and 2 rocks in bag 2.
The number of rocks in each bag are now [10,2,2].
Bags 0, 1, and 2 have full capacity.
There are 3 bags at full capacity, so we return 3.
It can be shown that it is not possible to have more than 3 bags at full capacity.
Note that we did not use all of the additional rocks.


Constraints:

n == capacity.length == rocks.length
1 <= n <= 5 * 104
1 <= capacity[i] <= 109
0 <= rocks[i] <= capacity[i]
1 <= additionalRocks <= 109
*/
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <map>
#include <unordered_set>
#include <algorithm>
#include <cmath>
#include <queue>
#include <stack>
#include <stdio.h>
#include <set>
#include <numeric>
using namespace std;

class Solution {
public:
    int maximumBags(vector<int>& capacity, vector<int>& rocks, int additionalRocks) {
        int n = rocks.size();
        vector<int> left_cap(n, 0);
        long long total_left = 0;
        int rst = 0;
        for (int i = 0; i < n; i++) {
            left_cap[i] = capacity[i] - rocks[i];
            total_left += left_cap[i];
            rst += left_cap[i] == 0 ? 1 : 0;
        }

        if (total_left <= additionalRocks) {
            return n;
        }

        sort(left_cap.begin(), left_cap.end());
        for (const int& cap : left_cap) {
            if (cap != 0 && cap <= additionalRocks) {
                rst += 1;
                additionalRocks -= cap;
            }
        }
        return rst;
    }
};
