/*
1261. Find Elements in a Contaminated Binary Tree
https://leetcode.com/problems/find-elements-in-a-contaminated-binary-tree/

Given a binary tree with the following rules:
root.val == 0
If treeNode.val == x and treeNode.left != null, then treeNode.left.val == 2 * x + 1
If treeNode.val == x and treeNode.right != null, then treeNode.right.val == 2 * x + 2

Now the binary tree is contaminated, which means all treeNode.val have been changed to -1.
You need to first recover the binary tree and then implement the FindElements class:
FindElements(TreeNode* root) Initializes the object with a contamined binary tree, you need to recover it first.
bool find(int target) Return if the target value exists in the recovered binary tree.

Example 1:
-1            0
  \    ----->  \
   -1           2
Input
["FindElements","find","find"]
[[[-1,null,-1]],[1],[2]]
Output
[null,false,true]
Explanation
FindElements findElements = new FindElements([-1,null,-1]);
findElements.find(1); // return False
findElements.find(2); // return True

Example 2:
            -1                                   0
        /        \                          /        \
       -1        -1        ----->          1          2
    /     \                              /   \
   -1     -1                            3     4
Input
["FindElements","find","find","find"]
[[[-1,-1,-1,-1,-1]],[1],[3],[5]]
Output
[null,true,true,false]
Explanation
FindElements findElements = new FindElements([-1,-1,-1,-1,-1]);
findElements.find(1); // return True
findElements.find(3); // return True
findElements.find(5); // return False

Example 3:
Input
["FindElements","find","find","find","find"]
[[[-1,null,-1,-1,null,-1]],[2],[3],[4],[5]]
Output
[null,true,false,false,true]
Explanation
FindElements findElements = new FindElements([-1,null,-1,-1,null,-1]);
findElements.find(2); // return True
findElements.find(3); // return False
findElements.find(4); // return False
findElements.find(5); // return True

Constraints:
TreeNode.val == -1
The height of the binary tree is less than or equal to 20
The total number of nodes is between [1, 10^4]
Total calls of find() is between [1, 10^4]
0 <= target <= 10^6
*/
#include <iostream>
#include <sstream>
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

class FindElements {
private:
    unordered_set<int> values;

public:
    FindElements(TreeNode* root) {
        if (root == nullptr) {
            return;
        }

        queue<TreeNode*> bfs;
        bfs.push(root);
        root->val = 0;
        while (!bfs.empty()) {
            TreeNode* cur = bfs.front();
            values.insert(cur->val);
            bfs.pop();

            if (cur->left != nullptr) {
                cur->left->val = 2 * (cur->val) + 1;
                bfs.push(cur->left);
            }
            if (cur->right != nullptr) {
                cur->right->val = 2 * (cur->val) + 2;
                bfs.push(cur->right);
            }
        }
    }

    bool find(int target) {
        return values.find(target) != values.end();
    }
};
/**
 * Your FindElements object will be instantiated and called as such:
 * FindElements* obj = new FindElements(root);
 * bool param_1 = obj->find(target);
 */