/*
https://leetcode.com/problems/kth-largest-sum-in-a-binary-tree
2583. Kth Largest Sum in a Binary Tree
You are given the root of a binary tree and a positive integer k.

The level sum in the tree is the sum of the values of the nodes that are on the same level.

Return the kth largest level sum in the tree (not necessarily distinct). If there are fewer than k levels in the tree,
return -1.

Note that two nodes are on the same level if they have the same distance from the root.



Example 1:


Input: root = [5,8,9,2,1,3,7,4,6], k = 2
Output: 13
Explanation: The level sums are the following:
- Level 1: 5.
- Level 2: 8 + 9 = 17.
- Level 3: 2 + 1 + 3 + 7 = 13.
- Level 4: 4 + 6 = 10.
The 2nd largest level sum is 13.
Example 2:


Input: root = [1,2,null,3], k = 1
Output: 3
Explanation: The largest level sum is 3.


Constraints:

The number of nodes in the tree is n.
2 <= n <= 105
1 <= Node.val <= 106
1 <= k <= n
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
#include "extra_data_types.hpp"
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;

    TreeNode() : val(0), left(nullptr), right(nullptr) {
    }

    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {
    }

    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {
    }
};

/*
In Approach 1, our max heap stored sums for all levels of the tree, making heap operations costly.
In Approach 2, we use a min heap instead, where the smallest level sum is at the top.
As we add new level sums, if the heap size exceeds k, we remove the top element.
This ensures that, after processing all level sums, our heap contains the k largest sums,
with the k-th largest at the top, which we can return. All smaller sums would have been evicted earlier
whenever the heap size exceeded k. By limiting the heap size to k, where k≤logN, we reduce the overall time complexity.
 */
class Solution {
public:
    long long kthLargestLevelSum(TreeNode* root, int k) {
        queue<TreeNode*> bfs;
        priority_queue<long long, vector<long long>, greater<long long>> pq;
        bfs.push(root);
        while (!bfs.empty()) {
            int cur_size = bfs.size();
            long long cur_sum = 0;
            for (int i = 0; i < cur_size; i++) {
                TreeNode* cur = bfs.front();
                bfs.pop();
                cur_sum += cur->val;
                if (cur->left != nullptr) {
                    bfs.push(cur->left);
                }
                if (cur->right != nullptr) {
                    bfs.push(cur->right);
                }
            }
            pq.push(cur_sum);
            if (pq.size() > k) {
                pq.pop();
            }
        }

        if (pq.size() < k) {
            return -1;
        }
        return pq.top();
    }
};