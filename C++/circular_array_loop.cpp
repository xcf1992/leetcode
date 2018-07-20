/*
 You are given an array of positive and negative integers. If a number n at an index is positive, then move forward n steps. Conversely, if it's negative (-n), move backward n steps. Assume the first element of the array is forward next to the last element, and the last element is backward next to the first element. Determine if there is a loop in this array. A loop starts and ends at a particular index with more than 1 element along the loop.
!!!! The loop must be "forward" or "backward'. -> fuck this
 
 Example 1: Given the array [2, -1, 1, 2, 2], there is a loop, from index 0 -> 2 -> 3 -> 0.
 
 Example 2: Given the array [-1, 2], there is no loop.
 
 Note: The given array is guaranteed to contain no element "0".
 
 Can you do it in O(n) time complexity and O(1) space complexity?
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
private:
    int n;
    int getNext(vector<int>& nums, int i) {
        int next = i + nums[i];
        return next > 0 ? next % n : n + (next % n);
    }
public:
    bool circularArrayLoop(vector<int>& nums) {
        n = nums.size();
        if (n < 2) {
            return false;
        }
        for (int i = 0; i < n; i++) {
            if (i == getNext(nums, i)) {
                nums[i] = 0;
            }
        }
        
        for (int i = 0; i < n; i++) {
            if (nums[i] == 0) {
                continue;
            }
            int slow = i;
            int fast = i;
            bool moveForward = nums[slow] > 0;
            bool wrong = false;
            do {
                slow = getNext(nums, slow);
                fast = getNext(nums, getNext(nums, fast));
                if ((moveForward && nums[slow] < 0) || (!moveForward && nums[slow] > 0)) {
                    wrong = true;
                }
            } while (nums[slow] != 0 && slow != fast && !wrong);
            
            if (nums[slow] != 0 && slow == fast && !wrong) {
                return true;
            }
            nums[i] = 0;
        }
        return false;
    }
};
