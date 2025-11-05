/*
1181. Before and After Puzzle
https://leetcode.com/problems/before-and-after-puzzle/

Given a list of phrases, generate a list of Before and After puzzles.

A phrase is a string that consists of lowercase English letters and spaces only.
No space appears in the start or the end of a phrase.
There are no consecutive spaces in a phrase.

Before and After puzzles are phrases that are formed by merging two phrases
where the last word of the first phrase is the same as the first word of the second phrase.

Return the Before and After puzzles that can be formed by every two phrases phrases[i] and phrases[j] where i != j.
Note that the order of matching two phrases matters, we want to consider both orders.

You should return a list of distinct strings sorted lexicographically.

Example 1:
Input: phrases = ["writing code","code rocks"]
Output: ["writing code rocks"]

Example 2:
Input: phrases = ["mission statement",
                  "a quick bite to eat",
                  "a chip off the old block",
                  "chocolate bar",
                  "mission impossible",
                  "a man on a mission",
                  "block party",
                  "eat my words",
                  "bar of soap"]
Output: ["a chip off the old block party",
         "a man on a mission impossible",
         "a man on a mission statement",
         "a quick bite to eat my words",
         "chocolate bar of soap"]

Example 3:
Input: phrases = ["a","b","a"]
Output: ["a"]

Constraints:

1 <= phrases.length <= 100
1 <= phrases[i].length <= 100
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
    void parse(int index, string &phrase, unordered_map<string, vector<pair<int, string> > > &beginWtih,
               unordered_map<string, vector<pair<int, string> > > &endWtih) {
        int n = phrase.size();
        int left = 0;
        string first = "";
        for (; left < n; ++left) {
            if (phrase[left] == ' ') {
                break;
            }
            first.push_back(phrase[left]);
        }
        if (left < n) {
            left += 1;
        }
        beginWtih[first].push_back({index, phrase.substr(left)});

        int right = n - 1;
        string last = "";
        for (; right >= 0; --right) {
            if (phrase[right] == ' ') {
                break;
            }
            last.push_back(phrase[right]);
        }
        reverse(last.begin(), last.end());
        if (right < 0) {
            right += 1;
        }
        endWtih[last].push_back({index, phrase.substr(0, right)});
    }

public:
    vector<string> beforeAndAfterPuzzles(vector<string> &phrases) {
        unordered_map<string, vector<pair<int, string> > > beginWtih;
        unordered_map<string, vector<pair<int, string> > > endWith;
        for (int i = 0; i < phrases.size(); ++i) {
            parse(i, phrases[i], beginWtih, endWith);
        }

        set<string> result;
        for (auto &eIt: endWith) {
            string last = eIt.first;
            if (beginWtih.find(last) == beginWtih.end()) {
                continue;
            }

            vector<pair<int, string> > &endPhrases = eIt.second;
            vector<pair<int, string> > &beginPhrases = beginWtih[last];
            for (int i = 0; i < endPhrases.size(); ++i) {
                for (int j = 0; j < beginPhrases.size(); ++j) {
                    if (endPhrases[i].first == beginPhrases[j].first) {
                        continue;
                    }

                    string part1 = endPhrases[i].second;
                    if (part1 != "") {
                        part1.push_back(' ');
                    }
                    string part2 = beginPhrases[j].second == "" ? beginPhrases[j].second : " " + beginPhrases[j].second;
                    result.insert(part1 + last + part2);
                }
            }
        }
        return vector<string>(result.begin(), result.end());
    }
};