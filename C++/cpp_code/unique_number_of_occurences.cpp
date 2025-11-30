/*
1207. Unique Number of Occurrences
https://leetcode.com/problems/unique-number-of-occurrences/

Given an array of integers arr, write a function that returns true
if and only if the number of occurrences of each value in the array is unique.

Example 1:
Input: arr = [1,2,2,1,1,3]
Output: true
Explanation: The value 1 has 3 occurrences, 2 has 2 and 3 has 1. No two values have the same number of occurrences.

Example 2:
Input: arr = [1,2]
Output: false

Example 3:
Input: arr = [-3,0,1,-3,1,1,1,-3,10,0]
Output: true

Constraints:
1 <= arr.length <= 1000
-1000 <= arr[i] <= 1000
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
using namespace std;

class Solution {
public:
    bool uniqueOccurrences(vector<int>& arr) {
        int n = arr.size();
        if (n <= 1) {
            return true;
        }

        vector<int> occurernce(n + 1, 0);
        unordered_map<int, int> count;
        for (int num : arr) {
            count[num] += 1;
            occurernce[count[num] - 1] -= 1;
            occurernce[count[num]] += 1;
        }

        for (int i = 1; i <= n; ++i) {
            if (occurernce[i] > 1) {
                return false;
            }
        }
        return true;
    }
};