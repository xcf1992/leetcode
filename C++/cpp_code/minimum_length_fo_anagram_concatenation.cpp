/*
https://leetcode.com/problems/minimum-length-of-anagram-concatenation/description/
3138. Minimum Length of Anagram Concatenation

You are given a string s, which is known to be a concatenation of anagrams of some string t.

Return the minimum possible length of the string t.

An anagram is formed by rearranging the letters of a string. For example, "aab", "aba", and, "baa" are anagrams of
"aab".



Example 1:

Input: s = "abba"

Output: 2

Explanation:

One possible string t could be "ba".

Example 2:

Input: s = "cdef"

Output: 4

Explanation:

One possible string t could be "cdef", notice that t can be equal to s.

Example 2:

Input: s = "abcbcacabbaccba"

Output: 3



Constraints:

1 <= s.length <= 105
s consist only of lowercase English letters.
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
#include <set>
using namespace std;

class Solution {
public:
    int minAnagramLength(string s) {
        int n = s.length();
        vector<vector<int>>v(n,vector<int>(26));
        vector<int>c(26,0);
        for(int i=0;i<s.length();i++){
            c[s[i]-'a']++;
            v[i] = c;
        }
        for(int i=0;i<26;i++){
            if(c[i]==n) return 1;
        }
        for(int i=2;i<n;i++){
            if(n%i!=0) continue;
            vector<int>cm = v[i-1];
            bool flag = false;
            for(int j = i;j<n;j+=i){
                vector<int>d(26,0);
                for(int k=0;k<26;k++){
                    d[k] = v[j+i-1][k]-v[j-1][k];
                }
                if(d!=cm){
                    flag = true;
                    break;
                }
            }
            if(flag==false) return i;
        }
        return n;
    }
};