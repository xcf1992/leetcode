/*
1657. Determine if Two Strings Are Close
https://leetcode.com/problems/determine-if-two-strings-are-close/

Two strings are considered close if you can attain one from the other using the following operations:
Operation 1: Swap any two existing characters.
For example, abcde -> aecdb
Operation 2: Transform every occurrence of one existing character into another existing character,
and do the same with the other character.
For example, aacabb -> bbcbaa (all a's turn into b's, and all b's turn into a's)
You can use the operations on either string as many times as necessary.

Given two strings, word1 and word2,
return true if word1 and word2 are close,
and false otherwise.

Example 1:
Input: word1 = "abc", word2 = "bca"
Output: true
Explanation: You can attain word2 from word1 in 2 operations.
Apply Operation 1: "abc" -> "acb"
Apply Operation 1: "acb" -> "bca"

Example 2:
Input: word1 = "a", word2 = "aa"
Output: false
Explanation: It is impossible to attain word2 from word1, or vice versa, in any number of operations.

Example 3:
Input: word1 = "cabbba", word2 = "abbccc"
Output: true
Explanation: You can attain word2 from word1 in 3 operations.
Apply Operation 1: "cabbba" -> "caabbb"
Apply Operation 2: "caabbb" -> "baaccc"
Apply Operation 2: "baaccc" -> "abbccc"

Example 4:
Input: word1 = "cabbba", word2 = "aabbss"
Output: false
Explanation: It is impossible to attain word2 from word1, or vice versa, in any amount of operations.

Constraints:
1 <= word1.length, word2.length <= 105
word1 and word2 contain only lowercase English letters.
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
#include <cfloat>
#include <stdio.h>
#include <map>
#include <set>
#include <list>
#include <numeric>
#include <random>
#include <vector>
#include "extra_data_types.hpp"
using namespace std;
/*
Idea : Two thing's Need to check

Frequency of Char need's to be same there both of string as we can do Transform every occurrence of one existing
character into another existing character All the unique char which there in String1 need's to there as well In string2
let's See One example :

String 1 = "aabaacczp"        String 2="bbzbbaacp"
Frequency in string1 :                         Frequency in string2 :
       a -> 4                                              b->4
        b->1                                                a->2
        c->2                                                z->1
        z->1                                                c->1
        p->1                                                p->1

see in String 1 count array ->   1, 1, 1, 2, 4 =>sorted order
and in String 2 count array ->   1, 1, 1, 2, 4 =>sorted order

Unique all char   a,b,c,z,p  in string 1 is there as well in string2 so it's a valid One just return True
*/
class Solution {
public:
    bool closeStrings(string word1, string word2) {
        vector<int> cnt1(26, 0), cnt2(26, 0);
        set<char> s1, s2;
        for (char c : word1) {
            cnt1[c - 'a'] += 1;
            s1.insert(c);
        }
        for (char c : word2) {
            cnt2[c - 'a'] += 1;
            s2.insert(c);
        }

        sort(cnt1.begin(), cnt1.end());
        sort(cnt2.begin(), cnt2.end());
        return cnt1 == cnt2 and s1 == s2;
    }
};