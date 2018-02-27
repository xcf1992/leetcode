//
//  paint_house.cpp
//  C++
//
//  Created by Chenfu Xie on 2/27/18.
//  Copyright © 2018 Chenfu Xie. All rights reserved.
//

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

/*
 There are a row of n houses, each house can be painted with one of the three colors: red, blue or green. The cost of painting each house with a certain color is different. You have to paint all the houses such that no two adjacent houses have the same color.
 
 The cost of painting each house with a certain color is represented by a n x 3 cost matrix. For example, costs[0][0] is the cost of painting house 0 with color red; costs[1][2] is the cost of painting house 1 with color green, and so on... Find the minimum cost to paint all houses.
 
 Note:
 All costs are positive integers.
 

 */
class Solution {
public:
    int minCost(vector<vector<int>>& costs) {
        if (costs.empty()) {
            return 0;
        }
        vector<int> minCost(costs[0]);
        
        for (int i = 1; i < costs.size(); i++) {
            int newR = min(minCost[1], minCost[2]) + costs[i][0];
            int newB = min(minCost[0], minCost[2]) + costs[i][1];
            int newY = min(minCost[0], minCost[1]) + costs[i][2];
            minCost[0] = newR;
            minCost[1] = newB;
            minCost[2] = newY;
        }
        
        int result = minCost[0];
        for (int cost : minCost) {
            result = min(result, cost);
        }
        return result;
    }
};
