//
//  verify_preorder_sequence_in_binary_search_tree.cpp
//  C++
//
//  Created by Chenfu Xie on 3/2/18.
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
 Given an array of numbers, verify whether it is the correct preorder traversal sequence of a binary search tree.
 
 You may assume each number in the sequence is unique.
 
 Follow up:
 Could you do it using only constant space complexity?
 */

class Solution {
private:
    bool verify(vector<int>& preorder, int start, int end, int minVal, int maxVal) {
        if (start >= end) {
            return true;
        }
        
        if (preorder[start] <= minVal || preorder[start] >= maxVal) {
            return false;
        }
        
        int newEnd = start + 1;
        while (newEnd < preorder.size() && preorder[newEnd] <= preorder[start]) {
            newEnd++;
        }
        return verify(preorder, start + 1, newEnd, minVal, preorder[start]) &&
                verify(preorder, newEnd, end, preorder[start], maxVal);
    }
public:
    bool verifyPreorder(vector<int>& preorder) {
        int start = 1;
        int end = start;
        while (end < preorder.size() && preorder[end] <= preorder[0]) {
            end++;
        }
        return verify(preorder, start, end, INT_MIN, preorder[0]) &&
                verify(preorder, end, (int)preorder.size(), preorder[0], INT_MAX);
    }
};
