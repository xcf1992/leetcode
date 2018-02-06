//
//  find_median_from_data_stream.cpp
//  C++
//
//  Created by Chenfu Xie on 2/5/18.
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

class MedianFinder {
private:
    priority_queue<int> left;
    priority_queue<int, vector<int>, greater<int>> right;
public:
    /** initialize your data structure here. */
    MedianFinder() {
        
    }
    
    void addNum(int num) {
        if (left.empty() || left.top() > num) {
            left.push(num);
        }
        else {
            right.push(num);
        }
        
        if (left.size() > right.size() + 1) {
            right.push(left.top());
            left.pop();
        }
        else if (left.size() + 1 < right.size()) {
            left.push(right.top());
            right.pop();
        }
    }
    
    double findMedian() {
        if (left.size() == right.size()) {
            return left.empty() ? 0.0 : (left.top() + right.top()) / 2.0;
        }
        
        return left.size() > right.size() ? left.top() : right.top();
    }
};

