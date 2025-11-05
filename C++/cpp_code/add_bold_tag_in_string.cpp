/*
616. Add Bold Tag in String
https://leetcode.com/problems/add-bold-tag-in-string/

Given a string s and a list of strings dict,
you need to add a closed pair of bold tag <b> and </b>
to wrap the substrings in s that exist in dict.
If two such substrings overlap,
you need to wrap them together by only one pair of closed bold tag.
Also, if two substrings wrapped by bold tags are consecutive, you need to combine them.

Example 1:
Input:
s = "abcxyz123"
dict = ["abc","123"]
Output:
"<b>abc</b>xyz<b>123</b>"

Example 2:
Input:
s = "aaabbcc"
dict = ["aaa","aab","bc"]
Output:
"<b>aaabbc</b>c"

Note:
The given dict won't contain duplicates, and its length won't exceed 100.
All the strings in input have length in range [1, 1000].
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
#include <set>
using namespace std;

class Solution {
public:
    string addBoldTag(string s, vector<string> &dict) {
        if (s.empty() or
        dict.empty()
        )
        {
            return s;
        }

        vector<pair<int, int> > pos;
        for (string word: dict) {
            for (int i = 0; (i = s.find(word, i)) != string::npos; i++) {
                pos.push_back(make_pair(i, i + word.size()));
            }
        }

        sort(pos.begin(), pos.end(), [](pair<int, int> &a, pair<int, int> &b) {
            return a.first < b.first
            or(a.first == b.first and a.second < b.second);
        });

        vector<pair<int, int> > merge;
        for (int i = 0, j = -1; i < pos.size(); i++) {
            if (j < 0 or pos[i]
            .
            first > merge[j].second
            )
            {
                merge.push_back(pos[i]);
                j += 1;
            }
            else
            {
                merge[j].second = max(merge[j].second, pos[i].second);
            }
        }

        for (int i = merge.size() - 1; i >= 0; i--) {
            s.insert(merge[i].second, "</b>");
            s.insert(merge[i].first, "<b>");
        }
        return s;
    }
};