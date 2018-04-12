/*
 Remember the story of Little Match Girl? By now, you know exactly what matchsticks the little match girl has, please find out a way you can make one square by using up all those matchsticks. You should not break any stick, but you can link them up, and each matchstick must be used exactly one time.
 
 Your input will be several matchsticks the girl has, represented with their stick length. Your output will either be true or false, to represent whether you could make one square using all the matchsticks the little match girl has.
 
 Example 1:
 Input: [1,1,2,2,2]
 Output: true
 
 Explanation: You can form a square with length 2, one side of the square came two sticks with length 1.
 Example 2:
 Input: [3,3,3,3,4]
 Output: false
 
 Explanation: You cannot find a way to form a square with all the matchsticks.
 Note:
 The length sum of the given matchsticks is in the range of 0 to 10^9.
 The length of the given matchstick array will not exceed 15.

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
private:
    bool valid(vector<int>& nums, int index, vector<int>& side, int length) {
        if (index >= nums.size()) {
            for (int l : side) {
                if (l != length) {
                    return false;
                }
            }
            return true;
        }
        
        for (int i = 0; i < side.size(); i++) {
            if (side[i] + nums[index] <= length) {
                side[i] += nums[index];
                if (valid(nums, index + 1, side, length)) {
                    return true;
                }
                side[i] -= nums[index];
            }
        }
        return false;
    }
public:
    bool makesquare(vector<int>& nums) {
        if (nums.size() < 4) {
            return false;
        }
        
        int sum = 0;
        int longest = 0;
        for (int num : nums) {
            sum += num;
            longest = max(longest, num);
        }
        
        if (sum % 4 != 0) {
            return false;
        }
        int length = sum / 4;
        if (longest > length) {
            return false;
        }
        
        vector<int> side(4, 0);
        return valid(nums, 0, side, length);
    }
};
