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

class Codec1 {
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


class Codec {
private:
    TreeNode* parse(string data, int& pos) {
        if (data[pos] == '$') {
            pos++;
            return nullptr;
        }
        
        int cur = pos;
        while (data[cur] <= '9' && data[cur] >= '0') {
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

class Codec2 {
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
    
    TreeNode* myDeserialize(string& data, int& pos) {
        int n = data.size();
        int i = pos;
        bool found = false;
        
        while (data[i] != '(' && data[i] != ')' && i < n) {
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
};
