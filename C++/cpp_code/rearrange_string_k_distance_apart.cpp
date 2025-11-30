/*
358. Rearrange String k Distance Apart

Given a non-empty string s and an integer k,
rearrange the string such that the same characters are at least distance k from each other.

All input strings are given in lowercase letters.
If it is not possible to rearrange the string, return an empty string "".

Example 1:

Input: s = "aabbcc", k = 3
Output: "abcabc"
Explanation: The same letters are at least distance 3 from each other.
Example 2:

Input: s = "aaabc", k = 3
Output: ""
Explanation: It is not possible to rearrange the string.
Example 3:

Input: s = "aaadbbcc", k = 2
Output: "abacabcd"
Explanation: The same letters are at least distance 2 from each other.
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
#include <numeric>
using namespace std;
/*
we should not arrange the most frequent letter with k distance to solve this problem
for example "aaabbbccc" with k = 2
it will become abababccc using above algorithm

instead we should arrange a group of k letters time by time,
in each group we always try to put the most frequent letter first
and try to make we only use each letter once in each group
*/
struct mycompare {
    bool operator()(pair<int, char>& a, pair<int, char>& b) {
        return a.first < b.first or (a.first == b.first and a.second < b.second);
    }
};

class Solution {
public:
    string rearrangeString(string s, int k) {
        if (k == 0) {
            return s;
        }

        unordered_map<char, int> dict;
        for (char c : s) {
            dict[c] += 1;
        }

        priority_queue<pair<int, char>, vector<pair<int, char>>, mycompare> pq;
        for (auto it = dict.begin(); it != dict.end(); ++it) {
            pq.push({it->second, it->first});
        }

        int n = s.size();
        string result = "";
        while (!pq.empty()) {
            vector<pair<int, int>> cache;  // store used char during one while loop
            int count = min(k, n);
            for (int i = 0; i < count; ++i) {
                if (pq.empty()) {
                    return "";
                }
                pair<int, char> cur = pq.top();
                pq.pop();

                result.push_back(cur.second);
                cur.first -= 1;
                if (cur.first > 0) {
                    cache.push_back(cur);
                }
                n -= 1;
            }
            for (auto p : cache) {
                pq.push(p);
            }
        }
        return result;
    }
};