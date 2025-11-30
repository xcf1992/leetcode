/*
1465. Maximum Area of a Piece of Cake After Horizontal and Vertical Cuts
https://leetcode.com/problems/maximum-area-of-a-piece-of-cake-after-horizontal-and-vertical-cuts/

Given a rectangular cake with height h and width w,
and two arrays of integers horizontalCuts
and verticalCuts where horizontalCuts[i] is the distance from the top of the rectangular cake to the ith horizontal cut
and similarly, verticalCuts[j] is the distance from the left of the rectangular cake to the jth vertical cut.

Return the maximum area of a piece of cake after you cut at each horizontal
and vertical position provided in the arrays horizontalCuts and verticalCuts.
Since the answer can be a huge number, return this modulo 10^9 + 7.

Example 1:
Input: h = 5, w = 4, horizontalCuts = [1,2,4], verticalCuts = [1,3]
Output: 4
Explanation: The figure above represents the given rectangular cake. Red lines are the horizontal and vertical cuts.
After you cut the cake, the green piece of cake has the maximum area.

Example 2:
Input: h = 5, w = 4, horizontalCuts = [3,1], verticalCuts = [1]
Output: 6
Explanation: The figure above represents the given rectangular cake. Red lines are the horizontal and vertical cuts.
After you cut the cake, the green and yellow pieces of cake have the maximum area.

Example 3:
Input: h = 5, w = 4, horizontalCuts = [3], verticalCuts = [3]
Output: 9

Constraints:
2 <= h, w <= 10^9
1 <= horizontalCuts.length < min(h, 10^5)
1 <= verticalCuts.length < min(w, 10^5)
1 <= horizontalCuts[i] < h
1 <= verticalCuts[i] < w
It is guaranteed that all elements in horizontalCuts are distinct.
It is guaranteed that all elements in verticalCuts are distinct.
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
#include <map>
#include <climits>
#include "extra_data_types.hpp"
using namespace std;

class Solution {
public:
    int maxArea(int h, int w, vector<int>& horizontalCuts, vector<int>& verticalCuts) {
        sort(horizontalCuts.begin(), horizontalCuts.end());
        int firstHor = 0;
        int maxHorDis = 0;
        for (int i = 0; i < horizontalCuts.size(); ++i) {
            maxHorDis = max(maxHorDis, horizontalCuts[i] - firstHor);
            firstHor = horizontalCuts[i];
        }
        maxHorDis = max(maxHorDis, h - firstHor);

        sort(verticalCuts.begin(), verticalCuts.end());
        int firtVer = 0;
        int maxVerDis = 0;
        for (int i = 0; i < verticalCuts.size(); ++i) {
            maxVerDis = max(maxVerDis, verticalCuts[i] - firtVer);
            firtVer = verticalCuts[i];
        }
        maxVerDis = max(maxVerDis, w - firtVer);
        long mod = 1e9 + 7;
        return ((long)maxHorDis * (long)maxVerDis) % (mod);
    }
};
