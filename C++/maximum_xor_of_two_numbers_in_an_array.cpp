/*
421. Maximum XOR of Two Numbers in an Array

Given a non-empty array of numbers, a0, a1, a2, … , an-1, where 0 ≤ ai < 231.

Find the maximum result of ai XOR aj, where 0 ≤ i, j < n.

Could you do this in O(n) runtime?

Example:

Input: [3, 10, 5, 25, 2, 8]

Output: 28

Explanation: The maximum result is 5 ^ 25 = 28.
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

class Solution {
public:
    int findMaximumXOR(vector<int>& nums) {
        int result = 0;
        int mask = 0;
        unordered_set<int> values;
        for (int i = 31; i >= 0; i--) {
            values.clear();
            mask |= (1 << i);
            for (int num : nums) {
                values.insert(mask & num);
            }
            
            int temp = result | (1 << i);
            for (int value : values) {
                if (values.find(temp ^ value) != values.end()) {
                    result = temp;
                    break;
                }
            }
        }
        return result;
    }
};
