/*
1023. Camelcase Matching
https://leetcode.com/problems/camelcase-matching/

A query word matches a given pattern
if we can insert lowercase letters to the pattern word so that it equals the query.
(We may insert each character at any position, and may insert 0 characters.)

Given a list of queries, and a pattern,
return an answer list of booleans,
where answer[i] is true if and only if queries[i] matches the pattern.

Example 1:
Input: queries = ["FooBar","FooBarTest","FootBall","FrameBuffer","ForceFeedBack"], pattern = "FB"
Output: [true,false,true,true,false]
Explanation:
"FooBar" can be generated like this "F" + "oo" + "B" + "ar".
"FootBall" can be generated like this "F" + "oot" + "B" + "all".
"FrameBuffer" can be generated like this "F" + "rame" + "B" + "uffer".

Example 2:
Input: queries = ["FooBar","FooBarTest","FootBall","FrameBuffer","ForceFeedBack"], pattern = "FoBa"
Output: [true,false,true,false,false]
Explanation:
"FooBar" can be generated like this "Fo" + "o" + "Ba" + "r".
"FootBall" can be generated like this "Fo" + "ot" + "Ba" + "ll".

Example 3:
Input: queries = ["FooBar","FooBarTest","FootBall","FrameBuffer","ForceFeedBack"], pattern = "FoBaT"
Output: [false,true,false,false,false]
Explanation:
"FooBarTest" can be generated like this "Fo" + "o" + "Ba" + "r" + "T" + "est".

Note:
1 <= queries.length <= 100
1 <= queries[i].length <= 100
1 <= pattern.length <= 100
All strings consists only of lower and upper case English letters.
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

class Solution {
private:
    bool check(string &query, string &pattern) {
        int cur = 0;
        for (int i = 0; i < query.size(); i++) {
            if (cur < pattern.size() and query[i]
            ==
            pattern[cur]
            )
            {
                cur += 1;
                continue;
            }

            if (query[i] >= 'A' and query[i]
            <=
            'Z'
            )
            {
                return false;
            }
        }
        return cur == pattern.size();
    }

public:
    vector<bool> camelMatch(vector<string> &queries, string pattern) {
        vector<bool> result;
        for (string &query: queries) {
            result.push_back(check(query, pattern));
        }
        return result;
    }
};