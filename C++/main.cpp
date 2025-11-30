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
#include <map>
#include <set>
#include <numeric>
#include "extra_data_types.hpp"
using namespace std;

class Solution {
public:
    TreeNode* removeLeafNodes(TreeNode* root, int target) {
        if (root == nullptr) {
            return nullptr;
        }

        root -> left = removeLeafNodes(root -> left, target);
        root -> right = removeLeafNodes(root -> right, target);
        if (root -> left == nullptr and root -> right == nullptr) {
            if (root -> val == target) {
                delete root;
                root = nullptr;
            }
        }
        return root;
    }
};

int main() {
    vector<vector<int>> matrix({{0,1,1,0,0},{1,1,0,1,0}});
    
    Solution s;
    TreeNode* root = new TreeNode(1);
    TreeNode* n1 = new TreeNode(1);
    TreeNode* n2 = new TreeNode(1);
    TreeNode* n3 = new TreeNode(2);
    TreeNode* n4 = new TreeNode(2);
    TreeNode* n5 = new TreeNode(4);
    root -> left = n1;
    root -> right = n2;
    TreeNode* result = s.removeLeafNodes(root, 1);
    cout << "succeed" << endl;
    return 0;
}
