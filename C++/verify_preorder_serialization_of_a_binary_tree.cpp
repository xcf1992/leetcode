//
//  verify_preorder_serialization_of_a_binary_tree.cpp
//  C++
//
//  Created by Chenfu Xie on 2/3/18.
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
private:
    void verify(string preorder, int& pos) {
        if (pos >= preorder.size()) {
            return;
        }
        
        if (preorder[pos] == '#') {
            pos++;
            return;
        }
        
        while (preorder[pos] >= '0' && preorder[pos] <= '9') {
            pos++;
        }
        pos++;
        verify(preorder, pos);
        pos++;
        verify(preorder, pos);
    }
public:
    bool isValidSerialization(string preorder) {
        int pos = 0;
        verify(preorder, pos);
        return pos == preorder.size();
    }
};
