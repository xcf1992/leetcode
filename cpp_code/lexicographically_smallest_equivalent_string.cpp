/*
1061. Lexicographically Smallest Equivalent String

Given strings A and B of the same length,
we say A[i] and B[i] are equivalent characters.
For example, if A = "abc" and B = "cde",
then we have 'a' == 'c', 'b' == 'd', 'c' == 'e'.

Equivalent characters follow the usual rules of any equivalence relation:

Reflexivity: 'a' == 'a'
Symmetry: 'a' == 'b' implies 'b' == 'a'
Transitivity: 'a' == 'b' and 'b' == 'c' implies 'a' == 'c'

For example, given the equivalency information from A and B above,
S = "eed", "acd", and "aab" are equivalent strings,
and "aab" is the lexicographically smallest equivalent string of S.

Return the lexicographically smallest equivalent string of S by using the equivalency information from A and B.

Example 1:

Input: A = "parker", B = "morris", S = "parser"
Output: "makkek"
Explanation: Based on the equivalency information in A and B, we can group their characters as [m,p], [a,o], [k,r,s], [e,i]. The characters in each group are equivalent and sorted in lexicographical order. So the answer is "makkek".
Example 2:

Input: A = "hello", B = "world", S = "hold"
Output: "hdld"
Explanation:  Based on the equivalency information in A and B, we can group their characters as [h,w], [d,e,o], [l,r]. So only the second letter 'o' in S is changed to 'd', the answer is "hdld".
Example 3:

Input: A = "leetcode", B = "programs", S = "sourcecode"
Output: "aauaaaaada"
Explanation:  We group the equivalent characters in A and B as [a,o,e,r,s,c], [l,p], [g,t] and [d,m], thus all letters in S except 'u' and 'd' are transformed to 'a', the answer is "aauaaaaada".


Note:

String A, B and S consist of only lowercase English letters from 'a' - 'z'.
The lengths of string A, B and S are between 1 and 1000.
String A and B are of the same length.
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
private:
    char find(char c, vector<char>& parent) {
        if (c != parent[c - 'a']) {
            parent[c - 'a'] = find(parent[c - 'a'], parent);
        }
        return parent[c - 'a'];
    }
public:
    string smallestEquivalentString(string A, string B, string S) {
        int n = A.size();
        if (n == 0) {
            return S;
        }

        vector<char> parent(26, 'a');
        for (int i = 1; i < 26; ++i) {
            parent[i] = 'a' + i;
        }

        for (int i = 0; i < n; ++i) {
            char pa = find(A[i], parent);
            char pb = find(B[i], parent);
            if (pa != pb) {
                if (pa < pb) {
                    parent[pb - 'a'] = pa;
                }
                else {
                    parent[pa - 'a'] = pb;
                }
            }
        }

        for (int i = 0; i < S.size(); i++) {
            S[i] = find(S[i], parent);
        }
        return S;
    }
};
