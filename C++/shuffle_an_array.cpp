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
    
    /** Resets the array to its original configuration and return it. */
    vector<int> reset() {
        return origin;
    }
    
    /** Returns a random shuffling of the array. */
    vector<int> shuffle() {
        int size = origin.size();
        for (int i = 0; i < size; i++) {
            swap(shuffled[i], shuffled[rand() % size]);
        }
        return shuffled;
    }
};

int main() {
    Solution s;
    return 0;
}