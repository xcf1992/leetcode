/*
1415. The k-th Lexicographical String of All Happy Strings of Length n
https://leetcode.com/problems/the-k-th-lexicographical-string-of-all-happy-strings-of-length-n/

A happy string is a string that:
consists only of letters of the set ['a', 'b', 'c'].
s[i] != s[i + 1] for all values of i from 1 to s.length - 1 (string is 1-indexed).
For example, strings "abc", "ac", "b" and "abcbabcbcb"
are all happy strings and strings "aa", "baa" and "ababbc" are not happy strings.

Given two integers n and k, consider a list of all happy strings of length n sorted in lexicographical order.
Return the kth string of this list or return an empty string if there are less than k happy strings of length n.

Example 1:
Input: n = 1, k = 3
Output: "c"
Explanation: The list ["a", "b", "c"] contains all happy strings of length 1. The third string is "c".

Example 2:
Input: n = 1, k = 4
Output: ""
Explanation: There are only 3 happy strings of length 1.

Example 3:
Input: n = 3, k = 9
Output: "cab"
Explanation: There are 12 different happy string of length 3 ["aba", "abc", "aca", "acb", "bab", "bac", "bca", "bcb",
"cab", "cac", "cba", "cbc"]. You will find the 9th string = "cab"

Example 4:
Input: n = 2, k = 7
Output: ""

Example 5:
Input: n = 10, k = 100
Output: "abacbabacb"

Constraints:
1 <= n <= 10
1 <= k <= 100
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

class Solution {
public:
    string getHappyString(int n, int k) {
        if (k > 3 * pow(2, n - 1)) {
            return "";
        }

        queue<string> bfs;
        bfs.push("a");
        bfs.push("b");
        bfs.push("c");
        string result = "";
        for (int i = 1; i <= n; ++i) {
            int curSize = bfs.size();
            for (int j = 0; j < curSize; ++j) {
                string cur = bfs.front();
                bfs.pop();

                if (i == n and j == k - 1) {
                    result = cur;
                    break;
                }

                for (int c = 'a'; c <= 'c'; ++c)
                    if (c != cur.back()) {
                        string temp = cur;
                        temp.push_back(c);
                        bfs.push(temp);
                    }
            }
        }
        return result;
    }
};
