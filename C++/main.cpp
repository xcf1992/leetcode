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
#include <map>
#include <set>
#include <numeric>
#include "extra_data_types.hpp"
using namespace std;

class Solution {
private:
    void traverse(TreeNode* root, vector<TreeNode*>& parent, unordered_set<TreeNode*>& leaves, int cur, int& height) {
        if (root == nullptr) {
            return;
        }
        
        if (cur > height) {
            height = cur;
            leaves.clear();
        }
        if (cur == height) {
            leaves.insert(root);
        }
        
        if (root -> left != nullptr) {
            parent[root -> left -> val] = root;
        }
        if (root -> right != nullptr) {
            parent[root -> right -> val] = root;
        }
        
        traverse(root -> left, parent, leaves, cur + 1, height);
        traverse(root -> right, parent, leaves, cur + 1, height);
    }
public:
    TreeNode* lcaDeepestLeaves(TreeNode* root) {
        vector<TreeNode*> parent(1001, nullptr);
        unordered_set<TreeNode*> leaves;
        int height = 0;
        traverse(root, parent, leaves, 0, height);
        
        while (leaves.size() > 1) {
            for (auto it = leaves.begin(); it != leaves.end(); it++) {
                leaves.insert(parent[(*it) -> val]);
                leaves.erase(it);
            }
        }
        return *leaves.begin();
    }
};

int main() {
    Solution s;
    vector<int> temp({1,3,2,4});
    vector<int> temp1({1,3,3,3,2});
    vector<vector<int>> matrix({
        {0,1},
        {1,2},
        {2,1},
        {1,0},
        {0,2},
        {0,0},
        {1,1}
    });
    vector<vector<int>> matrix2({
        {1,2,2,3,5},
        {3,2,3,4,4},
        {2,4,5,3,1},
        {6,7,1,4,5},
        {5,1,1,2,4}
    });
    vector<string> words({"cat","cats","and","sand","dog"});
    TreeNode* r1 = new TreeNode(1);
    TreeNode* r2 = new TreeNode(2);
    TreeNode* r3 = new TreeNode(3);
    r1 -> left = r2;
    r1 -> right = r3;
    s.lcaDeepestLeaves(r1);
}
