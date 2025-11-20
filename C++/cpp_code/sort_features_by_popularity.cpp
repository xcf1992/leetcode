/*
https://leetcode.com/problems/sort-features-by-popularity/description/
1772. Sort Features by Popularity

You are given a string array features where features[i] is a single word that represents the name of a feature of the
latest product you are working on. You have made a survey where users have reported which features they like. You are
given a string array responses, where each responses[i] is a string containing space-separated words.

The popularity of a feature is the number of responses[i] that contain the feature. You want to sort the features in
non-increasing order by their popularity. If two features have the same popularity, order them by their original index
in features. Notice that one response could contain the same feature multiple times; this feature is only counted once
in its popularity.

Return the features in sorted order.



Example 1:

Input: features = ["cooler","lock","touch"], responses = ["i like cooler cooler","lock touch cool","locker like touch"]
Output: ["touch","cooler","lock"]
Explanation: appearances("cooler") = 1, appearances("lock") = 1, appearances("touch") = 2. Since "cooler" and "lock"
both had 1 appearance, "cooler" comes first because "cooler" came first in the features array. Example 2:

Input: features = ["a","aa","b","c"], responses = ["a","a aa","a a a a a","b a"]
Output: ["a","aa","b","c"]


Constraints:

1 <= features.length <= 104
1 <= features[i].length <= 10
features contains no duplicates.
features[i] consists of lowercase letters.
1 <= responses.length <= 102
1 <= responses[i].length <= 103
responses[i] consists of lowercase letters and spaces.
responses[i] contains no two consecutive spaces.
responses[i] has no leading or trailing spaces.
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
    void calc_freq(unordered_map<string, pair<int, int>>& freq, string& response) {
        unordered_set<string> words;
        // split response
        int start = 0;
        int n = response.size();
        while (start < n) {
            int end = start;
            while (end < n && response[end] != ' ') {
                end += 1;
            }

            string word = response.substr(start, end - start);
            words.insert(word);

            start = end + 1;
        }

        for (const string& word : words) {
            if (freq.find(word) == freq.end()) {
                continue;
            }

            freq[word].second += 1;
        }
    }
public:
    vector<string> sortFeatures(vector<string>& features, vector<string>& responses) {
        int n = features.size();
        unordered_map<string, pair<int, int>> freq; // feature -> (idx, cnt)
        for (int i = 0; i < n; i++) {
            freq[features[i]] = make_pair(i, 0);
        }

        for (string& response : responses) {
            calc_freq(freq, response);
        }

        sort(features.begin(), features.end(), [&freq](const string& a, const string& b) {
            return freq[a].second > freq[b].second || (freq[a].second == freq[b].second && freq[a].first < freq[b].first);
        });
        return features;
    }
};
