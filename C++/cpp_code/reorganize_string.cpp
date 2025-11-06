/*
767. Reorganize String
https://leetcode.com/problems/reorganize-string/

Given a string S, check if the letters can be rearranged
so that two characters that are adjacent to each other are not the same.

If possible, output any possible result.
If not possible, return the empty string.

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

struct myComp {
    bool operator()(pair<char, int>& a, pair<char, int>& b) {
        return a.second < b.second or (a.second == b.second and a.first < b.first);
    }
};

class Solution {
public:
    string reorganizeString(string S) {
        int n = S.size();
        if (n <= 1) {
            return S;
        }

        vector<int> letter(26, 0);
        for (char c : S) {
            letter[c - 'a'] += 1;
        }

        priority_queue<pair<char, int>, vector<pair<char, int>>, myComp> pq;
        for (int i = 0; i < 26; ++i)
            if (letter[i]) {
                if (letter[i] * 2 > n + 1) {
                    return "";
                }
                pq.push({'a' + i, letter[i]});
            }

        string result = "";
        while (pq.size() >= 2) {
            pair<char, int> l1 = pq.top();
            pq.pop();
            pair<char, int> l2 = pq.top();
            pq.pop();

            result.push_back(l1.first);
            l1.second -= 1;
            result.push_back(l2.first);
            l2.second -= 1;
            if (l1.second > 0) {
                pq.push(l1);
            }
            if (l2.second > 0) {
                pq.push(l2);
            }
        }
        if (pq.size() > 0) {
            result.push_back(pq.top().first);
        }
        return result;
    }
};