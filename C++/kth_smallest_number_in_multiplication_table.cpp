//
//  kth_smallest_number_in_multiplication_table.cpp
//  C++
//
//  Created by Chenfu Xie on 1/24/18.
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
    int findKthNumber(int m, int n, int k) {
        int left = 1;
        int right = m * n;
        while (left < right) {
            int mid = left + (right - left) / 2;
            int count = 0;
            for (int i = 1; i <= m; i++) {
                count += min(mid / i, n);
            }
            
            if (count >= k) {
                right = mid;
            }
            else {
                left = mid + 1;
            }
        }
        return left;
    }
};
