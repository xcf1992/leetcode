/*
https://leetcode.com/problems/check-if-the-sentence-is-pangram/description/
1832. Check if the Sentence Is Pangram

A pangram is a sentence where every letter of the English alphabet appears at least once.

Given a string sentence containing only lowercase English letters, return true if sentence is a pangram, or false
otherwise.



Example 1:

Input: sentence = "thequickbrownfoxjumpsoverthelazydog"
Output: true
Explanation: sentence contains at least one of every letter of the English alphabet.
Example 2:

Input: sentence = "leetcode"
Output: false


Constraints:

1 <= sentence.length <= 1000
sentence consists of lowercase English letters.
*/
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <map>
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
    bool checkIfPangram(string sentence) {
        vector<int> freq(26, 0);
        int left = 26;
        for (char c : sentence) {
            freq[c - 'a']++;
            if (freq[c - 'a'] == 1) {
                left -= 1;
            }
            if (left <= 0) {
                return true;
            }
        }
        return false;
    }
};
