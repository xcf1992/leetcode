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
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 * };
 */
class Solution {
public:
    vector<int> largestValues(TreeNode* root) {
        vector<int> result;
        queue<TreeNode*> row;
        row.push(root);
        row.push(nullptr);

        while (!row.empty() && row.front() != nullptr) {
            int max_value = INT_MIN;

            while (row.front() != nullptr) {
                TreeNode* current = row.front();
                row.pop();
                max_value = max(max_value, current -> val);

                if (current -> left != nullptr) {
                    row.push(current -> left);
                }
                if (current -> right != nullptr) {
                    row.push(current -> right);
                }
            }

            row.push(nullptr);
            result.push_back(max_value);
            row.pop();
        }

        return result;
    }
};

int main() {
    Solution s;
    return 0;
}
