/*
297. Serialize and Deserialize Binary Tree
Serialization is the process of converting a data structure or object into a sequence of bits so that it can be stored in a file or memory buffer, or transmitted across a network connection link to be reconstructed later in the same or another computer environment.

Design an algorithm to serialize and deserialize a binary tree. There is no restriction on how your serialization/deserialization algorithm should work. You just need to ensure that a binary tree can be serialized to a string and this string can be deserialized to the original tree structure.

Example: 

You may serialize the following tree:

    1
   / \
  2   3
     / \
    4   5

as "[1,2,3,null,null,4,5]"
Clarification: The above format is the same as how LeetCode serializes a binary tree. You do not necessarily need to follow this format, so please be creative and come up with different approaches yourself.

Note: Do not use class member/global/static variables to store states. Your serialize and deserialize algorithms should be stateless.
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
using namespace std;

 struct TreeNode {
      int val;
      TreeNode *left;
      TreeNode *right;
      TreeNode(int x) : val(x), left(NULL), right(NULL) {}
  };

class Codec {
private:
    TreeNode* myDeserialize(string& data, int& pos) {
        int n = data.size();
        int i = pos;
        bool found = false;
        for (; i < n; i++) {
            if (data[i] == ',' || data[i] == ']') {
                break;
            }
            if (data[i] == '[') {
                found = true;
                break;
            }
        }

        if (i == pos && i < n) {
            return nullptr;
        }

        int val = stoi(data.substr(pos, i - pos));
        TreeNode* node = new TreeNode(val);

        if (i == n) {
            return node;
        }

        pos = i;
        if (found) {
            pos++;
            node -> left = myDeserialize(data, pos);
            pos++;
            node -> right = myDeserialize(data, pos);
            pos++;
        }
        return node;
    }
public:
    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        if (!root) {
            return "";
        }
        return to_string(root -> val) + "[" + serialize(root -> left) + "," + serialize(root -> right) + "]";
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        if (data.empty()) {
            return nullptr;
        }
        int pos = 0;
        return myDeserialize(data, pos);
    }
};

// Your Codec object will be instantiated and called as such:
// Codec codec;
// codec.deserialize(codec.serialize(root));
