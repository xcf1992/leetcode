//
//  freedom_trail.cpp
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
public:
    int findRotateSteps(string ring, string key) {
        int result = 0;
        int length = ring.size();
        unordered_map<char, vector<int>> pos;
        for (int i = 0; i < length; i++) {
            pos[ring[i]].push_back(i);
        }
        
        int ksize = key.size();
        vector<vector<int>> steps(ksize + 1, vector<int>(length, INT_MAX));
        steps[0][0] = 0;
        vector<int> curPos(1, 0);
        for (int i = 0; i < key.size(); i++) {
            int newDis = INT_MAX;
            for (int nextIndex : pos[key[i]]) {
                for (int curIndex : curPos) {
                    int distance = min(abs(nextIndex - curIndex), length - abs(nextIndex - curIndex));
                    steps[i + 1][nextIndex] = min(steps[i + 1][nextIndex], steps[i][curIndex] + distance);
                    newDis = min(steps[i + 1][nextIndex], newDis);
                }
            }
            curPos = pos[key[i]];
            result = newDis;
        }
        return result + ksize;
    }
};
