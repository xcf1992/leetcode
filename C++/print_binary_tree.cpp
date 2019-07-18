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
private:
    int getDepth(TreeNode* root) {
        if (root == nullptr) {
            return 0;
        }
        return max(getDepth(root -> left), getDepth(root -> right)) + 1;
    }

    void printHelper(TreeNode* root, vector<vector<string>>& res, int begin, int end, int row) {
        if (root == nullptr || begin > end) {
            return;
        }

        int mid = (begin + end) / 2;
        res[row][mid] = to_string(root -> val);
        printHelper(root -> left, res, begin, mid - 1, row + 1);
        printHelper(root -> right, res, mid + 1, end, row + 1);
    }
public:
    vector<vector<string>> printTree(TreeNode* root) {
        int depth = getDepth(root);
        int width = pow(2, depth) - 1;
        vector<vector<string>> result(depth, vector<string>(width, ""));

        printHelper(root, result, 0, width, 0);
        return result;
    }
};