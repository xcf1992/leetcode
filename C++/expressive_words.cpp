/*
809. Expressive Words
 Sometimes people repeat letters to represent extra feeling,
 such as "hello" -> "heeellooo", "hi" -> "hiiii".
 Here, we have groups, of adjacent letters that are all the same character,
 and adjacent characters to the group are different.
 A group is extended if that group is length 3 or more,
 so "e" and "o" would be extended in the first example,
 and "i" would be extended in the second example.
  As another example, the groups of "abbcccaaaa" would be "a", "bb", "ccc", and "aaaa";
  and "ccc" and "aaaa" are the extended groups of that string.

 For some given string S, a query word is stretchy if it can be made to be equal to S by extending some groups.
 Formally, we are allowed to repeatedly choose a group (as defined above) of characters c,
 and add some number of the same character c to it so that the length of the group is 3 or more.
 Note that we cannot extend a group of size one like "h" to a group of size two like "hh"
 - all extensions must leave the group extended - ie., at least 3 characters long.

 Given a list of query words, return the number of words that are stretchy.

 Example:
 Input:
 S = "heeellooo"
 words = ["hello", "hi", "helo"]
 Output: 1
 Explanation:
 We can extend "e" and "o" in the word "hello" to get "heeellooo".
 We can't extend "helo" to get "heeellooo" because the group "ll" is not extended.
 Notes:

 0 <= len(S) <= 100.
 0 <= len(words) <= 100.
 0 <= len(words[i]) <= 100.
 S and all words in words consist only of lowercase letters
*/
#include <iostream>
#include <sstream>
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
    pair<string, vector<int>> parse(string str) {
        vector<int> count;
        string key = "";
        int prev = -1;
        int n = str.size();
        for (int i = 0; i < n; ++i) {
            if (i == n - 1 or str[i] != str[i + 1]) {
                key.push_back(str[i]);
                count.push_back(i - prev);
                prev = i;
            }
        }
        return {key, count};
    }

    bool check(pair<string, vector<int>>& s, pair<string, vector<int>>& word) {
        if (s.first != word.first) {
            return false;
        }

        vector<int> sCount = s.second;
        vector<int> wCount = word.second;
        for (int i = 0; i < sCount.size(); ++i) {
            if (sCount[i] < wCount[i] or (sCount[i] < 3 and sCount[i] != wCount[i])) {
                return false;
            }
        }
        return true;
    }
public:
    int expressiveWords(string S, vector<string>& words) {
        int n = words.size();
        if (n <= 0) {
            return 0;
        }

        pair<string, vector<int>> s = parse(S);
        int result = 0;
        for (int i = 0; i < n; ++i) {
            pair<string, vector<int>> w = parse(words[i]);
            if (check(s, w)) {
                result += 1;
            }
        }
        return result;
    }
};

class Solution1 {
private:
    bool check(string& word, string S) {
        int i = 0;
        int j = 0;
        int n = word.size();
        int m = S.size();
        while (i < n && j < m) {
            while (i < n && j < m && word[i] == S[j]) {
                i++;
                j++;
            }
            while (j > 0 && S[j] == S[j - 1]) {
                j++;
            }
            if (j < 3 || S[j - 1] != S[j - 2] || S[j - 2] != S[j - 3]) {
                break;
            }
        }
        return i == n && j == m;
    }
public:
    int expressiveWords(string S, vector<string>& words) {
        int result = 0;
        for (string& word : words) {
            result += check(word, S) ? 1 : 0;
        }
        return result;
    }
};
