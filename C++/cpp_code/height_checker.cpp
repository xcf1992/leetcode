/*
 1051. Height Checker
 Students are asked to stand in non-decreasing order of heights for an annual photo.

 Return the minimum number of students not standing in the right positions.
 (This is the number of students that must move in order for all students to be standing in non-decreasing order of height.)

 Example 1:

 Input: [1,1,4,2,1,3]
 Output: 3
 Explanation:
 Students with heights 4, 3 and the last 1 are not standing in the right positions.


 Note:

 1 <= heights.length <= 100
 1 <= heights[i] <= 100
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
#include <map>
#include <set>
#include <numeric>
using namespace std;

class Solution { // bucket sort
public:
    int heightChecker(vector<int>& heights) {
        vector<int> heightToFreq(101, 0);
        for (int height : heights) {
            heightToFreq[height] += 1;
        }

        int result = 0;
        int curHeight = 0;
        for (int i = 0; i < heights.size(); i++) {
            while (heightToFreq[curHeight] == 0) {
                curHeight++;
            }
            if (curHeight != heights[i]) {
                result++;
            }
            heightToFreq[curHeight]--;
        }
        return result;
    }
};

class Solution1 {
public:
    int heightChecker(vector<int>& heights) {
        int result = 0;
        vector<int> temp = heights;
        sort(temp.begin(), temp.end());
        for (int i = 0; i < heights.size(); ++i) {
            result += temp[i] == heights[i] ? 0 : 1;
        }
        return result;
    }
};
