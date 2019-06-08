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

class CBTInserter {
private:
    TreeNode* r = nullptr;
    queue<TreeNode*> row;
public:
    CBTInserter(TreeNode* root) {
        r = root;
        row.push(root);
        TreeNode* cur = row.front();
        while (cur -> left != nullptr and cur -> right != nullptr) {
            row.pop();
            row.push(cur -> left);
            row.push(cur -> right);
            cur = row.front();
        }
    }

    int insert(int v) {
        TreeNode* cur = row.front();
        if (cur -> left == nullptr) {
            cur -> left = new TreeNode(v);
            row.push(cur -> left);
        }
        else {
            cur -> right = new TreeNode(v);
            row.push(cur -> right);
            row.pop();
        }
        return cur -> val;
    }

    TreeNode* get_root() {
        return r;
    }
};



int main() {
    //Solution s;
    vector<int> temp({1,15,7,9,2,5,10});
    vector<vector<int>> matrix({
        {0,1,0},
        {1,1,1},
        {0,1,0}
    });

    TreeNode* r = new TreeNode(1);
    r -> left = new TreeNode(2);
    CBTInserter it(r);
    it.insert(3);

    it.insert(4);
}
