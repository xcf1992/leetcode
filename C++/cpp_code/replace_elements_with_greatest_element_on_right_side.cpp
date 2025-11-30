/*
1299. Replace Elements with Greatest Element on Right Side
https://leetcode.com/problems/replace-elements-with-greatest-element-on-right-side/

Given an array arr,
replace every element in that array with the greatest element among the elements to its right,
and replace the last element with -1.

After doing so, return the array.

Example 1:
Input: arr = [17,18,5,4,6,1]
Output: [18,6,6,6,1,-1]

Constraints:
1 <= arr.length <= 10^4
1 <= arr[i] <= 10^5
*/
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <set>
#include <algorithm>
#include <cmath>
#include <queue>
#include <stack>
#include <climits>
#include <map>
#include <numeric>
#include "extra_data_types.hpp"
using namespace std;

class Solution {
public:
    vector<int> replaceElements(vector<int>& arr) {
        int n = arr.size();
        vector<int> rightMax(n, -1);
        int curMax = arr[n - 1];
        for (int i = n - 2; i >= 0; --i) {
            rightMax[i] = curMax;
            curMax = max(curMax, arr[i]);
        }
        return rightMax;
    }
};
