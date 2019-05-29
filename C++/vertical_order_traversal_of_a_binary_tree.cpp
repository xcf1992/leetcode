/*
 987. Vertical Order Traversal of a Binary Tree

 Given a binary tree, return the vertical order traversal of its nodes values.

 For each node at position (X, Y), its left and right children respectively will be at positions (X-1, Y-1) and (X+1, Y-1).

 Running a vertical line from X = -infinity to X = +infinity, whenever the vertical line touches some nodes, we report the values of the nodes in order from top to bottom (decreasing Y coordinates).

 If two nodes have the same position, then the value of the node that is reported first is the value that is smaller.

 Return an list of non-empty reports in order of X coordinate.  Every report will have a list of values of nodes.



 Example 1:



 Input: [3,9,20,null,null,15,7]
 Output: [[9],[3,15],[20],[7]]
 Explanation:
 Without loss of generality, we can assume the root node is at position (0, 0):
 Then, the node with value 9 occurs at position (-1, -1);
 The nodes with values 3 and 15 occur at positions (0, 0) and (0, -2);
 The node with value 20 occurs at position (1, -1);
 The node with value 7 occurs at position (2, -2).
 Example 2:



 Input: [1,2,3,4,5,6,7]
 Output: [[4],[2],[1,5,6],[3],[7]]
 Explanation:
 The node with value 5 and the node with value 6 have the same position according to the given scheme.
 However, in the report "[1,5,6]", the node value of 5 comes first since 5 is smaller than 6.


 Note:

 The tree will have between 1 and 1000 nodes.
 Each node's value will be between 0 and 1000.
 */

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

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    vector<vector<int>> verticalTraversal(TreeNode* root) {
        if (root == nullptr) {
            return {};
        }
        
        map<int, vector<pair<int, int>>> column;
        queue<pair<int, TreeNode*>> bfs;
        bfs.push({0, root});
        int row = 0;
        while (!bfs.empty()) {
            int curSize = bfs.size();
            for (int i = 0; i < curSize; ++i) {
                int pos = bfs.front().first;
                TreeNode* node = bfs.front().second;
                bfs.pop();

                column[pos].push_back({row, node -> val});
                if (node -> left) {
                    bfs.push({pos + 1, node -> left});
                }
                if (node -> right) {
                    bfs.push({pos - 1, node -> right});
                }
            }
            row += 1;
        }
        
        vector<vector<int>> result;
        for (auto it = column.begin(); it != column.end(); ++it) {
            vector<pair<int, int>> nums = it -> second;
            sort(nums.begin(), nums.end(), [](pair<int, int>& a, pair<int, int>& b) {
                return a.first < b.first or (a.first == b.first and a.second < b.second);
            });
            
            vector<int> temp;
            for (pair<int, int>& num : nums) {
                temp.push_back(num.second);
            }
            result.push_back(temp);
        }
        reverse(result.begin(), result.end());
        return result;
    }
};

class Solution1 {
public:
    vector<vector<int>> verticalTraversal(TreeNode* root) {
        map<int, vector<pair<int, int>>> topDownList;
        queue<pair<pair<int, int>, TreeNode*>> bfs;
        bfs.push({{0, 0}, root});
        while (!bfs.empty()) {
            int curSize = bfs.size();
            for (int i = 0; i < curSize; i++) {
                int x = bfs.front().first.first;
                int y = bfs.front().first.second;
                TreeNode* node = bfs.front().second;
                bfs.pop();

                topDownList[x].push_back({y, node -> val});
                if (node -> left) {
                    bfs.push({{x - 1, y + 1}, node -> left});
                }
                if (node -> right) {
                    bfs.push({{x + 1, y + 1}, node -> right});
                }
            }
        }
        vector<vector<int>> result;
        for (auto it = topDownList.begin(); it != topDownList.end(); it++) {
            vector<pair<int, int>> vals = it -> second;
            sort(vals.begin(), vals.end(), [](pair<int, int>& a, pair<int, int>& b) {
                return a.first < b.first or (a.first == b.first and a.second < b.second);
            });
            vector<int> temp;
            for (pair<int, int>& v : vals) {
                temp.push_back(v.second);
            }
            result.push_back(temp);
        }
        return result;
    }
};
