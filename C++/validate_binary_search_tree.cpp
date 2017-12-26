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

class Solution {
private:
    bool hasPre;
    int preVal;
public:
    bool isValidBST(TreeNode *root) {
        hasPre = false;
        preVal = 0;
        return visit(root);
    }

    bool visit(TreeNode *root) {
        if (root == nullptr) {
            return true;
        }

        if (visit(root->left)) {
            if (hasPre) {
                if (preVal < root->val) {
                    preVal = root->val;
                    visit(root->right);
                }
                else {
                    return false;
                }
            }
            else {
                hasPre = true;
                preVal = root->val;
                return visit(root->right);
            }
        }
        return false;
    }
};

int main() {
	Solution s;
	TreeNode *root = new TreeNode(0);
	root->left = new TreeNode(-1);
	root->right = nullptr;
	s.isValidBST(root);
	return 0;
}