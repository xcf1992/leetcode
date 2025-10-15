/*
692. Top K Frequent Words
https://leetcode.com/problems/top-k-frequent-words/

Given a non-empty list of words, return the k most frequent elements.
Your answer should be sorted by frequency from highest to lowest.
If two words have the same frequency, then the word with the lower alphabetical order comes first.

Example 1:
Input: ["i", "love", "leetcode", "i", "love", "coding"], k = 2
Output: ["i", "love"]
Explanation: "i" and "love" are the two most frequent words.
    Note that "i" comes before "love" due to a lower alphabetical order.

Example 2:
Input: ["the", "day", "is", "sunny", "the", "the", "the", "sunny", "is", "is"], k = 4
Output: ["the", "is", "sunny", "day"]
Explanation: "the", "is", "sunny" and "day" are the four most frequent words,
    with the number of occurrence being 4, 3, 2 and 1 respectively.

Note:
You may assume k is always valid, 1 ≤ k ≤ number of unique elements.
Input words contain only lowercase letters.

Follow up:
Try to solve it in O(n log k) time and O(n) extra space.
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

struct Comp {
    bool operator()(const pair<string, int>& a, const pair<string, int>& b) {
        return b.second > a.second || (a.second == b.second && b.first < a.first);
    }
};

class Solution {
public:
    vector<string> topKFrequent(vector<string>& words, int k) {
        unordered_map<string, int> frequency;
        for (string word : words) {
            frequency[word] += 1;
        }

        priority_queue<pair<string, int>, vector<pair<string, int>>, Comp> sortWords;
        for (const auto& freq : frequency) {
            sortWords.push(freq);
        }

        vector<string> result;
        while (result.size() < k and !sortWords.empty()) {
            result.push_back(sortWords.top().first);
            sortWords.pop();
        }
        return result;
    }
};
