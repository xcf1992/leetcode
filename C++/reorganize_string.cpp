/*
 Given a string S, check if the letters can be rearranged so that two characters that are adjacent to each other are not the same.
 
 If possible, output any possible result.  If not possible, return the empty string.
 
 Example 1:
 
 Input: S = "aab"
 Output: "aba"
 Example 2:
 
 Input: S = "aaab"
 Output: ""
 Note:
 
 S will consist of lowercase letters and have length in range [1, 500].
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
    string reorganize(string str) {
        int n = str.size();
        string result = "";
        
        int start = 0;
        int mid = (n - 1) / 2 + 1;
        while (start <= (n - 1) / 2) {
            result.push_back(str[start]);
            if (mid < n) {
                result.push_back(str[mid]);
            }
            start += 1;
            mid += 1;
        }
        return result;
    }
public:
    string reorganizeString(string S) {
        int n = S.size();
        vector<int> letter(26);
        for (char c: S) {
            letter[c - 'a'] += 1;
        }
        
        vector<pair<char, int>> charCounts;
        for (int i = 0; i < 26; i++) {
            if (letter[i] * 2 - 1 > n) {
                return "";
            }
            if (letter[i] > 0) {
                charCounts.push_back(make_pair(i + 'a', letter[i]));
            }
        }
        
        sort(charCounts.begin(), charCounts.end(), [](pair<char, int>& p1, pair<char, int>& p2) {
            return p1.second < p2.second;
        });
        string strSorted = "";
        for (int i = charCounts.size() - 1; i >= 0; i--) {
            strSorted += string(charCounts[i].second, charCounts[i].first);
        }
        return reorganize(strSorted);
        return reorganize(strSorted);
    }
};
