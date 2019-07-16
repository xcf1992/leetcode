/*
763. Partition Labels
A string S of lowercase letters is given.
We want to partition this string into as many parts as possible
so that each letter appears in at most one part,
and return a list of integers representing the size of these parts.

Example 1:
Input: S = "ababcbacadefegdehijhklij"
Output: [9,7,8]
Explanation:
The partition is "ababcbaca", "defegde", "hijhklij".
This is a partition so that each letter appears in at most one part.
A partition like "ababcbacadefegde", "hijhklij" is incorrect, because it splits S into less parts.
Note:

S will have length in range [1, 500].
S will consist of lowercase letters ('a' to 'z') only.
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
using namespace std;

class Solution {
public:
    vector<int> partitionLabels(string S) {
        vector<int> result;
        int sum = 0;
        vector<int> labels(26, -1);
        for (int i = 0; i < S.size(); i++) {
            char c = S[i];
            if (labels[c - 'a'] == -1) {
                labels[c - 'a'] = i;
                result.push_back(1);
                sum += 1;
            }
            else {
                int pos = labels[c - 'a'];
                int cur = i;
                while (cur > pos) {
                    cur -= result.back();
                    sum -= result.back();
                    result.pop_back();
                }
                result.push_back(i - sum + 1);
                sum += result.back();
                labels[c - 'a'] = i;
            }
        }
        return result;
    }
};

class Solution1 {
private:
    vector<pair<int, int>> merge(vector<pair<int, int>>& intervals) {
        if (intervals.empty()) {
            return {};
        }

        vector<pair<int, int>> result;
        for (int i = 0; i < intervals.size(); i++) {
            if (!result.empty() and result.back().second > intervals[i].first) {
                result.back().second = max(result.back().second, intervals[i].second);
            }
            else {
                result.push_back(intervals[i]);
            }
        }
        return result;
    }
public:
    vector<int> partitionLabels(string S) {
        vector<vector<int>> letter(26);
        int index = 0;
        for (char c : S) {
            letter[c - 'a'].push_back(index);
            index += 1;
        }

        vector<pair<int, int>> intervals;
        for (vector<int>& l : letter) {
            if (!l.empty()) {
                intervals.push_back({l.front(), l.back()});
            }
        }

        sort(intervals.begin(), intervals.end(), [](pair<int, int>& a, pair<int, int>& b) {
            return a.first < b.first or (a.first == b.first and a.second < b.second);
        });
        vector<pair<int, int>> partitions = merge(intervals);

        vector<int> result;
        for (pair<int, int>& p : partitions) {
            result.push_back(p.second - p.first + 1);
        }
        return result;
    }
};