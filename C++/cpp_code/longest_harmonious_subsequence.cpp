/*
594. Longest Harmonious Subsequence
We define a harmounious array as an array where the difference between its maximum value and its minimum value is
exactly 1.

Now, given an integer array,
you need to find the length of its longest harmonious subsequence among all its possible subsequences.

Example 1:

Input: [1,3,2,2,5,2,3,7]
Output: 5
Explanation: The longest harmonious subsequence is [3,2,2,2,3].


Note: The length of the input array will not exceed 20,000.
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
#include <map>
using namespace std;

class Solution {
public:
    int findLHS(vector<int>& nums) {
        map<int, int> count;
        for (int num : nums) {
            count[num] += 1;
        }

        int result = 0;
        for (auto& it : count) {
            if (count.find(it.first + 1) != count.end()) {
                result = max(result, it.second + count[1 + it.first]);
            }
        }
        return result;
    }
};