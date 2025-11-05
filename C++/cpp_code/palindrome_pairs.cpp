/*
336. Palindrome Pairs
https://leetcode.com/problems/palindrome-pairs/

Given a list of unique words,
find all pairs of distinct indices (i, j) in the given list,
so that the concatenation of the two words,
i.e. words[i] + words[j] is a palindrome.

Example 1:
Input: ["abcd","dcba","lls","s","sssll"]
Output: [[0,1],[1,0],[3,2],[2,4]]
Explanation: The palindromes are ["dcbaabcd","abcddcba","slls","llssssll"]

Example 2:
Input: ["bat","tab","cat"]
Output: [[0,1],[1,0]]
Explanation: The palindromes are ["battab","tabbat"]
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
#include <stdio.h>
#include <set>
#include <numeric>
using namespace std;
/*
Traverse the array, build map. Key is the reversed string, value is index in array (0 based)

Edge case - check if empty string exists.
It's interesting that for given words {"a", ""},
it's expected to return two results [0,1] and [1,0].
Since my main logic can cover [0, 1] concatenate("a", ""),
so as to cover the other situation concatenate("", "a"),
I need to traverse the words array again,
find the palindrome word candidate except "" itself, and add pair("", palindrome word) to the final answer.

Main logic part. Partition the word into left and right, and see
1) if there exists a candidate in map equals the left side of current word,
and right side of current word is palindrome, so concatenate(current word, candidate) forms a pair: left | right | candidate.
2) same for checking the right side of current word: candidate | left | right.
*/
class Solution {
private:
    bool isPalindrome(string word) {
        if (word.size() <= 1) {
            return true;
        }

        int left = 0;
        int right = word.size() - 1;
        while (left < right) {
            if (word[left++] != word[right--]) {
                return false;
            }
        }
        return true;
    }

public:
    vector<vector<int> > palindromePairs(vector<string> &words) {
        unordered_map<string, int> dict;
        for (int i = 0; i < words.size(); i++) {
            string key = words[i];
            reverse(key.begin(), key.end());
            dict[key] = i;
        }

        vector<vector<int> > result;
        for (int i = 0; i < words.size(); i++) {
            for (int j = 0; j < words[i].size(); j++) {
                string left = words[i].substr(0, j);
                string right = words[i].substr(j);
                if (dict.find(left) != dict.end() and isPalindrome(right) and dict[left]
                !=
                i
                )
                {
                    result.push_back({i, dict[left]});
                    if (left == "") {
                        result.push_back({dict[left], i});
                    }
                }
                if (dict.find(right) != dict.end() and isPalindrome(left) and dict[right]
                !=
                i
                )
                {
                    result.push_back({dict[right], i});
                }
            }
        }
        return result;
    }
};

// time limit exceed
class Solution1 {
private:
    bool isPalindrome(string word) {
        if (word.size() <= 1) {
            return true;
        }

        int left = 0;
        int right = word.size() - 1;
        while (left < right) {
            if (word[left] != word[right]) {
                return false;
            }
            left += 1;
            right -= 1;
        }
        return true;
    }

public:
    vector<vector<int> > palindromePairs(vector<string> &words) {
        vector<vector<int> > result;
        for (int i = 0; i < words.size(); i++) {
            for (int j = i + 1; j < words.size(); j++) {
                if (isPalindrome(words[i] + words[j])) {
                    result.push_back({i, j});
                }
                if (isPalindrome(words[j] + words[i])) {
                    result.push_back({j, i});
                }
            }
        }
        return result;
    }
};