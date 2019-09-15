/*
384. Shuffle an Array
Shuffle a set of numbers without duplicates.

Example:

// Init an array with set 1, 2, and 3.
int[] nums = {1,2,3};
Solution solution = new Solution(nums);

// Shuffle the array [1,2,3] and return its result. Any permutation of [1,2,3] must equally likely to be returned.
solution.shuffle();

// Resets the array back to its original configuration [1,2,3].
solution.reset();

// Returns the random shuffling of array [1,2,3].
solution.shuffle();
*/
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <cmath>
#include <queue>
#include <stack>
#include <stdio.h>
using namespace std;

class Solution {
private:
    vector<int> origin;
    vector<int> shuffled;
public:
    Solution(vector<int> nums) {
        origin = nums;
        shuffled = nums;
    }

    /* Resets the array to its original configuration and return it.*/
    vector<int> reset() {
        return origin;
    }

    /* Returns a random shuffling of the array.*/
    vector<int> shuffle() {
        int size = origin.size();
        for (int i = 0; i < size; i++) {
            swap(shuffled[i], shuffled[rand() % size]);
        }
        return shuffled;
    }
};
