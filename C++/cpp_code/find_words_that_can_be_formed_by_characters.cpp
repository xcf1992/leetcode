/*
1160. Find Words That Can Be Formed by Characters
You are given an array of strings words and a string chars.

A string is good if it can be formed by characters from chars (each character can only be used once).

Return the sum of lengths of all good strings in words.



Example 1:

Input: words = ["cat","bt","hat","tree"], chars = "atach"
Output: 6
Explanation:
The strings that can be formed are "cat" and "hat" so the answer is 3 + 3 = 6.
Example 2:

Input: words = ["hello","world","leetcode"], chars = "welldonehoneyr"
Output: 10
Explanation:
The strings that can be formed are "hello" and "world" so the answer is 5 + 5 = 10.


Note:

1 <= words.length <= 1000
1 <= words[i].length, chars.length <= 100
All strings contain lowercase English letters only.
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
using namespace std;

class Solution {
private:
    bool isGood(string& word, vector<int> count) {
        for (char c : word) {
            if (count[c - 'a'] <= 0) {
                return false;
            }
            count[c - 'a'] -= 1;
        }
        return true;
    }

public:
    int countCharacters(vector<string>& words, string chars) {
        vector<int> count(26, 0);
        for (char c : chars) {
            count[c - 'a'] += 1;
        }
        int result = 0;
        for (string& word : words)
            if (isGood(word, count)) {
                result += word.size();
            }
        return result;
    }
};
