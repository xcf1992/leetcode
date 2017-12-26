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
    vector<vector<int> > pathSum(TreeNode *root, int sum) {
        vector<vector<int>> result;
        vector<int> path;

        getAllPaths(root, path, result, sum);

        return result;
    }

    void getAllPaths(TreeNode* root, vector<int> path, vector<vector<int>>& result, int sum) {
        if (root == nullptr) {
            return;
        }

        if (root -> left == nullptr && root -> right == nullptr) {
            if (sum == root -> val) {
                path.push_back(root -> val);
                result.push_back(path);
                return;
            }
        }

        path.push_back(root -> val);
        getAllPaths(root -> left, path, result, sum - root -> val);
        getAllPaths(root -> right, path, result, sum - root -> val);

        return;
    }
};