/*
 307. Range Sum Query - Mutable
 Given an integer array nums, find the sum of the elements between indices i and j (i ≤ j), inclusive.
 
 The update(i, val) function modifies nums by updating the element at index i to val.
 
 Example:
 
 Given nums = [1, 3, 5]
 
 sumRange(0, 2) -> 9
 update(1, 2)
 sumRange(0, 2) -> 8
 Note:
 
 The array is only modifiable by the update function.
 You may assume the number of calls to update and sumRange function is distributed evenly.
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

class NumArray {
private:
    vector<int> sum;
    vector<int> array;
public:
    NumArray(vector<int> nums) {
        sum.push_back(0);
        for (int num : nums) {
            sum.push_back(sum.back() + num);
            array.push_back(num);
        }
    }
    
    void update(int i, int val) {
        int gap = val - array[i];
        for (int x = i + 1; x < sum.size(); x++) {
            sum[x] += gap;
        }
        array[i] = val;
    }
    
    int sumRange(int i, int j) {
        return sum[j + 1] - sum[i];
    }
};

/**
 * Your NumArray object will be instantiated and called as such:
 * NumArray obj = new NumArray(nums);
 * obj.update(i,val);
 * int param_2 = obj.sumRange(i,j);
 */
