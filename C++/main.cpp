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
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
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
        pos++;
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

int main() {
    /*Solution s;
    vector<string> v({"ABD","BCE","DEF","FFF"});
    vector<int> v2({7,2,5,10,8});
    cout << s.repeatedSubstringPattern("aabaaba") << endl;
    */
    TreeNode* root = new TreeNode(2);
    root -> left = new TreeNode(1);
    root -> right = new TreeNode(3);
    Codec codec;
    string data= codec.serialize(root);
    codec.deserialize(data);
}
