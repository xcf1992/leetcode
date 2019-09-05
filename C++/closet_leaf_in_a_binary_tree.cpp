/*
 Given a binary tree where every node has a unique value, and a target key k, find the value of the nearest leaf node to target k in the tree.

 Here, nearest to a leaf means the least number of edges travelled on the binary tree to reach any leaf of the tree. Also, a node is called a leaf if it has no children.

 In the following examples, the input tree is represented in flattened form row by row. The actual root tree given will be a TreeNode object.

 Example 1:

 Input:
 root = [1, 3, 2], k = 1
 Diagram of binary tree:
   1
  / \
 3   2

 Output: 2 (or 3)

 Explanation: Either 2 or 3 is the nearest leaf node to the target of 1.
 Example 2:

 Input:
 root = [1], k = 1
 Output: 1

 Explanation: The nearest leaf node is the root node itself.
 Example 3:

 Input:
 root = [1,2,3,4,null,null,null,5,null,6], k = 2
 Diagram of binary tree:
         1
        / \
       2   3
      /
     4
    /
   5
  /
 6

 Output: 3
 Explanation: The leaf node with value 3 (and not the leaf node with value 6) is nearest to the node with value 2.
 Note:
 root represents a binary tree with at least 1 node and at most 1000 nodes.
 Every node has a unique node.val in range [1, 1000].
 There exists some node in the given binary tree for which node.val == k.
*/

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <map>
#include <unordered_set>
#include <algorithm>
#include <cmath>
#include <queue>
#include <stack>
#include <stdio.h>
#include <set>
#include <numeric>
#include "extra_data_types.hpp"
using namespace std;

class Solution {
private:
    // use TreeNode*& target, to make sure found targe node is passed outside, TreeNode* target
    // won't work
    void traverse(vector<TreeNode*>& parent, TreeNode*& target, int k, TreeNode* root) {
        if (root -> val == k) {
            target = root;
        }

        if (root -> left != nullptr) {
            parent[root -> left -> val] = root;
            traverse(parent, target, k, root -> left);
        }

        if (root -> right != nullptr) {
            parent[root -> right -> val] = root;
            traverse(parent, target, k, root -> right);
        }
    }
public:
    int findClosestLeaf(TreeNode* root, int k) {
        vector<TreeNode*> parent(1001, nullptr);
        TreeNode* target = nullptr;
        traverse(parent, target, k, root);

        queue<TreeNode*> bfs;
        unordered_set<int> visited;
        visited.insert(target -> val);
        bfs.push(target);
        while (!bfs.empty()) {
            int count = bfs.size();
            for (int i = 0; i < count; i++) {
                TreeNode* cur = bfs.front();
                bfs.pop();

                if (cur -> left == nullptr && cur -> right == nullptr) {
                    return cur -> val;
                }

                if (cur -> left != nullptr && visited.find(cur -> left -> val) == visited.end()) {
                    bfs.push(cur -> left);
                    visited.insert(cur -> left -> val);
                }

                if (cur -> right != nullptr && visited.find(cur -> right -> val) == visited.end()) {
                    bfs.push(cur -> right);
                    visited.insert(cur -> right -> val);
                }

                if (parent[cur -> val] != nullptr && visited.find(parent[cur -> val] -> val) == visited.end()) {
                    bfs.push(parent[cur -> val]);
                    visited.insert(parent[cur -> val] -> val);
                }
            }
        }
        return k;
    }
};
