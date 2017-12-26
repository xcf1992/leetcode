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

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 * };
 */
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