//
//  split_array_into_consecutive_subsequences.cpp
//  C++
//
//  Created by Chenfu Xie on 2/3/18.
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

class Solution {
public:
    bool isPossible(vector<int>& nums) {
        unordered_map<int, int> count;
        for (int num : nums) {
            count[num] += 1;
        }
        
        unordered_map<int, int> sub;
        for (int num : nums) {
            if (count[num] == 0) {
                continue;
            }
            
            if (sub[num] > 0) {
                count[num] -= 1;
                sub[num] -= 1;
                sub[num + 1] += 1;
            }
            else if (count[num + 1] > 0 && count[num + 2] > 0) {
                count[num] -= 1;
                count[num + 1] -= 1;
                count[num + 2] -= 1;
                sub[num + 3] += 1;
            }
            else {
                return false;
            }
        }
        return true;
    }
};
