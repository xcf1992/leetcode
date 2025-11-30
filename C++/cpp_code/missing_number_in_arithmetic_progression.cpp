/*
1228. Missing Number In Arithmetic Progression
https://leetcode.com/problems/missing-number-in-arithmetic-progression/

In some array arr, the values were in arithmetic progression:
the values arr[i+1] - arr[i] are all equal for every 0 <= i < arr.length - 1.

Then, a value from arr was removed that was not the first or last value in the array.
Return the removed value.

Example 1:
Input: arr = [5,7,11,13]
Output: 9
Explanation: The previous array was [5,7,9,11,13].

Example 2:
Input: arr = [15,13,12]
Output: 14
Explanation: The previous array was [15,14,13,12].

Constraints:
3 <= arr.length <= 1000
0 <= arr[i] <= 10^5
*/
#include <iostream>
#include <sstream>
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
    int missingNumber(vector<int>& arr) {
        int n = arr.size();
        int gap = arr[1] - arr[0];
        for (int i = 1; i < n; ++i) {
            if (abs(gap) > abs(arr[i] - arr[i - 1])) {
                gap = arr[i] - arr[i - 1];
            }
        }

        int result = arr[0];
        for (int i = 0; i < n; ++i) {
            if (arr[i] != result) {
                break;
            }
            result += gap;
        }
        return result;
    }
};
