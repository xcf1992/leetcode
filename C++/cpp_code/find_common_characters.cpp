/*
 1002. Find Common Characters

 Given an array A of strings made only from lowercase letters, return a list of all characters that show up in all strings within the list (including duplicates).  For example, if a character occurs 3 times in all strings but not 4 times, you need to include that character three times in the final answer.

 You may return the answer in any order.



 Example 1:

 Input: ["bella","label","roller"]
 Output: ["e","l","l"]
 Example 2:

 Input: ["cool","lock","cook"]
 Output: ["c","o"]


 Note:

 1 <= A.length <= 100
 1 <= A[i].length <= 100
 A[i][j] is a lowercase letter
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
    vector<string> commonChars(vector<string> &A) {
        vector<int> inAll(26, 0);
        for (char c: A[0]) {
            inAll[c - 'a'] += 1;
        }
        for (string &a: A) {
            vector<int> exist(26, 0);
            for (char c: a) {
                exist[c - 'a'] += 1;
            }
            for (int i = 0; i < 26; i++) {
                inAll[i] = min(inAll[i], exist[i]);
            }
        }

        vector<string> result;
        for (int i = 0; i < 26; i++) {
            for (int j = 0; j < inAll[i]; j++) {
                result.push_back(string(1, 'a' + i));
            }
        }
        return result;
    }
};