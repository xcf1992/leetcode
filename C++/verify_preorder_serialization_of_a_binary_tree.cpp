/*
331. Verify Preorder Serialization of a Binary Tree

One way to serialize a binary tree is to use pre-order traversal.
When we encounter a non-null node, we record the node's value.
If it is a null node, we record using a sentinel value such as #.

     _9_
    /   \
   3     2
  / \   / \
 4   1  #  6
/ \ / \   / \
# # # #   # #
For example, the above binary tree can be serialized to the string "9,3,4,#,#,1,#,#,2,#,6,#,#", where # represents a null node.

Given a string of comma separated values,
verify whether it is a correct preorder traversal serialization of a binary tree.
Find an algorithm without reconstructing the tree.

Each comma separated value in the string must be either an integer or a character '#' representing null pointer.

You may assume that the input format is always valid, for example it could never contain two consecutive commas such as "1,,3".

Example 1:

Input: "9,3,4,#,#,1,#,#,2,#,6,#,#"
Output: true
Example 2:

Input: "1,#"
Output: false
Example 3:

Input: "9,#,#,1"
Output: false
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
using namespace std;
/*
At first glance, a leaf node's pattern should look like
number,#,#,
start from the beginning of array,
once you see this pattern, convert it to a single "#",
meaning the node with value number has already been fully explored(left subtree, right subtree),
so we replace it with a "#". While iterating the array,
we just keep doing this kind of absorbing/merging backward until we reach the end of array.

Then we check if the root has been fully explored,
which should eventually be a single #.
During absorbing, if this pattern appears #,#,#, return false.
It's known that it's a pain in C++ that there is no split function as Java does,
but it won't matter here since split string is not necessary,
we just need to know before , it's a number or #.
*/
class Solution {
private:
    vector<string> split(string preorder) {
        vector<string> result;
        string cur = "";
        for (char c : preorder) {
            if (c == ',') {
                result.push_back(cur);
                cur = "";
            }
            else {
                cur.push_back(c);
            }
        }
        result.push_back(cur);
        return result;
    }
public:
    bool isValidSerialization(string preorder) {
        vector<string> token = split(preorder);
        stack<string> stk;
        int pos = 0;
        while (pos < token.size()) {
            if (token[pos] == "#") {
                while (!stk.empty() and stk.top() == "#") {
                    stk.pop();
                    if (stk.empty() or stk.top() == "#") {
                        return false;
                    }
                    stk.pop();
                }
                stk.push("#");
            }
            else {
                stk.push(token[pos]);
            }
            pos += 1;
        }
        return stk.size() == 1 and stk.top() == "#";
    }
};

class Solution1 { // too slow
private:
    void verify(string preorder, int& pos) {
        if (pos >= preorder.size()) {
            return;
        }

        if (preorder[pos] == '#') {
            pos++;
            return;
        }

        while (preorder[pos] >= '0' && preorder[pos] <= '9') {
            pos++;
        }
        pos++;
        verify(preorder, pos);
        pos++;
        verify(preorder, pos);
    }
public:
    bool isValidSerialization(string preorder) {
        int pos = 0;
        verify(preorder, pos);
        return pos == preorder.size();
    }
};
