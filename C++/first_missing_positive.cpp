/*
41. First Missing Positive
Given an unsorted integer array, find the smallest missing positive integer.

Example 1:

Input: [1,2,0]
Output: 3
Example 2:

Input: [3,4,-1,1]
Output: 2
Example 3:

Input: [7,8,9,11,12]
Output: 1
Note:

Your algorithm should run in O(n) time and uses constant extra space.
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
    int firstMissingPositive(vector<int>& nums) {
        int smallest = -1;
        int largest = 0;
        for (int k : nums) {
            if (k > 0) {
                if (smallest == -1 or k < smallest) {
                    smallest = k;
                }
                if (k > largest) {
                    largest = k;
                }
            }
        }
    }
};
