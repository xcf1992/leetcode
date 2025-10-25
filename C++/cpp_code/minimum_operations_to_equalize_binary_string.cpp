/*
https://leetcode.com/problems/minimum-operations-to-equalize-binary-string/
3666. Minimum Operations to Equalize Binary String
You are given a binary string s, and an integer k.

In one operation, you must choose exactly k different indices and flip each '0' to '1' and each '1' to '0'.

Return the minimum number of operations required to make all characters in the string equal to '1'. If it is not possible, return -1.



Example 1:

Input: s = "110", k = 1

Output: 1

Explanation:

There is one '0' in s.
Since k = 1, we can flip it directly in one operation.
Example 2:

Input: s = "0101", k = 3

Output: 2

Explanation:

One optimal set of operations choosing k = 3 indices in each operation is:

Operation 1: Flip indices [0, 1, 3]. s changes from "0101" to "1000".
Operation 2: Flip indices [1, 2, 3]. s changes from "1000" to "1111".
Thus, the minimum number of operations is 2.

Example 3:

Input: s = "101", k = 2

Output: -1

Explanation:

Since k = 2 and s has only one '0', it is impossible to flip exactly k indices to make all '1'. Hence, the answer is -1.



Constraints:

1 <= s.length <= 10^5
s[i] is either '0' or '1'.
1 <= k <= s.length
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
#include <set>
#include <map>
#include <numeric>
using namespace std;

class Solution {
private:
    int find_parent(int cur, vector<int>& parent) {
        if (parent[cur] == -1) {
            return cur;
        }
        parent[cur] = find_parent(parent[cur], parent);
        return parent[cur];
    }

public:
    long long countPairs(int n, vector<vector<int>>& edges) {
        vector<int> parent(n, -1);
        unordered_map<int, int> group;
        for (const vector<int>& edge : edges) {
            int u = find_parent(edge[0], parent);
            int v = find_parent(edge[1], parent);
            if (u == v) {
                continue;
            }
            parent[u] = v;
        }

        for (int i = 0; i < n; i++) {
            int cur_parent = find_parent(i, parent);
            if (group.find(cur_parent) == group.end()) {
                group[cur_parent] = 0;
            }
            group[cur_parent] += 1;
        }

        long long result = 0;
        int other_cnt = n;
        for (auto it = group.begin(); it != group.end(); it++) {
            int cur_cnt = it->second;
            other_cnt -= cur_cnt;
            result += cur_cnt * other_cnt;
        }
        return result;
    }
};
