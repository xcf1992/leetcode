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

class Solution {
private:
    pair<double, double> traverse(TreeNode* root, double& result) {
        if (root == nullptr) {
            return {0.0, 0.0};
        }
        
        if (root -> left == nullptr and root -> right == nullptr) {
            result = max(result, (double)(root -> val));
            return {root -> val, 1.0};
        }
        
        pair<double, double> lft = traverse(root -> left, result);
        pair<double, double> rgt = traverse(root -> left, result);
        double sum = root -> val + lft.first + rgt.first;
        double count = 1 + lft.second + rgt.second;
        double avg = sum / count;
        result = max(result, avg);
        return {sum, count};
    }
public:
    double maximumAverageSubtree(TreeNode* root) {
        double result = 0.0;
        traverse(root, result);
        return result;
    }
};

int main() {
    Solution s;
    vector<int> temp({1,3,2,4});
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
    vector<string> words({"cat","cats","and","sand","dog"});
    TreeNode* r1 = new TreeNode(0);
    TreeNode* r2 = new TreeNode(1);
    TreeNode* r3 = new TreeNode(3);
    r1 -> left = r2;
    s.maximumAverageSubtree(r1);
}
