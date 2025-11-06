/*
https://leetcode.com/problems/count-paths-that-can-form-a-palindrome-in-a-tree/description/
2791. Count Paths That Can Form a Palindrome in a Tree

You are given a tree (i.e. a connected, undirected graph that has no cycles) rooted at node 0 consisting of n nodes
numbered from 0 to n - 1. The tree is represented by a 0-indexed array parent of size n, where parent[i] is the parent
of node i. Since node 0 is the root, parent[0] == -1.

You are also given a string s of length n, where s[i] is the character assigned to the edge between i and parent[i].
s[0] can be ignored.

Return the number of pairs of nodes (u, v) such that u < v and the characters assigned to edges on the path from u to v
can be rearranged to form a palindrome.

A string is a palindrome when it reads the same backwards as forwards.



Example 1:



Input: parent = [-1,0,0,1,1,2], s = "acaabc"
Output: 8
Explanation: The valid pairs are:
- All the pairs (0,1), (0,2), (1,3), (1,4) and (2,5) result in one character which is always a palindrome.
- The pair (2,3) result in the string "aca" which is a palindrome.
- The pair (1,5) result in the string "cac" which is a palindrome.
- The pair (3,5) result in the string "acac" which can be rearranged into the palindrome "acca".
Example 2:

Input: parent = [-1,0,0,0,0], s = "aaaaa"
Output: 10
Explanation: Any pair of nodes (u,v) where u < v is valid.


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
#include <unordered_set>
#include <algorithm>
#include <cmath>
#include <queue>
#include <stack>
#include <stdio.h>
using namespace std;

/*
If the path between nodes (u, v) is rearranged to form a palindrome,
then the paths between nodes (u, root) + (v, root) are is rearranged to form a palindrome,
because the path of ancestres is calculated twice.

Bit mask
Use a bit mask to calculate the character frequency on a path.
If 1 << 1 is present, a has odd frequency.
If 1 << 2 is present, b has odd frequency.
..
If 1 << 26 is present, z has odd frequency.

Explanation
f(i) = mask calculate the path value from root node to i.
Increment result res with count[mask],
since we have count[v] paths with same value.

Increment result res with count[mask ^ (1 << 1)],
since we have count[mask ^ (1 << 1)] paths,
can merge with current path with single a in middle.

Increment result res with count[mask ^ (1 << 2)],
since we have count[mask ^ (1 << 1)] paths,
can merge with current path with single b in middle.

..
After we calculate the pair for node i,
also need to update count[mask] += 1.

Continue doing this for all nodes,
and finally return result res in the end.
 */
class Solution {
private:
    int get_mask(vector<int>& masks, vector<int>& parent, string& s, int i) {
        if (i == 0 || parent[i] == -1) {
            return 0;
        }

        if (masks[i] == 0) {
            int parent_mask = get_mask(masks, parent, s, parent[i]);
            masks[i] = parent_mask ^ (1 << (s[i] - 'a'));
        }
        return masks[i];
    }

public:
    long long countPalindromePaths(vector<int>& parent, string s) {
        int n = parent.size();
        long long res = 0;
        vector<int> masks(n, 0);
        unordered_map<int, int> count;
        for (int i = 0; i < n; i++) {
            int mask = get_mask(masks, parent, s, i);

            // count the path with all even count of character
            res += count[mask];

            // count the path can have one odd character
            for (int j = 0; j < 26; j++) {
                int temp_mask = mask ^ (1 << j);
                if (count.find(temp_mask) == count.end()) {
                    continue;
                }
                res += count[temp_mask];
            }

            count[mask] += 1;
        }
        return res;
    }
};
