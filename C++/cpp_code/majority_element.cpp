/*
169. Majority Element
Given an array of size n, find the majority element.
The majority element is the element that appears more than ⌊ n/2 ⌋ times.

You may assume that the array is non-empty and the majority element always exist in the array.

Example 1:

Input: [3,2,3]
Output: 3
Example 2:

Input: [2,2,1,1,1,2,2]
Output: 2
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
    int majorityElement(vector<int>& num) {
        int cur = -1;
        int count = 0;
        for (int i = 0; i < num.size(); ++i) {
            if (count == 0) {
                cur = num[i];
                count = 1;
                continue;
            }

            if (num[i] == cur) {
                count += 1;
            } else {
                count -= 1;
            }
        }
        return cur;
    }
};