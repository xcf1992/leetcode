//
//  max_chunks_to_make_sorted.cpp
//  C++
//
//  Created by Chenfu Xie on 1/21/18.
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
    int maxChunksToSorted(vector<int>& arr) {
        int result = 0;
        int curMax = 0;
        for (int i = 0; i < arr.size(); i++) {
            curMax = max(curMax, arr[i]);
            if (curMax == i) {
                result += 1;
            }
        }
        return result;
    }
};
