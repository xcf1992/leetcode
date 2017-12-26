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
    int find(TreeNode* root, int& k) {
        int result;
        if (root -> left) {
            result = find(root -> left, k);
        }
        if (k == 0) {
            return result;
        }

        k -= 1;
        if (k == 0) {
            return root -> val;
        }

        if (root -> right) {
            return find(root -> right, k);
        }
        return -1;
    }
public:
    int kthSmallest(TreeNode* root, int k) {
        return find(root, k);
    }
};

int main() {
    Solution s;
    return 0;
}