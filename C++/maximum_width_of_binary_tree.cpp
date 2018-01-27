//
//  maximum_width_of_binary_tree.cpp
//  C++
//
//  Created by Chenfu Xie on 1/26/18.
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
public:
    int widthOfBinaryTree(TreeNode* root) {
        if (root == nullptr) {
            return 0;
        }
        int result = 1;
        queue<pair<int, TreeNode*>> row;
        row.push(pair<int, TreeNode*>(0, root));
        row.push(pair<int, TreeNode*>(-1, nullptr));
        
        while (!row.empty()) {
            int left = INT_MAX;
            int right = INT_MIN;
            while (row.front().first != -1) {
                pair<int, TreeNode*> cur = row.front();
                int pos = cur.first;
                TreeNode* node = cur.second;
                left = min(left, pos);
                right = max(right, pos);
                if (node -> left) {
                    row.push(pair<int, TreeNode*>(pos * 2, node -> left));
                }
                if (node -> right) {
                    row.push(pair<int, TreeNode*>(pos * 2 + 1, node -> right));
                }
                row.pop();
            }
            if (left <= right) {
                result = max(result, right - left + 1);
                row.push(pair<int, TreeNode*>(-1, nullptr));
            }
            row.pop();
        }
        return result;
    }
};
