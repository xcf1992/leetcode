/*
655. Print Binary Tree
Print a binary tree in an m*n 2D string array following these rules:

The row number m should be equal to the height of the given binary tree.

The column number n should always be an odd number.

The root node's value (in string format) should be put in the exactly middle of the first row it can be put.

The column and the row where the root node belongs will separate the rest space into two parts
(left-bottom part and right-bottom part).

You should print the left subtree in the left-bottom part
and print the right subtree in the right-bottom part.

The left-bottom part and the right-bottom part should have the same size.
Even if one subtree is none while the other is not,
you don't need to print anything for the none subtree but still need to leave the space as large as that for the other subtree.

However, if two subtrees are none, then you don't need to leave space for both of them.
Each unused space should contain an empty string "".
Print the subtrees following the same rules.

Example 1:
Input:
     1
    /
   2
Output:
[["", "1", ""],
 ["2", "", ""]]
Example 2:
Input:
     1
    / \
   2   3
    \
     4
Output:
[["", "", "", "1", "", "", ""],
 ["", "2", "", "", "", "3", ""],
 ["", "", "4", "", "", "", ""]]
Example 3:
Input:
      1
     / \
    2   5
   /
  3
 /
4
Output:

[["",  "",  "", "",  "", "", "", "1", "",  "",  "",  "",  "", "", ""]
 ["",  "",  "", "2", "", "", "", "",  "",  "",  "",  "5", "", "", ""]
 ["",  "3", "", "",  "", "", "", "",  "",  "",  "",  "",  "", "", ""]
 ["4", "",  "", "",  "", "", "", "",  "",  "",  "",  "",  "", "", ""]]
Note: The height of binary tree is in the range of [1, 10].
*/
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

    void print(TreeNode* root, vector<vector<string>>& result, int begin, int end, int row) {
        if (root == nullptr or begin > end) {
            return;
        }

        int mid = (begin + end) / 2;
        result[row][mid] = to_string(root -> val);
        print(root -> left, result, begin, mid - 1, row + 1);
        print(root -> right, result, mid + 1, end, row + 1);
    }
public:
    vector<vector<string>> printTree(TreeNode* root) {
        int depth = getDepth(root);
        int width = pow(2, depth) - 1;
        vector<vector<string>> result(depth, vector<string>(width, ""));
        print(root, result, 0, width, 0);
        return result;
    }
};
