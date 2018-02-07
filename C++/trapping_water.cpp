//
//  trapping_water.cpp
//  C++
//
//  Created by Chenfu Xie on 2/7/18.
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
    int trap(vector<int>& height) {
        int n = height.size();
        if (n < 2) {
            return 0;
        }
        vector<int> left(n, 0);
        left[0] = height.front();
        vector<int> right(n, 0);
        right.back() = height.back();
        for (int i = 1; i < n; i++) {
            left[i] = max(left[i - 1], height[i]);
            right[n - i - 1] = max(right[n - i], height[n - i - 1]);
        }
        
        int result = 0;
        for (int i = 0; i < n; i++) {
            int wall = min(left[i], right[i]);
            if (wall > height[i]) {
                result += wall - height[i];
            }
        }
        return result;
    }
};
