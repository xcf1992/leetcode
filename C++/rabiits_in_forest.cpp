//
//  rabiits_in_forest.cpp
//  C++
//
//  Created by Chenfu Xie on 2/11/18.
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
#include <map>
using namespace std;

class Solution {
public:
    int numRabbits(vector<int>& answers) {
        unordered_map<double, double> counts;
        for (int ans : answers) {
            counts[ans + 1] += 1;
        }
        
        int result = 0;
        for (pair<double, double> count : counts) {
            result += ceil(count.second / count.first) * count.first;
        }
        return result;
    }
};
