/*
449. Serialize and Deserialize BST

Serialization is the process of converting a data structure
or object into a sequence of bits so that it can be stored in a file or memory buffer,
or transmitted across a network connection link to be reconstructed later in the same or another computer environment.

Design an algorithm to serialize and deserialize a binary search tree.
There is no restriction on how your serialization/deserialization algorithm should work.
You just need to ensure that a binary search tree can be serialized to a string
and this string can be deserialized to the original tree structure.

The encoded string should be as compact as possible.

Note: Do not use class member/global/static variables to store states.
Your serialize and deserialize algorithms should be stateless.
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

class Codec {
private:
    TreeNode* myDeserialize(string& data, int& pos) {
        int n = data.size();
        int i = pos;
        while (data[i] != '(' and data[i] != ')' and i < n) {
            i++;
        }

        if (i == pos) {
            return nullptr;
        }

        int val = stoi(data.substr(pos, i - pos));
        TreeNode* node = new TreeNode(val);

        pos = i;
        pos++;
        node -> left = myDeserialize(data, pos);
        pos++;
        pos++;
        node -> right = myDeserialize(data, pos);
        pos++;
        return node;
    }
public:
    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        return root == nullptr ? "" : to_string(root -> val) +
                                        "(" + serialize(root -> left) + ")" +
                                        "(" + serialize(root -> right) + ")";
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        int pos = 0;
        return myDeserialize(data, pos);
    }
};

class Codec1 {
private:
    TreeNode* myDeserialize(string& data, int& pos) {
        int n = data.size();
        int i = pos;
        bool found = false;
        for (; i < n; i++) {
            if (data[i] == ',' or data[i] == ']') {
                break;
            }
            if (data[i] == '[') {
                found = true;
                break;
            }
        }

        if (i == pos and i < n) {
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

class Codec2 {
private:
    TreeNode* parse(string data, int& pos) {
        if (data[pos] == '$') {
            pos++;
            return nullptr;
        }

        int cur = pos;
        while (data[cur] <= '9' and data[cur] >= '0') {
            cur++;
        }
        int value = stoi(data.substr(pos, cur - pos));
        TreeNode* root = new TreeNode(value);

        pos = cur + 1;
        root -> left = parse(data, pos);
        pos++;
        root -> right = parse(data, pos);
        return root;
    }
public:
    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        if (root == nullptr) {
            return "$";
        }
        return to_string(root -> val) + "," +
                serialize(root -> left) + "," +
                serialize(root -> right);
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        int pos = 0;
        return parse(data, pos);
    }
};
