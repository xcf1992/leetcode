/*
265. Paint House II

There are a row of n houses, each house can be painted with one of the k colors.
The cost of painting each house with a certain color is different.
You have to paint all the houses such that no two adjacent houses have the same color.

The cost of painting each house with a certain color is represented by a n x k cost matrix.
For example, costs[0][0] is the cost of painting house 0 with color 0;
costs[1][2] is the cost of painting house 1 with color 2,
and so on... Find the minimum cost to paint all houses.

Note:
All costs are positive integers.

Example:
Input: [[1,5,3],[2,9,4]]
Output: 5
Explanation: Paint house 0 into color 0, paint house 1 into color 2. Minimum cost: 1 + 4 = 5;
             Or paint house 0 into color 2, paint house 1 into color 0. Minimum cost: 3 + 2 = 5.

Follow up:
Could you solve it in O(nk) runtime?
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
    int minCostII(vector<vector<int>>& costs) {
        int n = costs.size();
        if (n == 0) {
            return 0;
        }
        int k = costs[0].size();

        vector<int> minCost = costs[0];
        int least = INT_MAX;
        int lstIndex = -1;
        int less = INT_MAX;
        int lesIndex = - 1;
        for (int i = 0; i < k; i++) {
            if (minCost[i] < least) {
                less = least;
                least = minCost[i];
                lesIndex = least;
                lstIndex = i;
            }
            else if (minCost[i] < less) {
                less = minCost[i];
                lesIndex = i;
            }
        }

        for (int i = 1; i < costs.size(); i++) {
            int curLst = INT_MAX;
            int curLstIndex = -1;
            int curLes = INT_MAX;
            int curLesIndex = -1;
            for (int k = 0; k < minCost.size(); k++) {
                if (k != lstIndex) {
                    minCost[k] = least + costs[i][k];
                }
                else {
                    minCost[k] = less + costs[i][k];
                }

                if (curLst > minCost[k]) {
                    curLes = curLst;
                    curLst = minCost[k];
                    curLesIndex = curLstIndex;
                    curLstIndex = k;
                }
                else if (curLes > minCost[k]) {
                    curLes = minCost[k];
                    curLesIndex = k;
                }
            }
            least = curLst;
            lstIndex = curLstIndex;
            less = curLes;
            lesIndex = curLesIndex;
        }
        return least;
    }
};
