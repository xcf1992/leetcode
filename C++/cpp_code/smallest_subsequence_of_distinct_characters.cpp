/*
 1081. Smallest Subsequence of Distinct Characters
 Return the lexicographically smallest subsequence of text that contains all the distinct characters of text exactly
 once.

 Example 1:

 Input: "cdadabcc"
 Output: "adbc"
 Example 2:

 Input: "abcd"
 Output: "abcd"
 Example 3:

 Input: "ecbacba"
 Output: "eacb"
 Example 4:

 Input: "leetcode"
 Output: "letcod"


 Note:

 1 <= text.length <= 1000
 text consists of lowercase English letters.
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
#include <map>
#include <set>
#include <numeric>
using namespace std;

class Solution {
public:
    string smallestSubsequence(string text) {
        vector<int> count(26, 0);
        for (char c : text) {
            count[c - 'a'] += 1;
        }

        string result = "";
        vector<bool> used(26, false);
        for (char c : text) {
            count[c - 'a'] -= 1;
            if (used[c - 'a']) {
                continue;
            }
            while (!result.empty() and c < result.back() and count[result.back() - 'a'] > 0) {
                used[result.back() - 'a'] = false;
                result.pop_back();
            }
            result.push_back(c);
            used[c - 'a'] = true;
        }
        return result;
    }
};
