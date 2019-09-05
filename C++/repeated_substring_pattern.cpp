//
//  repeated_substring_pattern.cpp
//  C++
//
//  Created by Chenfu Xie on 1/25/18.
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
    bool repeatedSubstringPattern(string s) {
        int length = s.size();
        for (int i = 1; i <= s.size() / 2; i++) {
            if (s[i] == s[0] and length % i == 0) {
                string pattern = s.substr(0, i);
                bool match = true;
                for (int j = 1; j < length / i; j++) {
                    string sub = s.substr(j * i, i);
                    if (sub != pattern) {
                        match = false;
                        break;
                    }
                }
                if (match) {
                    return true;
                }
            }
        }
        return false;
    }
};
