//
//  flatten_2d_vector.cpp
//  C++
//
//  Created by Chenfu Xie on 3/1/18.
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

/*
 Implement an iterator to flatten a 2d vector.
 
 For example,
 Given 2d vector =
 
 [
 [1,2],
 [3],
 [4,5,6]
 ]
 By calling next repeatedly until hasNext returns false, the order of elements returned by next should be: [1,2,3,4,5,6].
 
 Follow up:
 As an added challenge, try to code it using only iterators in C++ or iterators in Java.
 */

class Vector2D {
    class Vector2D {
    private:
        vector<vector<int>>::iterator rowIt;
        vector<vector<int>>::iterator rowEnd;
        vector<int>::iterator colIt;
    public:
        Vector2D(vector<vector<int>>& vec2d) {
            rowIt = vec2d.begin();
            rowEnd = vec2d.end();
            if (rowIt != rowEnd) {
                colIt = rowIt -> begin();
            }
        }
        
        int next() {
            int i = *colIt;
            colIt += 1;
            return i;
        }
        
        bool hasNext() {
            while (rowIt != rowEnd && colIt == rowIt -> end()) {
                rowIt += 1;
                if (rowIt != rowEnd) {
                    colIt = rowIt -> begin();
                }
            }
            return rowIt != rowEnd;
        }
    };

/**
 * Your Vector2D object will be instantiated and called as such:
 * Vector2D i(vec2d);
 * while (i.hasNext()) cout << i.next();
 */
