/*
 988. Smallest String Starting From Leaf

 Given the root of a binary tree, each node has a value from 0 to 25 representing the letters 'a' to 'z': a value of 0 represents 'a', a value of 1 represents 'b', and so on.

 Find the lexicographically smallest string that starts at a leaf of this tree and ends at the root.

 (As a reminder, any shorter prefix of a string is lexicographically smaller: for example, "ab" is lexicographically smaller than "aba".  A leaf of a node is a node that has no children.)



 Example 1:



 Input: [0,1,2,3,4,3,4]
 Output: "dba"
 Example 2:



 Input: [25,1,3,1,3,0,2]
 Output: "adz"
 Example 3:



 Input: [2,2,1,null,1,0,null,0]
 Output: "abc"


 Note:

 The number of nodes in the given tree will be between 1 and 1000.
 Each node in the tree will have a value between 0 and 25.
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
#include <map>
#include <numeric>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
private:
    string reverse(string str) {
        int left = 0;
        int right = str.size() - 1;
        while (left < right) {
            swap(str[left], str[right]);
            left += 1;
            right -= 1;
        }
        return str;
    }
    void traverse(TreeNode* root, string cur, vector<string>& allStr) {
        if (root == nullptr) {
            return;
        }

        cur.push_back('a' + root -> val);
        if (root -> left == nullptr and root -> right == nullptr) {
            allStr.push_back(reverse(cur));
            return;
        }
        traverse(root -> left, cur, allStr);
        traverse(root -> right, cur, allStr);
    }
public:
    string smallestFromLeaf(TreeNode* root) {
        vector<string> allStr;
        traverse(root, "", allStr);
        sort(allStr.begin(), allStr.end());
        return allStr.front();
    }
};
