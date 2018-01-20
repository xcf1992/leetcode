//
//  valid_square.cpp
//  C++
//
//  Created by Chenfu Xie on 1/20/18.
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
private:
    int getDistance(vector<int>& p1, vector<int>& p2) {
        return (p1[0] - p2[0]) * (p1[0] - p2[0]) + (p1[1] - p2[1]) * (p1[1] - p2[1]);
    }
public:
    bool validSquare(vector<int>& p1, vector<int>& p2, vector<int>& p3, vector<int>& p4) {
        unordered_set<int> sides({
            getDistance(p1, p2),
            getDistance(p1, p3),
            getDistance(p1, p4),
            getDistance(p2, p3),
            getDistance(p2, p4),
            getDistance(p3, p4)
        });
        return sides.find(0) == sides.end() && sides.size() == 2;
    }
};
