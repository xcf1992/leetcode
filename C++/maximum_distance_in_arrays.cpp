/*
 Given m arrays, and each array is sorted in ascending order. Now you can pick up two integers from two different arrays (each array picks one) and calculate the distance. We define the distance between two integers a and b to be their absolute difference |a-b|. Your task is to find the maximum distance.
 
 Example 1:
 Input:
 [[1,2,3],
 [4,5],
 [1,2,3]]
 Output: 4
 Explanation:
 One way to reach the maximum distance 4 is to pick 1 in the first or third array and pick 5 in the second array.
 Note:
 Each given array will have at least 1 number. There will be at least two non-empty arrays.
 The total number of the integers in all the m arrays will be in the range of [2, 10000].
 The integers in the m arrays will be in the range of [-10000, 10000].
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
#include <set>
using namespace std;

class Solution {
public:
    int maxDistance(vector<vector<int>>& arrays) {
        int minVal = INT_MAX;
        int maxVal = INT_MIN;
        int i = 0;
        for (; i < arrays.size(); i++) {
            if (!arrays[i].empty()) {
                minVal = arrays[i].front();
                maxVal = arrays[i].back();
                break;
            }
        }
        
        int result = INT_MIN;
        for (int j = i + 1; j < arrays.size(); j++) {
            if (!arrays[j].empty()) {
                int newMin = arrays[j].front();
                int newMax = arrays[j].back();
                
                result = max(result, max(newMax - minVal, maxVal - newMin));
                minVal = min(newMin, minVal);
                maxVal = max(newMax, maxVal);
            }
        }
        return result;
    }
};
