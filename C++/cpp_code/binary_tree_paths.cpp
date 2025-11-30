#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <cmath>
#include <queue>
#include <stack>
#include <climits>
#include "extra_data_types.hpp"
using namespace std;

class Solution {
private:
    void traverse(string result, TreeNode* root) {
        if (root == nullptr) {
            return;
        }

        result += to_string(root->val);
        if (root->left == nullptr and root->right == nullptr) {
            results.push_back(result);
        }
        result += "->";

        traverse(result, root->left);
        traverse(result, root->right);
    }

public:
    vector<string> results;

    vector<string> binaryTreePaths(TreeNode* root) {
        traverse("", root);

        return results;
    }
};

int main() {
    Solution s;
    return 0;
}