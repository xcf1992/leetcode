//
//  open_the_lock.cpp
//  C++
//
//  Created by Chenfu Xie on 1/30/18.
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
    vector<string> open(string curStr) {
        vector<string> nextStrs;
        for (int i = 0; i< curStr.size(); i++) {
            string temp = curStr;
            temp[i] = ((curStr[i] - '0' + 1) % 10) + '0';
            nextStrs.push_back(temp);
            temp[i] = ((curStr[i] - '0' - 1 + 10) % 10) + '0';
            nextStrs.push_back(temp);
        }
        return nextStrs;
    }
public:
    int openLock(vector<string>& deadends, string target) {
        unordered_set<string> des(deadends.begin(), deadends.end());
        unordered_set<string> visited;
        queue<string> bfs;
        string init = "0000";
        
        if (des.find(init) != des.end()) {
            return -1;
        }
        visited.insert(init);
        bfs.push(init);
        int result = 0;
        while (!bfs.empty()) {
            int size = bfs.size();
            for (int i = 0; i < size; i++) {
                string curStr = bfs.front();
                bfs.pop();
                vector<string> nextStrings = open(curStr);
                for (string nextStr : nextStrings) {
                    if (nextStr == target) {
                        return ++result;
                    }
                    if (des.find(nextStr) == des.end() && visited.find(nextStr) == visited.end()) {
                        visited.insert(nextStr);
                        bfs.push(nextStr);
                    }
                }
            }
            result += 1;
        }
        return -1;
    }
};
