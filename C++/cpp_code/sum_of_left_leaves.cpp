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
#include "extra_data_types.hpp"
using namespace std;

class Solution {
public:
    int sumOfLeftLeaves(TreeNode *root) {
        if (root == nullptr) {
            return 0;
        }

        int leftValue = 0;
        if (root->left != nullptr and
        root->left->left == nullptr
        and
        root->left->right == nullptr
        )
        {
            leftValue = root->left->val;
        }
        else
        {
            leftValue = sumOfLeftLeaves(root->left);
        }

        return leftValue + sumOfLeftLeaves(root->right);
    }
};

int main() {
    Solution s;
    return 0;
}