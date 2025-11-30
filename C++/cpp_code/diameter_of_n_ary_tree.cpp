/*
https://leetcode.com/problems/diameter-of-n-ary-tree/
1522. Diameter of N-Ary Tree

Given a root of an N-ary tree, you need to compute the length of the diameter of the tree.

The diameter of an N-ary tree is the length of the longest path between any two nodes in the tree. This path may or may
not pass through the root.

(Nary-Tree input serialization is represented in their level order traversal, each group of children is separated by the
null value.)



Example 1:



Input: root = [1,null,3,2,4,null,5,6]
Output: 3
Explanation: Diameter is shown in red color.
Example 2:



Input: root = [1,null,2,null,3,4,null,5,null,6]
Output: 4
Example 3:



Input: root = [1,null,2,3,4,5,null,null,6,7,null,8,null,9,10,null,null,11,null,12,null,13,null,null,14]
Output: 7


Constraints:

The depth of the n-ary tree is less than or equal to 1000.
The total number of nodes is between [1, 104].
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
#include <climits>
#include <map>
using namespace std;

/*
// Definition for a Node.
*/

class Node {
public:
    int val;
    vector<Node*> children;

    Node() {
    }

    Node(int _val) {
        val = _val;
    }

    Node(int _val, vector<Node*> _children) {
        val = _val;
        children = _children;
    }
};

class Solution {
private:
    int longest_path_len(Node* root, int& result) {
        if (root == nullptr) {
            return -1;
        }

        int longest = -1;
        int longer = -1;
        for (Node* nxt : root->children) {
            int path_len = longest_path_len(nxt, result);
            if (path_len >= longest) {
                longer = longest;
                longest = path_len;
            } else if (path_len > longer) {
                longer = path_len;
            }
        }

        result = max(result, longest + longer + 2);
        return 1 + longest;
    }

public:
    int diameter(Node* root) {
        int result = 0;
        longest_path_len(root, result);
        return result;
    }
};