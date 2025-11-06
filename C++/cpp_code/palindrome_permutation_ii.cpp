/*
267. Palindrome Permutation II
https://leetcode.com/problems/palindrome-permutation-ii/

Given a string s,
return all the palindromic permutations (without duplicates) of it.
Return an empty list if no palindromic permutation could be form.

Example 1:
Input: "aabb"
Output: ["abba", "baab"]

Example 2:
Input: "abc"
Output: []
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

class Solution {
private:
    void generate(int length, string cur, map<string, int>& letter, vector<string>& result) {
        if (cur.size() == length) {
            result.push_back(cur);
        }

        for (auto& it : letter) {
            if (it.second > 0) {
                it.second -= 2;
                generate(length, it.first + cur + it.first, letter, result);
                it.second += 2;
            }
        }
    }

public:
    vector<string> generatePalindromes(string s) {
        map<string, int> letter;
        for (char c : s) {
            letter[string(1, c)] += 1;
        }

        string odd = "";
        for (auto& it : letter) {
            if (it.second % 2 == 1) {
                if (odd.empty()) {
                    odd += it.first;
                } else {
                    return {};
                }
            }
        }
        letter[odd] -= 1;
        vector<string> result;
        generate(s.size(), odd, letter, result);
        return result;
    }
};