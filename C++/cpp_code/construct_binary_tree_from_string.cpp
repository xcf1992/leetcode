/*
 You need to construct a binary tree from a string consisting of parenthesis and integers.

 The whole input represents a binary tree. It contains an integer followed by zero, one or two pairs of parenthesis. The
 integer represents the root's value and a pair of parenthesis contains a child binary tree with the same structure.

 You always start to construct the left child node of the parent first if it exists.

 Example:
 Input: "4(2(3)(1))(6(5))"
 Output: return the tree root node representing the following tree:

 4
 /   \
 2     6
 / \   /
 3   1 5
 Note:
 There will only be '(', ')', '-' and '0' ~ '9' in the input string.
 An empty tree is represented by "" instead of "()".
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
#include <climits>
#include <set>

using namespace std;

class Solution {
private:
    TreeNode* build(string& s, int& cur) {
        int pos = cur;
        while (isdigit(s[cur]) or s[cur] == '-') {
            cur += 1;
        }

        TreeNode* root = new TreeNode(stoi(s.substr(pos, cur - pos)));
        if (s[cur] == '(') {
            cur += 1;
            root->left = build(s, cur);
            cur += 1;
        }
        if (s[cur] == '(') {
            cur += 1;
            root->right = build(s, cur);
            cur += 1;
        }
        return root;
    }

public:
    TreeNode* str2tree(string s) {
        int cur = 0;
        return s.empty() ? nullptr : build(s, cur);
    }
};