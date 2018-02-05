//
//  permutation_in_string.cpp
//  C++
//
//  Created by Chenfu Xie on 2/4/18.
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
    bool allZero(vector<int>& count) {
        for (int num : count) {
            if (num != 0) {
                return false;
            }
        }
        return true;
    }
public:
    bool checkInclusion(string s1, string s2) {
        int m = s1.size();
        int n = s2.size();
        if (m > n) {
            return false;
        }
        
        vector<int> count(26, 0);
        for (int i = 0; i < m; i++) {
            count[s1[i] - 'a'] += 1;
            count[s2[i] - 'a'] -= 1;
        }
        if (allZero(count)) {
            return true;
        }
        
        for (int i = m; i < n; i++) {
            count[s2[i - m] - 'a'] += 1;
            count[s2[i] - 'a'] -= 1;
            if (allZero(count)) {
                return true;
            }
        }
        return false;
    }
};
