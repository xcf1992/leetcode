//
//  find_duplicate_subtrees.cpp
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

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 };

class Solution {
private:
    string parse(TreeNode* root, unordered_map<string, vector<TreeNode*>>& duplicates) {
        if (root == nullptr) {
            return "";
        }
        
        string rootStr = "(" + parse(root -> left, duplicates) + ")" +
                         to_string(root -> val) +
                         "(" + parse(root -> right, duplicates) + ")";
        duplicates[rootStr].push_back(root);
        return rootStr;
    }
public:
    vector<TreeNode*> findDuplicateSubtrees(TreeNode* root) {
        unordered_map<string, vector<TreeNode*>> duplicates;
        vector<TreeNode*> result;
        parse(root, duplicates);
        for (auto& nodes : duplicates) {
            if (nodes.second.size() > 1) {
                result.push_back(nodes.second.front());
            }
        }
        return result;
    }
};
