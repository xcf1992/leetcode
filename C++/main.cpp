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
#include <numeric>
#include "extra_data_types.hpp"
using namespace std;

class Codec {
public:

    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        return root == nullptr ? "" : to_string(root -> val) +
        "(" + serialize(root -> left) + ")" +
        "(" + serialize(root -> right) + ")";
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        cout << data;
        int pos = 0;
        return myDeserialize(data, pos);
    }

    TreeNode* myDeserialize(string& data, int& pos) {
        int n = data.size();
        int i = pos;
        bool found = false;

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
};

int main() {
    TreeNode* r = new TreeNode(2);
    r -> left = new TreeNode(1);
    r -> right = new TreeNode(3);
    Codec co;
    string x = co.serialize(r);
    co.deserialize(x);

    vector<int> temp1({1,3,3,3,2});
    vector<vector<int>> matrix({
        {0,1},
        {1,2},
        {2,1},
        {1,0},
        {0,2},
        {0,0},
        {1,1}
    });
    vector<vector<int>> matrix2({
        {1,2,2,3,5},
        {3,2,3,4,4},
        {2,4,5,3,1},
        {6,7,1,4,5},
        {5,1,1,2,4}
    });
    vector<string> words({"hot","dot","dog","lot","log","cog"});
    TreeNode* r1 = new TreeNode(0);
    TreeNode* r2 = new TreeNode(1);
    TreeNode* r3 = new TreeNode(3);
    r1 -> left = r2;
}
