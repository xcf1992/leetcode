/*
给一个二叉树, 节点如果只有一个子节点, 则把它的子节点删除并折叠进这个节点中, 并把它的数值累加入它的父节点.
例如:
         1
        /
     2
  /
3
*/
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <cmath>
#include <queue>
#include <set>
#include <climits>
#include <map>
#include <cassert>
using namespace std;

/*
题意是：如果一个节点只有一个子节点（只有左孩子或只有右孩子），那就把这个子节点"吸收"掉——删掉子节点，把子节点的值加到自己身上。然后继续检查，因为吸收后可能还是只有一个子节点。
用题目给的例子：
     1
    /
   2
  /
 3
节点1只有左孩子2 → 吸收2，值变成1+2=3，把2的子树接上来：
     3    (原来的1，吸收了2)
    /
   3
节点3（原来的1）还是只有左孩子3 → 继续吸收，值变成3+3=6：
     6    (叶子节点，没有子节点了，停止)
再来一个更复杂的例子帮助理解：
       1
      / \
     2   3
    /
   4
  / \
 5   6
从下往上看：节点4有两个孩子（5和6）→ 不动。节点2只有左孩子4 → 吸收4，值变成2+4=6，接管4的两个孩子。节点1有两个孩子 →
不动。节点3是叶子 → 不动。 结果：
       1
      / \
     6   3
    / \
   5   6
简单说就是：链状的路径（每个节点只有一个孩子的那种长链）压缩成一个节点，值全部累加。 有点像路径压缩的味道。
 */

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {
    }
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {
    }
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {
    }
};

class Solution {
public:
    TreeNode* squash(TreeNode* root) {
        if (root == nullptr) {
            return nullptr;
        }

        if (root->left == nullptr && root->right == nullptr) {
            return root;
        }

        root->left = squash(root->left);
        root->right = squash(root->right);

        if (root->left != nullptr && root->right == nullptr) {
            TreeNode* child = root->left;
            root->left = child->left;
            root->right = child->right;
            root->val += child->val;
            delete child;
        }

        if (root->left == nullptr && root->right != nullptr) {
            TreeNode* child = root->right;
            root->left = child->left;
            root->right = child->right;
            root->val += child->val;
            delete child;
        }
        return root;
    }
};

// Serialize tree to string for easy comparison
string serialize(TreeNode* root) {
    if (!root) return "null";
    string result;
    queue<TreeNode*> q;
    q.push(root);
    while (!q.empty()) {
        auto* n = q.front(); q.pop();
        if (n) {
            result += to_string(n->val) + " ";
            q.push(n->left);
            q.push(n->right);
        } else {
            result += "null ";
        }
    }
    // trim trailing nulls
    while (result.size() > 5 && result.substr(result.size() - 5) == "null ") {
        result = result.substr(0, result.size() - 5);
    }
    return result;
}

void test(string name, TreeNode* root, string expected) {
    Solution sol;
    root = sol.squash(root);
    string got = serialize(root);
    bool pass = (got == expected);
    cout << (pass ? "PASS" : "FAIL") << " | " << name << endl;
    if (!pass) {
        cout << "  got:      " << got << endl;
        cout << "  expected: " << expected << endl;
    }
}

int main() {
    // Test 1: 1->2->3 (left chain)
    // Expected: 6
    {
        auto* r = new TreeNode(1);
        r->left = new TreeNode(2);
        r->left->left = new TreeNode(3);
        test("left chain 1->2->3", r, "6 ");
    }

    // Test 2: 1->2->3 (right chain)
    // Expected: 6
    {
        auto* r = new TreeNode(1);
        r->right = new TreeNode(2);
        r->right->right = new TreeNode(3);
        test("right chain 1->2->3", r, "6 ");
    }

    // Test 3: mixed chain (left then right)
    //     1
    //    /
    //   2
    //    \
    //     3
    // 2 has only right child -> absorb 3 -> 2 becomes 5 (leaf)
    // 1 has only left child 5 -> absorb -> 1 becomes 6 (leaf)
    {
        auto* r = new TreeNode(1);
        r->left = new TreeNode(2);
        r->left->right = new TreeNode(3);
        test("zigzag chain left-right", r, "6 ");
    }

    // Test 4: full binary tree, nothing to squash
    //       1
    //      / \
    //     2   3
    {
        auto* r = new TreeNode(1, new TreeNode(2), new TreeNode(3));
        test("full tree no squash", r, "1 2 3 ");
    }

    // Test 5: complex tree from earlier example
    //        1
    //       / \
    //      2   3
    //     /
    //    4
    //   / \
    //  5   6
    // Node 2 absorbs 4 -> val=6, gets children 5,6
    // Result:  1
    //         / \
    //        6   3
    //       / \
    //      5   6
    {
        auto* r = new TreeNode(1);
        r->left = new TreeNode(2);
        r->right = new TreeNode(3);
        r->left->left = new TreeNode(4);
        r->left->left->left = new TreeNode(5);
        r->left->left->right = new TreeNode(6);
        test("complex tree", r, "1 6 3 5 6 ");
    }

    // Test 6: single node
    {
        auto* r = new TreeNode(42);
        test("single node", r, "42 ");
    }

    // Test 7: null tree
    {
        Solution sol;
        TreeNode* r = sol.squash(nullptr);
        bool pass = (r == nullptr);
        cout << (pass ? "PASS" : "FAIL") << " | null tree" << endl;
    }

    // Test 8: long left chain 1->2->3->4->5
    // All collapse into one node: 1+2+3+4+5 = 15
    {
        auto* r = new TreeNode(1);
        r->left = new TreeNode(2);
        r->left->left = new TreeNode(3);
        r->left->left->left = new TreeNode(4);
        r->left->left->left->left = new TreeNode(5);
        test("long chain 1-5", r, "15 ");
    }

    // Test 9: chain then fork
    //      1
    //       \
    //        2
    //       / \
    //      3   4
    // Node 1 absorbs 2 (only right child) -> val=3, gets children 3,4
    // Result:  3
    //         / \
    //        3   4
    {
        auto* r = new TreeNode(1);
        r->right = new TreeNode(2);
        r->right->left = new TreeNode(3);
        r->right->right = new TreeNode(4);
        test("chain then fork", r, "3 3 4 ");
    }

    // Test 10: both subtrees have chains
    //        1
    //       / \
    //      2   5
    //     /     \
    //    3       6
    //   / \     / \
    //  7   8   9  10
    // Left: 2 absorbs 3 -> val=5, children 7,8
    // Right: 5 absorbs 6 -> val=11, children 9,10
    // Result:     1
    //            / \
    //           5   11
    //          / \ / \
    //         7  8 9  10
    {
        auto* r = new TreeNode(1);
        r->left = new TreeNode(2);
        r->left->left = new TreeNode(3);
        r->left->left->left = new TreeNode(7);
        r->left->left->right = new TreeNode(8);
        r->right = new TreeNode(5);
        r->right->right = new TreeNode(6);
        r->right->right->left = new TreeNode(9);
        r->right->right->right = new TreeNode(10);
        test("both subtrees chain", r, "1 5 11 7 8 9 10 ");
    }

    return 0;
}
