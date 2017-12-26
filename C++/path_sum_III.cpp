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

struct TreeNode {
     int val;
     TreeNode *left;
     TreeNode *right;
     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    int pathSum(TreeNode *root, int sum) {
        if (!root) {
            return 0;
        }
        return getAllPaths(root, 0, sum) + pathSum(root -> left, sum) + pathSum(root -> right, sum);
    }

    int getAllPaths(TreeNode* root, int pre, int sum) {
        if (!root) {
            return 0;
        }

        int cur = pre + root -> val;
        return (cur == sum) + getAllPaths(root -> left, cur, sum) + getAllPaths(root -> right, cur, sum);
    }
};