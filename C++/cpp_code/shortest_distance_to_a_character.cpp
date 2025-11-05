/*
 Given a string S and a character C, return an array of integers representing the shortest distance from the character C in the string.

 Example 1:

 Input: S = "loveleetcode", C = 'e'
 Output: [3, 2, 1, 0, 1, 0, 0, 1, 2, 2, 1, 0]


 Note:

 S string length is in [1, 10000].
 C is a single character, and guaranteed to be in string S.
 All letters in S and C are lowercase.
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
public:
    vector<int> shortestToChar(string S, char C) {
        vector<int> pos;
        for (int i = 0; i < S.size(); i++) {
            if (C == S[i]) {
                pos.push_back(i);
            }
        }

        int cur = 0;
        vector<int> result;
        for (int i = 0; i < S.size(); i++) {
            while (cur < pos.size() - 1 and abs(i - pos[cur])
            >
            abs(i - pos[cur + 1])
            )
            {
                cur += 1;
            }
            result.push_back(abs(i - pos[cur]));
        }
        return result;
    }
};