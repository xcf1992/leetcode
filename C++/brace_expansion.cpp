/*
1087. Brace Expansion
A string S represents a list of words.

Each letter in the word has 1 or more options.  If there is one option, the letter is represented as is.  If there is more than one option, then curly braces delimit the options.  For example, "{a,b,c}" represents options ["a", "b", "c"].

For example, "{a,b,c}d{e,f}" represents the list ["ade", "adf", "bde", "bdf", "cde", "cdf"].

Return all words that can be formed in this manner, in lexicographical order.

 

Example 1:

Input: "{a,b}c{d,e}f"
Output: ["acdf","acef","bcdf","bcef"]
Example 2:

Input: "abcd"
Output: ["abcd"]
 

Note:

1 <= S.length <= 50
There are no nested curly brackets.
All characters inside a pair of consecutive opening and ending curly brackets are different.
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
#include <set>
#include <numeric>
using namespace std;

class Solution {
private:
    void dfs(vector<set<char>>& groups, int index, vector<string>& result, string cur) {
        if (index == groups.size()) {
            result.push_back(cur);
            return;
        }

        for (char c : groups[index]) {
            cur.push_back(c);
            dfs(groups, index + 1, result, cur);
            cur.pop_back();
        }
    }
public:
    vector<string> expand(string S) {
        int n = S.size();
        vector<set<char>> groups;
        for (int i = 0; i < n; ++i) {
            set<char> cur;
            if (S[i] == '{') {
                while (i < n and S[i] != '}') {
                    if (isalpha(S[i])) {
                        cur.insert(S[i]);
                    }
                    i += 1;
                }
            }
            else {
                cur.insert(S[i]);
            }
            groups.push_back(cur);
        }

        vector<string> result;
        dfs(groups, 0, result, "");
        return result;
    }
};
