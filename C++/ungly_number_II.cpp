//
//  ungly_number_II.cpp
//  C++
//
//  Created by Chenfu Xie on 2/11/18.
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
    int nthUglyNumber(int n) {
        vector<int> numbers;
        numbers.push_back(1);
        int multiply2 = 0;
        int multiply3 = 0;
        int multiply5 = 0;
        while (numbers.size() < n) {
            int nextNum = min(numbers[multiply2] * 2, min(numbers[multiply3] * 3, numbers[multiply5] * 5));
            numbers.push_back(nextNum);
            while (numbers[multiply2] * 2 <= nextNum) {
                multiply2++;
            }
            while (numbers[multiply3] * 3 <= nextNum) {
                multiply3++;
            }
            while (numbers[multiply5] * 5 <= nextNum) {
                multiply5++;
            }
        }
        return numbers.back();
    }
};
