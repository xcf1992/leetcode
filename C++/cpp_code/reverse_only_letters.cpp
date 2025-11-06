/*
 Given a string S, return the "reversed" string where all characters that are not a letter stay in the same place, and
 all letters reverse their positions.



 Example 1:

 Input: "ab-cd"
 Output: "dc-ba"
 Example 2:

 Input: "a-bC-dEf-ghIj"
 Output: "j-Ih-gfE-dCba"
 Example 3:

 Input: "Test1ng-Leet=code-Q!"
 Output: "Qedo1ct-eeLg=ntse-T!"


 Note:

 S.length <= 100
 33 <= S[i].ASCIIcode <= 122
 S doesn't contain \ or "
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
#include <numeric>
using namespace std;

class Solution {
public:
    string reverseOnlyLetters(string S) {
        int start = 0;
        int end = S.size() - 1;
        while (start < end) {
            while (!isalpha(S[start])) {
                start += 1;
            }
            while (!isalpha(S[end])) {
                end -= 1;
            }

            if (start < end) {
                swap(S[start], S[end]);
                start += 1;
                end -= 1;
            }
        }
        return S;
    }
};