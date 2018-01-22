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
        int n = arr.size();
        if (n < 2) {
            return n;
        }
        
        vector<int> leftMax(n , 0);
        leftMax[0] = arr[0];
        vector<int> rightMin(n , 0);
        rightMin[n - 1] = arr[n - 1];
        for (int i = 1; i < n; i++) {
            leftMax[i] = max(arr[i], leftMax[i - 1]);
            rightMin[n - 1 - i] = min(arr[n - 1 - i], rightMin[n - i]);
        }
        
        int result = 1;
        for (int i = 1; i < n; i++) {
            if (rightMin[i] > leftMax[i - 1]) {
                result += 1;
            }
        }
        return result;
    }
};

class Solution1 {
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
