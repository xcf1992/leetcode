/*
 428. Serialize and Deserialize N-ary Tree

 Serialization is the process of converting a data structure or object into a sequence of bits so that it can be stored in a file or memory buffer, 
 or transmitted across a network connection link to be reconstructed later in the same or another computer environment.

 Design an algorithm to serialize and deserialize an N-ary tree. An N-ary tree is a rooted tree in which each node has no more than N children. 
 There is no restriction on how your serialization/deserialization algorithm should work. 
 You just need to ensure that an N-ary tree can be serialized to a string and this string can be deserialized to the original tree structure.

 For example, you may serialize the following 3-ary tree
                                        1
                            /           |           \
                           3            2            4
                        /    \
                       5     6
 as [1 [3[5 6] 2 4]]. You do not necessarily need to follow this format, so please be creative and come up with different approaches yourself.

 Note:

 N is in the range of [1, 1000]
 Do not use class member/global/static variables to store states. Your serialize and deserialize algorithms should be stateless.
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
private:
    Node* decode(string data, int& pos) {
        if (data[pos] == '(' and data[pos + 1] == ')') {
            pos += 1;
            return nullptr;
        }

        Node* root = new Node();
        int value = 0;
        while (isdigit(data[pos])) {
            value = value * 10 + (data[pos] - '0');
            pos += 1;
        }
        root -> val = value;
        if (data[pos] == '(' and data[pos + 1] == ')') {
            pos += 1;
            return root;
        }

        pos += 1;

        while (data[pos] != ')') {
            root -> children.push_back(decode(data, pos));
            pos += 1;
        }
        return root;
    }
public:
    // Encodes a tree to a single string.
    string serialize(Node* root) {
        if (root == nullptr) {
            return "()";
        }
        string result = "";
        result += to_string(root -> val);
        result += "(";
        for (Node* child : root -> children) {
            result += serialize(child);
        }
        result += ")";
        return result;
    }

    // Decodes your encoded data to tree.
    Node* deserialize(string data) {
        int pos = 0;
        return decode(data, pos);
    }
};

// Your Codec object will be instantiated and called as such:
// Codec codec;
// codec.deserialize(codec.serialize(root));
