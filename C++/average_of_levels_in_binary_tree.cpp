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
using namespace std;

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    vector<double> averageOfLevels(TreeNode* root) {
        vector<double> result;
        queue<TreeNode*> row;
        row.push(root);
        row.push(nullptr);

        while (!row.empty() && row.front() != nullptr) {
            double sum = 0.0;
            double num = 0.0;

            while (row.front() != nullptr) {
                TreeNode* current = row.front();
                sum += current -> val;
                num += 1;

                if (current -> left != nullptr) {
                    row.push(current -> left);
                }
                if (current -> right != nullptr) {
                    row.push(current -> right);
                }

                row.pop();
            }

            row.push(nullptr);
            result.push_back(sum / num);
            row.pop();
        }

        return result;
    }
};