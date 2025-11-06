/*
 1065. Index Pairs of a String
 Given a text string and words (a list of strings),
 return all index pairs [i, j] so that the substring text[i]...text[j] is in the list of words.

 Example 1:

 Input: text = "thestoryofleetcodeandme", words = ["story","fleet","leetcode"]
 Output: [[3,7],[9,13],[10,17]]
 Example 2:

 Input: text = "ababa", words = ["aba","ab"]
 Output: [[0,1],[0,2],[2,3],[2,4]]
 Explanation:
 Notice that matches can overlap, see "aba" is found in [0,2] and [2,4].


 Note:

 All strings contains only lowercase English letters.
 It's guaranteed that all strings in words are different.
 1 <= text.length <= 100
 1 <= words.length <= 20
 1 <= words[i].length <= 50
 Return the pairs [i,j] in sorted order (i.e. sort them by their first coordinate in case of ties sort them by their
 second coordinate).
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
public:
    vector<vector<int>> indexPairs(string text, vector<string>& words) {
        vector<vector<int>> result;
        for (string& word : words) {
            int cur = 0;
            int len = word.size() - 1;
            int pos = text.find(word, cur);
            while (pos != string::npos) {
                result.push_back({pos, pos + len});
                pos = text.find(word, pos + 1);
            }
        }
        sort(result.begin(), result.end(),
             [](vector<int>& a, vector<int>& b) { return a[0] < b[0] or (a[0] == b[0] and a[1] < b[1]); });
        return result;
    }
};