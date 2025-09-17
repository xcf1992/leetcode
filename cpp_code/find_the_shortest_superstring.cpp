/*
943. Find the Shortest Superstring
Given an array A of strings, find any smallest string that contains each string in A as a substring.

We may assume that no string in A is substring of another string in A.


Example 1:

Input: ["alex","loves","leetcode"]
Output: "alexlovesleetcode"
Explanation: All permutations of "alex","loves","leetcode" would also be accepted.
Example 2:

Input: ["catg","ctaagt","gcta","ttca","atgcatc"]
Output: "gctaagttcatgcatc"


Note:

1 <= A.length <= 12
1 <= A[i].length <= 20
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
#include <numeric>
using namespace std;
/*
graph[i][j] means the length of string to append when A[i] followed by A[j].
eg. A[i] = abcd, A[j] = bcde, then graph[i][j] = 1

Then the problem becomes to: find the shortest path in this graph which visits every node exactly once.
This is a Travelling Salesman Problem.

Apply TSP DP solution. Remember to record the path.
Time complexity: O(n^2 * 2^n)
https://en.wikipedia.org/wiki/Held%E2%80%93Karp_algorithm
https://leetcode.com/problems/find-the-shortest-superstring/discuss/194932/Travelling-Salesman-Problem
https://leetcode.com/problems/find-the-shortest-superstring/discuss/195290/C++-solution-in-less-than-30-lines

We can use dynamic programming to leverage this recursion.
Let dp(mask, i) be the total overlap after putting some words down (represented by a bitmask mask),
for which A[i] was the last word put down.
Then, the key recursion is
dp(mask ^ (1<<j), j) = max(overlap(A[i], A[j]) + dp(mask, i)),
where the jth bit is not set in mask, and i ranges over all bits set in mask.

Of course, this only tells us what the maximum overlap is for each set of words.
We also need to remember each choice along the way (ie. the specific i that made dp(mask ^ (1<<j), j) achieve a minimum)
so that we can reconstruct the answer.
*/
class Solution {
private:
    int count(string a, string b) {
        int len = min(a.size(), b.size());
        for (int i = len; i > 0; i--) {
            if (a.substr(a.size() - i) == b.substr(0, i)) {
                return i;
            }
        }
        return 0;
    }
public:
    string shortestSuperstring(vector<string>& A) {
        int n = A.size();
        vector<vector<int>> overlap(n, vector<int>(n, 0)); // overlap[i][j], means the number of letters overlapped when put A[j] after A[i]
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i != j) {
                    overlap[i][j] = count(A[i], A[j]);
                }
            }
        }

        // dp[mask][i] : min superstring made by strings in mask,
        // and the last one is A[i]
        vector<vector<string>> dp(1 << n, vector<string>(n, ""));
        for (int i = 0; i < n; i++) {
            dp[1 << i][i] += A[i];
        }

        for (int mask = 1; mask < (1 << n); mask++) {
            for (int j = 0; j < n; j++) if ((mask & (1 << j)) > 0) { // (mask & (1 << j)) > 0 means city j will be visited
                for (int i = 0; i < n; i++) if (i != j and (mask & (1 << i)) > 0) { // we will put word j after word i
                    // so for min super word end with word i dp[mask ^ (1 << j)][i] under current mask
                    // we put A[j].substr(overlap[i][j]) after it to creat new super word end with j under current mask
                    string temp = dp[mask ^ (1 << j)][i] + A[j].substr(overlap[i][j]);
                    if (dp[mask][j].empty() or temp.size() < dp[mask][j].size()) {
                        dp[mask][j] = temp;
                    }
                }
            }
        }

        int last = (1 << n) - 1;
        string result = dp[last][0];
        for (int i = 1; i < n; i++) {
            if (dp[last][i].size() < result.size()) {
                result = dp[last][i];
            }
        }
        return result;
    }
};
