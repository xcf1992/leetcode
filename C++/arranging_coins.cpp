//
//  arranging_coins.cpp
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
    int arrangeCoins(int n) {
        return floor(-0.5 + sqrt((double) 2 * n + 0.25));
    }
};
