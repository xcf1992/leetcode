#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;


struct TreeLinkNode {
	int val;
	TreeLinkNode *left, *right, *next;
	TreeLinkNode(int x) : val(x), left(nullptr), right(nullptr), next(nullptr) {}
};

class Solution {
public:
    void connect(TreeLinkNode *root) {
        if ( root == nullptr) {
            return ;
        }

        struct TreeLinkNode * leftmost = root;
        struct TreeLinkNode * current = nullptr;

        while (leftmost != nullptr) {
            current = leftmost;
            TreeLinkNode * newleft = nullptr;
            TreeLinkNode * newright = nullptr;

            while (current != nullptr) {

                while (newleft == nullptr && current != nullptr) {
                    if (current->left != nullptr) {
                        newleft = current->left;
                    }
                    else if (current->right != nullptr) {
                        newleft = current->right;
                    }
                    else {
                        current = current->next;
                    }
                }

                while (newright == nullptr && current != nullptr) {
                    if (current->left != nullptr && newleft != current->left) {
                        newright = current->left;
                    }
                    else if (current->right != nullptr && newleft != current->right) {
                        newright = current->right;
                    }
                    else {
                        current = current->next;
                    }
                }

                if (newleft != nullptr) {
                    if ((newright == nullptr && current == nullptr) || (newright != nullptr)) {
                        newleft->next = newright;
                        newleft = newright;
                        newright = nullptr;
                    }
                }
            }

            TreeLinkNode * newleftmost = nullptr;
            while (newleftmost == nullptr && leftmost != nullptr) {
                if (leftmost->left != nullptr) {
                    newleftmost = leftmost->left;
                }
                else if (leftmost->right != nullptr) {
                    newleftmost = leftmost->right;
                }
                else {
                    leftmost = leftmost->next;
                }
            }
            leftmost = newleftmost;
        }

        return ;
    }
};

int main() {
	TreeLinkNode *root = new TreeLinkNode(1);
	root->left = new TreeLinkNode(2);
	root->right = new TreeLinkNode(3);
	Solution s;
	s.connect(root);
	return 0;
}