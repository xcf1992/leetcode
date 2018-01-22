//
//  maximum_swap.cpp
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
    int maximumSwap(int num) {
        if (num < 10) {
            return num;
        }
        
        vector<int> digits;
        while (num > 0) {
            digits.push_back(num % 10);
            num /= 10;
        }
        
        int maxIndex = -1;
        int leftIndex = -1;
        int rightIndex = -1;
        for (int i = 0; i < digits.size(); i++) {
            if (maxIndex == -1 || digits[maxIndex] < digits[i]) {
                maxIndex = i;
            }
            else {
                leftIndex = maxIndex;
                rightIndex = i;
            }
        }
        
        swap(digits[leftIndex], digits[rightIndex]);
        int result = 0;
        for (int i = digits.size() - 1; i >= 0; i--) {
            result = result * 10 + digits[i];
        }
        return result;
    }
};
