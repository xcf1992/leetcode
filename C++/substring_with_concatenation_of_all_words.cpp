/*
30. Substring with Concatenation of All Words
You are given a string, s, and a list of words, words,
that are all of the same length.
Find all starting indices of substring(s) in s
that is a concatenation of each word in words exactly once and without any intervening characters.

Example 1:

Input:
  s = "barfoothefoobarman",
  words = ["foo","bar"]
Output: [0,9]
Explanation: Substrings starting at index 0 and 9 are "barfoor" and "foobar" respectively.
The output order does not matter, returning [9,0] is fine too.
Example 2:

Input:
  s = "wordgoodgoodgoodbestword",
  words = ["word","good","best","word"]
Output: []
*/
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

/*
https://leetcode.wang/leetCode-30-Substring-with-Concatenation-of-All-Words.html

I think the following code is self-explanatory enough.
We use an unordered_map<string, int> counts to record the expected times of each word
and another unordered_map<string, int> seen to record the times we have seen.

Then we check for every possible position of i.
Once we meet an unexpected word or the times of some word is larger than its expected times,
we stop the check. If we finish the check successfully, push i to the result indexes.
*/
class Solution {
public:
    vector<int> findSubstring(string s, vector<string>& words) {
        int n = s.size();
        int k = words.size();
        if (n == 0 or k == 0) {
            return {};
        }
        
        unordered_map<string, int> count;
        for (string& word : words) {
            count[word] += 1;
        }

        vector<int> result;
        int len = words[0].size();
        for (int i = 0; i <= n - k * len; ++i) {
            unordered_map<string, int> find;
            int j = 0; // j is number of words we have found so far in current substring
            while (j < k) {
                string cur = s.substr(i + j * len, len);
                if (count.find(cur) != count.end()) {
                    find[cur] += 1;
                    if (find[cur] > count[cur]) {
                        break;
                    }
                }
                else {
                    break;
                }
                j += 1;
            }
            if (j == k) {
                result.push_back(i);
            }
        }
        return result;
    }
};
