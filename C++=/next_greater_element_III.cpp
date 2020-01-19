/*
556. Next Greater Element III
https://leetcode.com/problems/next-greater-element-iii/

Given a positive 32-bit integer n,
you need to find the smallest 32-bit integer
which has exactly the same digits existing in the integer n and is greater in value than n.
If no such positive 32-bit integer exists, you need to return -1.

Example 1:
Input: 12
Output: 21

Example 2:
Input: 21
Output: -1
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
using namespace std;

class Solution {
public:
    int nextGreaterElement(int n) {
        string num = to_string(n);
        int len = num.size();
        if (len == 1) {
            return -1;
        }
        if (len == 2) {
            if (num.front() >= num.back()) {
                return -1;
            }
            swap(num[0], num[1]);
            return stoi(num);
        }

        int left = len - 1;
        while (left - 1 >= 0 and num[left - 1] >= num[left]) {
            left -= 1;
        }
        if (left == 0) {
            return -1;
        }

        int right = len - 1;
        while (num[right] <= num[left - 1]) {
            right -= 1;
        }
        swap(num[left - 1], num[right]);

        right = len - 1;
        while (left < right) {
            swap(num[left++], num[right--]);
        }
        long long result = stol(num);
        return result > (long)INT_MAX ? -1 : result;
    }
};
