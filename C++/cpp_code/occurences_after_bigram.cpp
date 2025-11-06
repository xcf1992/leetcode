/*
5083. Occurrences After Bigram
Given words first and second, consider occurrences in some text of the form "first second third",
where second comes immediately after first, and third comes immediately after second.

For each such occurrence, add "third" to the answer, and return the answer.

Example 1:

Input: text = "alice is a good girl she is a good student", first = "a", second = "good"
Output: ["girl","student"]
Example 2:

Input: text = "we will we will rock you", first = "we", second = "will"
Output: ["we","rock"]


Note:

1 <= text.length <= 1000
text consists of space separated words, where each word consists of lowercase English letters.
1 <= first.length, second.length <= 10
first and second consist of lowercase English letters.
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
    vector<string> splitText(string text) {
        vector<string> words;
        int cur = 0;
        size_t pos = text.find(' ');
        while (pos != string::npos) {
            words.push_back(text.substr(cur, pos - cur));
            cur = pos + 1;
            pos = text.find(' ', cur);
        }
        words.push_back(text.substr(cur));
        return words;
    }

public:
    vector<string> findOcurrences(string text, string first, string second) {
        vector<string> tokens = splitText(text);
        vector<string> result;
        for (int i = 2; i < tokens.size(); ++i) {
            if (tokens[i - 2] == first and tokens[i - 1] == second) {
                result.push_back(tokens[i]);
            }
        }
        return result;
    }
};