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
public:
    TreeNode *upsideDownBinaryTree(TreeNode *root) {
        if (root == nullptr) {
            return root;
        }

        TreeNode *left = root->left;
        TreeNode *right = root->right;
        TreeNode *node = upsideDown(left);
        if (node == nullptr) {
            return root;
        }

        node->left = right;
        node->right = root;
        root->right = nullptr;
        return left;
    }

    TreeNode *upsideDown(TreeNode *root) {
        if (root == nullptr) {
            return nullptr;
        }

        TreeNode *left = root->left;
        TreeNode *right = root->right;

        TreeNode *newLeft = upsideDown(left);
        if (newLeft == nullptr) {
            return root;
        }

        newLeft->left = right;
        newLeft->right = root;
        root->right = nullptr;

        return root;
    }
};


int numSeqHelper(int ones, int twos, int threes, int fours, int last){
	if(ones ==0 && twos ==0 && threes ==0 && fours ==0)
		return 1;

	int sum = 0;

	if(last != 1 && ones != 0)
		sum += numSeqHelper(ones-1, twos, threes, fours, 1);
	if(last != 2 && twos != 0)
		sum += numSeqHelper(ones, twos-1, threes, fours, 2);
	if(last != 3 && threes != 0)
		sum += numSeqHelper(ones, twos, threes-1, fours, 3);
	if(last != 4 && fours != 0)
		sum += numSeqHelper(ones, twos, threes, fours-1, 4);

	return sum;
}

int numSeq(int ones, int twos, int threes, int fours){
	 return numSeqHelper(ones, twos, threes, fours, 0) ;
}
int main() {
	int i = numSeq(1,1,1,4);
	return 0;
}