/*
1028. Recover a Tree From Preorder Traversal

We run a preorder depth first search on the root of a binary tree.

At each node in this traversal,
we output D dashes (where D is the depth of this node),
then we output the value of this node.
(If the depth of a node is D, the depth of its immediate child is D+1.
The depth of the root node is 0.)

If a node has only one child, that child is guaranteed to be the left child.
Given the output S of this traversal, recover the tree and return its root.

Example 1:
                                        1
                2                                       5
            3       4                               6       7
Input: "1-2--3--4-5--6--7"
Output: [1,2,5,3,4,6,7]

 Example 2:
                            1
        2                                       5
    3                                       6
4                                         7
Input: "1-2--3---4-5--6---7"
Output: [1,2,5,3,null,6,null,4,null,7]

 Example 3:
                1
            401
        349         88
90
Input: "1-401--349---90--88"
Output: [1,401,null,349,88,90]

Note:
The number of nodes in the original tree is between 1 and 1000.
Each node will have a value between 1 and 10^9.
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
#include "extra_data_types.hpp"
using namespace std;

class Solution {
private:
    int getNumber(string S, int &start) {
        int num = 0;
        while (start < S.size() and isdigit(S[start])
        )
        {
            num = num * 10 + (S[start] - '0');
            start += 1;
        }
        return num;
    }

public:
    TreeNode *recoverFromPreorder(string S) {
        int n = S.size();
        if (n == 0) {
            return nullptr;
        }

        stack<pair<int, TreeNode *> > stk;
        int start = 0;
        int curNum = getNumber(S, start);
        TreeNode *root = new TreeNode(curNum);
        stk.push({0, root});
        while (start < n) {
            int height = 0;
            while (start < n and S[start]
            ==
            '-'
            )
            {
                start += 1;
                height += 1;
            }
            curNum = getNumber(S, start);
            TreeNode *curNode = new TreeNode(curNum);

            while (!stk.empty() and
            stk.top().first != height - 1
            )
            {
                stk.pop();
            }
            TreeNode *parent = stk.top().second;
            if (parent->left == nullptr) {
                parent->left = curNode;
            } else {
                parent->right = curNode;
            }
            stk.push({height, curNode});
        }
        return root;
    }
};