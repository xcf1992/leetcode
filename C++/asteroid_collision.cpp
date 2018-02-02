//
//  asteroid_collision.cpp
//  C++
//
//  Created by Chenfu Xie on 2/1/18.
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
    vector<int> asteroidCollision(vector<int>& asteroids) {
        vector<int> result;
        for (int asteroid : asteroids) {
            if (asteroid < 0) {
                bool exploded = false;
                while (!result.empty() && result.back() > 0) {
                    if (result.back() > abs(asteroid)) {
                        exploded = true;
                        break;
                    }
                    else if (result.back() == abs(asteroid)) {
                        result.pop_back();
                        exploded = true;
                        break;
                    }
                    else {
                        result.pop_back();
                    }
                }
                if (!exploded) {
                    result.push_back(asteroid);
                }
            }
            else {
                result.push_back(asteroid);
            }
        }
        return result;
    }
};
