/*
1718. Construct the Lexicographically Largest Valid Sequence
https://leetcode.com/problems/construct-the-lexicographically-largest-valid-sequence/

Given an integer n, find a sequence that satisfies all of the following:

The integer 1 occurs once in the sequence.
Each integer between 2 and n occurs twice in the sequence.
For every integer i between 2 and n, the distance between the two occurrences of i is exactly i.
The distance between two numbers on the sequence,
a[i] and a[j], is the absolute difference of their indices, |j - i|.

Return the lexicographically largest sequence.
It is guaranteed that under the given constraints, there is always a solution.

A sequence a is lexicographically larger than a sequence b (of the same length)
if in the first position where a and b differ, sequence a has a number greater than the corresponding number in b.
For example, [0,1,9,0] is lexicographically larger than [0,1,5,6]
because the first position they differ is at the third number, and 9 is greater than 5.

Example 1:
Input: n = 3
Output: [3,1,2,3,2]
Explanation: [2,3,2,1,3] is also a valid sequence, but [3,1,2,3,2] is the lexicographically largest valid sequence.
Example 2:
Input: n = 5
Output: [5,3,1,4,3,5,2,4,2]

Constraints:
1 <= n <= 20
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
#include <climits>
#include <set>
#include <numeric>
using namespace std;

class Solution {
    vector<int> used;
    bool dfs(vector<int>& ans, int i) {
        if (i == ans.size()) {
            return true;  // filled all the numbers, found the answer
        }

        if (ans[i]) {
            return dfs(ans, i + 1);  // this index is already filled, continue to fill the next index.
        }

        for (int j = used.size() - 1; j > 0; --j) {  // try each number in decending order from n -1 to 1.
            if (used[j]) {
                continue;  // j is already used, skip
            }

            if (j != 1 && (i + j >= ans.size() || ans[i + j])) {
                continue;  // we can't fill `ans[i + j]` either because `i + j` is out of bound or `ans[i + j]` is
                           // already filled. Skip.
            }

            used[j] = 1;  // mark number `j` as used.
            ans[i] = j;   // fill `ans[j]` and `ans[i + j]` (if needed) with `j`.
            if (j != 1) {
                ans[i + j] = j;
            }
            if (dfs(ans, i + 1)) {
                return true;
            }

            ans[i] = 0;  // this filling is invalid, backtrack and try the next number.
            if (j != 1) {
                ans[i + j] = 0;
            }
            used[j] = 0;
        }
        return false;
    }

public:
    vector<int> constructDistancedSequence(int n) {
        vector<int> ans(2 * n - 1);
        used.assign(n + 1, 0);  // numbers 1 ~ n are unused initially
        dfs(ans, 0);            // try filling numbers from index 0.
        return ans;
    }
};
