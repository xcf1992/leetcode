//
//  find_mode_in_binary_search_tree.cpp
//  C++
//
//  Created by Chenfu Xie on 1/30/18.
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

struct TreeNode {
      int val;
      TreeNode *left;
      TreeNode *right;
      TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
private:
    int maxCount;
    int count;
    vector<int> mode;
    TreeNode* pre;
    
    void find(TreeNode* root) {
        if (root == nullptr) {
            return;
        }
        
        find(root -> left);
        
        if (pre == nullptr) {
            count = 1;
        }
        else if (root -> val == pre -> val) {
            count += 1;
        }
        else {
            if (count > maxCount) {
                mode.clear();
                mode.push_back(pre -> val);
                maxCount = count;
            }
            else if (count == maxCount) {
                mode.push_back(pre -> val);
            }
            count = 1;
        }
        pre = root;
        
        find(root -> right);
    }
public:
    vector<int> findMode(TreeNode* root) {
        maxCount = 0;
        count = 0;
        pre = nullptr;
        mode.clear();
        find(root);
        if (pre == nullptr) {
            return mode;
        }
        if (count == maxCount) {
            mode.push_back(pre -> val);
        }
        if (count > maxCount) {
            mode.clear();
            mode.push_back(pre -> val);
        }
        return mode;
    }
};
