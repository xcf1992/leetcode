//
//  numbers_of_segments_in_a_string.cpp
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
public:
    int countSegments(string s) {
        int result = 0;
        int i = 0;
        while (i < s.size()) {
            if (s[i] == ' ') {
                i++;
                continue;
            }
            
            result += 1;
            while (i < s.size() && s[i] != ' ') {
                i++;
            }
        }
        return result;
    }
};
