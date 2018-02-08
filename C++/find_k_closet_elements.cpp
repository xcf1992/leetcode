//
//  find_k_closet_elements.cpp
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
    vector<int> findClosestElements(vector<int>& arr, int k, int x) {
        int left = 0;
        int right = arr.size() - 1;
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (arr[mid] == x) {
                left = mid;
                break;
            }
            else if (arr[mid] > x) {
                right = mid;
            }
            else {
                left = mid + 1;
            }
        }
        
        int start = left - 1;
        int end = left;
        int temp = k;
        while(k-- > 0){
            if (start < 0 || (end < arr.size() && abs(arr[start] - x) > abs(arr[end] - x))) {
                end++;
            }
            else {
                start--;
            }
        }
        
        vector<int> result;
        for (int i = start + 1; result.size() < temp; i++) {
            result.push_back(arr[i]);
        }
        return result;
    }
};
