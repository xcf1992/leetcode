/*
260. Single Number III
https://leetcode.com/problems/single-number-iii/

Given an array of numbers nums,
in which exactly two elements appear only once
and all the other elements appear exactly twice.
Find the two elements that appear only once.

Example:
Input:  [1,2,1,3,2,5]
Output: [3,5]

Note:
The order of the result is not important. So in the above example, [5, 3] is also correct.
Your algorithm should run in linear runtime complexity. Could you implement it using only constant space complexity?
*/
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <cmath>
#include <queue>
#include <stack>
#include <climits>
using namespace std;
/*
find the last bit which is 1 in xorResult;
say xorResult is 1100
then the lastBit will be 100, which means a and b is different in this bit
*/
class Solution {
public:
    vector<int> singleNumber(vector<int>& nums) {
        int xorResult = 0;
        for (auto num : nums) {
            xorResult ^= num;
        }

        int lastBit = xorResult & ((xorResult - 1) ^ xorResult);
        int result = 0;
        for (auto num : nums) {
            if (lastBit & num) {
                result ^= num;
            }
        }
        return {result, result ^ xorResult};
    }
};