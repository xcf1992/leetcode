/*
 Return any binary tree that matches the given preorder and postorder traversals.

 Values in the traversals pre and post are distinct positive integers.



 Example 1:

 Input: pre = [1,2,4,5,3,6,7], post = [4,5,2,6,7,3,1]
 Output: [1,2,3,4,5,6,7]


 Note:

 1 <= pre.length == post.length <= 30
 pre[] and post[] are both permutations of 1, 2, ..., pre.length.
 It is guaranteed an answer exists. If there exists multiple answers, you can return any of them.
 */

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <map>
#include <unordered_set>
#include <algorithm>
#include <cmath>
#include <queue>
#include <stack>
#include <stdio.h>
#include <set>
#include <numeric>
#include "extra_data_types.hpp"
using namespace std;

/*
 For two subarrays pre[a,b] and post[c,d], if we want to reconstruct a tree from them, we know that pre[a]==post[d] is the root node.

 [root][......left......][...right..]  ---pre
 [......left......][...right..][root]  ---post
 pre[a+1] is the root node of the left subtree.
 Find the index of pre[a+1] in post, then we know the left subtree should be constructed from pre[a+1, a+idx-c+1] and post[c, idx].
 */
class Solution {
public:
    unordered_map<int, int> m; // value->index
    TreeNode* constructFromPrePost(vector<int>& pre, vector<int>& post) {
        if (pre.empty()) {
            return nullptr;
        }
        int len = post.size();
        for (int i = 0; i < len; i++) {
            m[post[i]] = i;
        }
        return construct(pre, post, 0, len - 1, 0, len - 1);
    }

    TreeNode* construct(vector<int>& pre, vector<int>& post, int preS, int preE, int postS, int postE) {
        TreeNode* root = new TreeNode(pre[preS]);
        if (preS == preE) {
            return root;
        }

        int leftRoot = pre[preS + 1];
        int idx = m[leftRoot];
        int len = idx - postS + 1;
        root -> left = construct(pre, post, preS + 1, preS + len, postS, postS + len - 1);

        if (idx + 1 == postE) {
            return root;
        }

        root -> right = construct(pre, post, preS + len + 1, preE, idx + 1, postE - 1);
        return root;
    }
};
