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

class Solution {
private:
    TreeNode* find(TreeNode* node, TreeNode* prev, long& minDiff) {
        if (node -> left) {
            prev = find(node -> left, prev, minDiff);
        }

        if (prev != nullptr) {
            minDiff = min(minDiff, (long)abs(prev -> val - node -> val));
        }

        prev = node;
        if (node -> right) {
            prev = find(node -> right, prev, minDiff);
        }

        return prev;
    }
public:
    int getMinimumDifference(TreeNode* root) {
        long minDiff = INT_MAX;
        TreeNode* prev = nullptr;
        find(root, prev, minDiff);
        return minDiff;
    }
};


int main() {
    Solution s;
    return 0;
}
