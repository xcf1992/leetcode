/*
https://leetcode.com/problems/longest-path-with-different-adjacent-characters/
2246. Longest Path With Different Adjacent Characters

You are given a tree (i.e. a connected, undirected graph that has no cycles) rooted at node 0 consisting of n nodes
numbered from 0 to n - 1. The tree is represented by a 0-indexed array parent of size n, where parent[i] is the parent
of node i. Since node 0 is the root, parent[0] == -1.

You are also given a string s of length n, where s[i] is the character assigned to node i.

Return the length of the longest path in the tree such that no pair of adjacent nodes on the path have the same
character assigned to them.



Example 1:


Input: parent = [-1,0,0,1,1,2], s = "abacbe"
Output: 3
Explanation: The longest path where each two adjacent nodes have different characters in the tree is the path: 0 -> 1
-> 3. The length of this path is 3, so 3 is returned. It can be proven that there is no longer path that satisfies the
conditions. Example 2:


Input: parent = [-1,0,0,0], s = "aabc"
Output: 3
Explanation: The longest path where each two adjacent nodes have different characters is the path: 2 -> 0 -> 3. The
length of this path is 3, so 3 is returned.


Constraints:

n == parent.length == s.length
1 <= n <= 105
0 <= parent[i] <= n - 1 for all i >= 1
parent[0] == -1
parent represents a valid tree.
s consists of only lowercase English letters.
*/
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <cmath>
using namespace std;

class Solution {
private:
    int dfs(int currentNode, vector<vector<int>>& children, string& str, int& result) {
        // Longest and second-longest chains starting from currentNode
        // (does not count the currentNode itself).
        int longest = 0;
        int second_longest = 0;
        for (int child : children[currentNode]) {
            // Get the number of nodes in the longest path in the subtree of child,
            // including the child.
            int child_len = dfs(child, children, str, result);
            // We won't move to the child if it has the same character as the currentNode.
            if (str[currentNode] == str[child]) {
                continue;
            }
            // Modify the longestChain and secondLongestChain if longestChainStartingFromChild
            // is bigger.
            if (child_len > longest) {
                second_longest = longest;
                longest = child_len;
            } else if (child_len > second_longest) {
                second_longest = child_len;
            }
        }

        // Add "1" for the node itself.
        result = max(result, longest + second_longest + 1);
        return longest + 1;
    }

public:
    int longestPath(vector<int>& parent, string s) {
        int n = parent.size();
        vector<vector<int>> children(n);
        for (int i = 1; i < n; i++) {
            children[parent[i]].push_back(i);
        }

        int result = 1;
        dfs(0, children, s, result);
        return result;
    }
};
