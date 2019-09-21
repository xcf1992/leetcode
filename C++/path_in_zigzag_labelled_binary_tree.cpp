/*
1104. Path In Zigzag Labelled Binary Tree
https://leetcode.com/problems/path-in-zigzag-labelled-binary-tree/

In an infinite binary tree where every node has two children,
the nodes are labelled in row order.
In the odd numbered rows (ie., the first, third, fifth,...),
the labelling is left to right,
while in the even numbered rows (second, fourth, sixth,...),
the labelling is right to left.

Given the label of a node in this tree,
return the labels in the path from the root of the tree to the node with that label.
                                                                1
                            3                                                                   2
        4                                           5                           6                               7
15          14                                  13       12                 11      10                      9           8

Example 1:
Input: label = 14
Output: [1,3,4,14]

Example 2:
Input: label = 26
Output: [1,2,6,10,26]

Constraints:
1 <= label <= 10^6
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
#include <set>
#include <numeric>
using namespace std;
/*
Determine the tree level where our value is located.
The maximum label in the level is 1 << level - 1,
and minimum is 1 << (level - 1).
We will use this fact to "invert" the parent label.
*/
class Solution {
public:
    vector<int> pathInZigZagTree(int label) {
        int level = 1;
        while ((1 << level) <= label) {
            level += 1;
        }

        vector<int> result(level, 1);
        while (label > 1) {
            result[level - 1] = label;
            level -= 1;

            int parentStart = 1 << (level - 1);
            int parentEnd = (1 << level) - 1;
            label = parentEnd - (label / 2 - parentStart);
        }
        return result;
    }
};
