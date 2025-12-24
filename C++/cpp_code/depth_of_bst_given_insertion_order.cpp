/*
https://leetcode.com/problems/depth-of-bst-given-insertion-order/description/
1902. Depth of BST Given Insertion Order

You are given a 0-indexed integer array order of length n, a permutation of integers from 1 to n representing the order
of insertion into a binary search tree.

A binary search tree is defined as follows:

The left subtree of a node contains only nodes with keys less than the node's key.
The right subtree of a node contains only nodes with keys greater than the node's key.
Both the left and right subtrees must also be binary search trees.
The binary search tree is constructed as follows:

order[0] will be the root of the binary search tree.
All subsequent elements are inserted as the child of any existing node such that the binary search tree properties hold.
Return the depth of the binary search tree.

A binary tree's depth is the number of nodes along the longest path from the root node down to the farthest leaf node.



Example 1:


Input: order = [2,1,4,3]
Output: 3
Explanation: The binary search tree has a depth of 3 with path 2->3->4.
Example 2:


Input: order = [2,1,3,4]
Output: 3
Explanation: The binary search tree has a depth of 3 with path 2->3->4.
Example 3:


Input: order = [1,2,3,4]
Output: 4
Explanation: The binary search tree has a depth of 4 with path 1->2->3->4.


Constraints:

n == order.length
1 <= n <= 105
order is a permutation of integers between 1 and n.
*/
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <cmath>
#include <queue>
#include <stack>
#include <climits>
using namespace std;

/*
The idea is to find the two closest values to the current value being inserted; one greater and one smaller. The depth
of the current node then is the max of those two plus 1.

Why to find the smaller and bigger value than current one?
Imagine constructing a BST. When we insert a value into the tree, the value can either be the left child of a bigger
valued node or the right child of a smaller valued node. Therefore, these adjacent values are the values of interest for
the current node. Rest are irrelevant.

Why taking max from those two?
Because the smaller depth node would be higher up in the tree being the ancestor of the bigger depth node. The bigger
depth node will have place for current node to be inserted.

Code :
We store the depths of each node in a map so that searching for a value smaller and bigger than current value takes only
O(log n) time. Space used is O(n) because of map.

To find the next greater value than current : directly used upper_bound
To find the nearest smaller value than current : used lower_bound. Lower_bound returns the element greater than or equal
to the key searched. Therefore the element previous to lower_bound is actually what we want.
 */
class Solution {
public:
    int maxDepthBST(vector<int>& order) {
        map<int, int> depth;
        depth[order[0]] = 1;

        int n = order.size();
        int rst = 1;
        for (int i = 1; i < n; i++) {
            auto greater_it = depth.upper_bound(order[i]);
            auto less_it = depth.lower_bound(order[i]);
            int left_depth = 0;
            int right_depth = 0;
            if (less_it == depth.end()) {
                left_depth = depth.rbegin()->second;
            } else if (less_it != depth.begin()) {
                left_depth = (prev(less_it))->second;
            }

            if (greater_it != depth.end()) {
                right_depth = greater_it->second;
            }

            depth[order[i]] = max(left_depth, right_depth) + 1;
            rst = max(rst, depth[order[i]]);
        }
        return rst;
    }
};

class Solution {
public:
    int maxDepthBST(vector<int>& order) {
        map<int, int> m{{0, 0}, {100001, 0}};
        for (int i : order) {
            auto it = m.upper_bound(i);
            m[i] = 1 + max(it->second, prev(it)->second);
        }
        return max_element(begin(m), end(m), [](const auto& a, const auto& b) { return a.second < b.second; })->second;
    }
};
