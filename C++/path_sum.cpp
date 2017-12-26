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

class Solution {
public:
    bool hasPathSum(TreeNode *root, int sum) {
        if (root == nullptr) {
            return false;
        }

        if (root -> left == nullptr && root -> right == nullptr) {
            return sum == root -> val;
        }
        return hasPathSum(root -> left, sum - root -> val) || hasPathSum(root -> right, sum - root -> val);
    }
};