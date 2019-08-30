/*
431. Encode N-ary Tree to Binary Tree

Design an algorithm to encode an N-ary tree into a binary tree
and decode the binary tree to get the original N-ary tree.

An N-ary tree is a rooted tree in which each node has no more than N children.
Similarly, a binary tree is a rooted tree in which each node has no more than 2 children.

There is no restriction on how your encode/decode algorithm should work.
You just need to ensure that an N-ary tree can be encoded to a binary tree
and this binary tree can be decoded to the original N-nary tree structure.

For example, you may encode the following 3-ary tree to a binary tree in this way:
                1                                   1
        /       |       \                         /    \
       3        2        4  ==>                 3       2
     /   \                                     /         \
    5    6                                    5           4
                                               \
                                                6
Note that the above is just an example which might or might not work.
You do not necessarily need to follow this format,
so please be creative and come up with different approaches yourself.

Note:

N is in the range of [1, 1000]
Do not use class member/global/static variables to store states. Your encode and decode algorithms should be stateless.
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
#include <set>
#include "extra_data_types.hpp"
using namespace std;

// Definition for a Node.
class Node {
public:
    int val = NULL;
    vector<Node*> children;

    Node() {}

    Node(int _val, vector<Node*> _children) {
        val = _val;
        children = _children;
    }
};

class Codec {
public:
    // Encodes an n-ary tree to a binary tree.
    TreeNode* encode(Node* root) {
        if (root == nullptr) {
            return nullptr;
        }

        TreeNode* bRoot = new TreeNode(root -> val);
        TreeNode* cur = bRoot;
        vector<Node*> children = root -> children;
        for (int i = 0; i < children.size(); ++i) {
            Node* child = children[i];
            if (i == 0) {
                cur -> left = encode(child);
                cur = cur -> left;
            }
            else {
                cur -> right = encode(child);
                cur = cur -> right;
            }
        }
        return bRoot;
    }

    // Decodes your binary tree to an n-ary tree.
    Node* decode(TreeNode* root) {
        if (root == nullptr) {
            return nullptr;
        }

        Node* nRoot = new Node();
        nRoot -> val = root -> val;
        TreeNode* cur = root;
        if (cur -> left != nullptr) {
            nRoot -> children.push_back(decode(cur -> left));
            cur = cur -> left;
            while (cur -> right != nullptr) {
                nRoot -> children.push_back(decode(cur -> right));
                cur = cur -> right;
            }
        }
        return nRoot;
    }
};
// Your Codec object will be instantiated and called as such:
// Codec codec;
// codec.decode(codec.encode(root));
