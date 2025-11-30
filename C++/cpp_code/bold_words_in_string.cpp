/*
758. Bold Words in String
Given a set of keywords words and a string S,
make all appearances of all keywords in S bold.
Any letters between <b> and </b> tags become bold.

The returned string should use the least number of tags possible,
and of course the tags should form a valid combination.

For example, given that words = ["ab", "bc"] and S = "aabcd",
we should return "a<b>abc</b>d". Note that returning "a<b>a<b>b</b>c</b>d" would use more tags, so it is incorrect.

Note:

words has length in range [0, 50].
words[i] has length in range [1, 10].
S has length in range [0, 500].
All characters in words[i] and S are lowercase letters.
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
#include <climits>
#include <set>
using namespace std;

class Solution {
public:
    string boldWords(vector<string>& words, string S) {
        int n = S.size();
        vector<bool> marked(n, false);
        for (string& word : words) {
            string temp = S;
            size_t pos = temp.find(word);
            while (pos != string::npos) {
                for (int j = 0; j < word.size(); ++j) {
                    marked[pos + j] = true;
                }
                pos = temp.find(word, pos + 1);
                // we should not use substr, cause it it will change returned pos relative to pos in origin S
            }
        }

        string result = "";
        for (int i = 0; i < S.size(); i++) {
            if (marked[i] and (i == 0 or !marked[i - 1])) {
                result += "<b>";
            }
            result.push_back(S[i]);
            if (marked[i] and (i == S.size() - 1 or !marked[i + 1])) {
                result += "</b>";
            }
        }
        return result;
    }
};