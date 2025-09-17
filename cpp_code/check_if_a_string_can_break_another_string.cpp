/*
1433. Check If a String Can Break Another String
https://leetcode.com/problems/check-if-a-string-can-break-another-string/

Given two strings: s1 and s2 with the same size,
check if some permutation of string s1 can break some permutation of string s2 or vice-versa
(in other words s2 can break s1).

A string x can break string y (both of size n)
if x[i] >= y[i] (in alphabetical order) for all i between 0 and n-1.

Example 1:
Input: s1 = "abc", s2 = "xya"
Output: true
Explanation: "ayx" is a permutation of s2="xya" which can break to string "abc" which is a permutation of s1="abc".

Example 2:
Input: s1 = "abe", s2 = "acd"
Output: false
Explanation: All permutations for s1="abe" are: "abe", "aeb", "bae", "bea", "eab" and "eba" and all permutation for s2="acd" are: "acd", "adc", "cad", "cda", "dac" and "dca". However, there is not any permutation from s1 which can break some permutation from s2 and vice-versa.

Example 3:
Input: s1 = "leetcodee", s2 = "interview"
Output: true

Constraints:
s1.length == n
s2.length == n
1 <= n <= 10^5
All strings consist of lowercase English letters.
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
#include <set>
#include <numeric>
using namespace std;

class Solution {
public:
    bool checkIfCanBreak(string s1, string s2) {
        if(s1.size()!=s2.size()) return false;
        int A[26]={0},B[26]={0};
        for(auto c:s1){
            A[c-'a']++;
        }
        for(auto c:s2){
            B[c-'a']++;
        }
        int a=0,b=0,k=0;
        for(int i=0;i<26;i++){
            a+=A[i];
            b+=B[i];
            if(k==1 && a<b) return false;
            if(k==2 && a>b) return false;
            if(a>b && k==0) k=1;
            else if(a<b && k==0) k=2;
        }
        return true;
    }
};

// O(nlogn)
class Solution1 {
private:
    bool check(string& s1, string& s2) {
        for (int i = 0; i < s1.size(); ++i) {
            if (s1[i] < s2[i]) {
                return false;
            }
        }
        return true;
    }
public:
    bool checkIfCanBreak(string s1, string s2) {
        sort(s1.rbegin(), s1.rend());
        sort(s2.rbegin(), s2.rend());
        return check(s1, s2) or check(s2, s1);
    }
};
