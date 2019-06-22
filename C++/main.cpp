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
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};
class Solution {
private:
    void traverse(TreeNode* root, TreeNode*& prev, TreeNode*& first, TreeNode*& second) {
        if (root == nullptr) {
            return;
        }

        traverse(root -> left, prev, first, second);
        if (prev != nullptr and first == nullptr && prev->val >= root->val) first = prev;
        if (prev != nullptr and first != nullptr && prev->val >= root->val) second = root;
        prev = root;
        traverse(root -> right, prev, first, second);
    }
public:
    void recoverTree(TreeNode* root) {
        TreeNode* prev = nullptr;
        TreeNode* first = nullptr;
        TreeNode* second = nullptr;
        traverse(root, prev, first, second);
        swap(first -> val, second -> val);
    }
};

int main() {
    Solution s;
    vector<int> temp({1,3,2,4});
    vector<int> temp1({1,3,3,3,2});
    vector<vector<char>> matrix({
        {'1','0','1','0','0'},
        {'1','0','1','1','1'},
        {'1','1','1','1','1'},
        {'1','0','0','1','0'}
    });
    vector<string> words({"cat","cats","and","sand","dog"});

    TreeNode* r1 = new TreeNode(3);
    TreeNode* r2 = new TreeNode(1);
    TreeNode* r3 = new TreeNode(2);
    TreeNode* r4 = new TreeNode(4);
    r1 -> left = r2;
    r1 -> right = r4;
    r4 -> left = r3;
    s.recoverTree(r1);
}
