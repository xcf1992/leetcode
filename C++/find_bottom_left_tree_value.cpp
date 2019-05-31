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
class Solution { //dfs
private:
    void dfs(TreeNode* root, int height, int& longest, int& result) {
        if (root == nullptr) {
            return;
        }
        
        height += 1;
        if (height > longest) {
            longest = height;
            result = root -> val;
        }
        dfs(root -> left, height, longest, result);
        dfs(root -> right, height, longest, result);
    }
public:
    int findBottomLeftValue(TreeNode* root) {
        int result = 0;
        int longest = 0;
        dfs(root, 0, longest, result);
        return result;
    }
};

class Solution { //bfs
public:
    int findBottomLeftValue(TreeNode* root) {
        queue<TreeNode*> row1;
        queue<TreeNode*> row2;
        int result = root -> val;

        row1.push(root);

        while (!row1.empty() || !row2.empty()) {
            if (row2.empty()) {
                result = row1.front() -> val;
                while (!row1.empty()) {
                    TreeNode* left_most = row1.front();
                    if (left_most -> left != nullptr) {
                        row2.push(left_most -> left);
                    }
                    if (left_most -> right != nullptr) {
                        row2.push(left_most -> right);
                    }
                    row1.pop();
                }
            }
            else {
                result = row2.front() -> val;
                while (!row2.empty()) {
                    TreeNode* left_most = row2.front();
                    if (left_most -> left != nullptr) {
                        row1.push(left_most -> left);
                    }
                    if (left_most -> right != nullptr) {
                        row1.push(left_most -> right);
                    }
                    row2.pop();
                }
            }
        }

        return result;
    }
};

int main() {
    Solution s;
    return 0;
}
