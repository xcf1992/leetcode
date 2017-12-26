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

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 * };
 */
class Solution {
private:
    unordered_map<int, int> frequency;
    int mostFrequent = 0;

    void getSum(TreeNode* root) {
        if (root == nullptr) {
            return;
        }

        if (root -> left != nullptr) {
            getSum(root -> left);
            root -> val += root -> left -> val;
        }
        if (root -> right != nullptr) {
            getSum(root -> right);
            root -> val += root -> right -> val;
        }

        frequency[root -> val] += 1;
        mostFrequent = max(mostFrequent, frequency[root -> val]);
    }
public:
    vector<int> findFrequentTreeSum(TreeNode* root) {
        vector<int> result;

        getSum(root);

        for (auto iter : frequency) {
            if (iter.second == mostFrequent) {
                result.push_back(iter.first);
            }
        }
        return result;
    }
};

int main() {
    Solution s;
    return 0;
}
