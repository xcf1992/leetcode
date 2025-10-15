/*
1170. Compare Strings by Frequency of the Smallest Character

Let's define a function f(s) over a non-empty string s,
which calculates the frequency of the smallest character in s.
For example, if s = "dcce" then f(s) = 2 because the smallest character is "c" and its frequency is 2.

Now, given string arrays queries and words, return an integer array answer,
where each answer[i] is the number of words such that f(queries[i]) < f(W),
where W is a word in words.

Example 1:
Input: queries = ["cbd"], words = ["zaaaz"]
Output: [1]
Explanation: On the first query we have f("cbd") = 1, f("zaaaz") = 3 so f("cbd") < f("zaaaz").

Example 2:
Input: queries = ["bbb","cc"], words = ["a","aa","aaa","aaaa"]
Output: [1,2]
Explanation: On the first query only f("bbb") < f("aaaa"). On the second query both f("aaa") and f("aaaa") are both > f("cc").

Constraints:
1 <= queries.length <= 2000
1 <= words.length <= 2000
1 <= queries[i].length, words[i].length <= 10
queries[i][j], words[i][j] are English lowercase letters.
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
using namespace std;

class Solution {
private:
    int getFrequency(string str) {
        vector<int> letter(26, 0);
        for (char c: str) {
            letter[c - 'a'] += 1;
        }

        int result = 0;
        for (int i = 0; i < 26; ++i) if (letter[i] != 0) {
            result = letter[i];
            break;
        }
        return result;
    }
public:
    vector<int> numSmallerByFrequency(vector<string>& queries, vector<string>& words) {
        vector<int> frequency(2001, 0);
        for (string& word : words) {
            frequency[getFrequency(word)] += 1;
        }

        for (int i = 1999; i >= 0; --i) {
            frequency[i] += frequency[i + 1];
        }

        int n = queries.size();
        vector<int> result(n, 0);
        for (int i = 0; i < n; ++i) {
            int freq = getFrequency(queries[i]);
            if (freq >= 2000) {
                result[i] = 0;
            }
            else {
                result[i] = frequency[freq + 1];
            }
        }
        return result;
    }
};
