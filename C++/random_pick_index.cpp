/*
398. Random Pick Index

Given an array of integers with possible duplicates, randomly output the index of a given target number. You can assume that the given target number must exist in the array.

Note:
The array size can be very large. Solution that uses too much extra space will not pass the judge.

Example:

int[] nums = new int[] {1,2,3,3,3};
Solution solution = new Solution(nums);

// pick(3) should return either index 2, 3, or 4 randomly. Each index should have equal probability of returning.
solution.pick(3);

// pick(1) should return 0. Since in the array only nums[0] is equal to 1.
solution.pick(1);
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
    vector<int> nums;
public:
    Solution(vector<int> numbers) {
        nums = numbers;
        srand(time(NULL));
    }
    
    int pick(int target) {
        int result;
        int count = 1;
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] != target) {
                continue;
            }

            if (rand() % count == 0) {
                result = i;
            }
            count += 1;
        }
        return result;
    }
};

