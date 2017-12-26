#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

struct TreeNode {
    int val;
   TreeNode *left;
    TreeNode *right;
   TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

void traverse(TreeNode *root, TreeNode *pre, TreeNode *mistake1, TreeNode *mistake2) {
        if (root == nullptr) {
            return;
        }

        traverse(root->left, pre, mistake1, mistake2);
        if (pre == nullptr) {
            pre = root;
        }
        else {
            if (root->val < pre->val) {
                if (mistake1 == nullptr) {
                    mistake1 = pre;
                }
                mistake2 = root;
            }
            pre = root;
        }
        traverse(root->right, pre, mistake1, mistake2);

        return;
    }

void recoverTree(TreeNode *root) {
        if (root == nullptr) {
            return;
        }
        if (root->left == nullptr && root->right == nullptr) {
            return;
        }

        TreeNode *mistake1 = nullptr;
        TreeNode *mistake2 = nullptr;
        TreeNode *pre = nullptr;

        traverse(root->left, pre, mistake1, mistake2);
        if (pre == nullptr) {
            pre = root;
        }
        else {
            if (root->val < pre->val) {
                if (mistake1 == nullptr) {
                    mistake1 = pre;
                }
                mistake2 = root;
            }
            pre = root;
        }
        traverse(root->right, pre, mistake1, mistake2);

        if (mistake1 != nullptr && mistake2 != nullptr) {
            int temp = mistake1->val;
            mistake1->val = mistake2->val;
            mistake2->val = temp;
        }

        return;
    }

int main() {
	TreeNode *root = new TreeNode(1);
	root->left = new TreeNode(0);
	recoverTree(root);
	return 0;
}