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
private:
    unordered_map<TreeNode*, int> cache;
public:
    int rob(TreeNode* root) {
        if (root == nullptr) {
            return 0;
        }

        if (cache.find(root) != cache.end()) {
            return cache[root];
        }

        int maxMoney = 0;
        if (root -> left != nullptr) {
            maxMoney += rob(root -> left -> left) + rob(root -> left -> right);
        }
        if (root -> right != nullptr) {
            maxMoney += rob(root -> right -> left) + rob(root -> right -> right);
        }
        maxMoney = max(root -> val + maxMoney, rob(root -> left) + rob(root -> right));

        cache[root] = maxMoney;
        return maxMoney;
    }
};

int main() {
    Solution s;
    return 0;
}