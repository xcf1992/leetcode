/*
 In a string S of lowercase letters, these letters form consecutive groups of the same character.

 For example, a string like S = "abbxxxxzyy" has the groups "a", "bb", "xxxx", "z" and "yy".

 Call a group large if it has 3 or more characters.  We would like the starting and ending positions of every large group.

 The final answer should be in lexicographic order.



 Example 1:

 Input: "abbxxxxzzy"
 Output: [[3,6]]
 Explanation: "xxxx" is the single large group with starting  3 and ending positions 6.
 Example 2:

 Input: "abc"
 Output: []
 Explanation: We have "a","b" and "c" but no large group.
 Example 3:

 Input: "abcdddeeeeaabbbcd"
 Output: [[3,5],[6,9],[12,14]]


 Note:  1 <= S.length <= 1000
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
    vector<vector<int> > largeGroupPositions(string S) {
        if (S.size() < 3) {
            return {};
        }

        vector<vector<int> > result;
        int start = 0;
        int end = 1;
        while (end < S.size()) {
            while (end < S.size() and S[end]
            ==
            S[start]
            )
            {
                end += 1;
            }

            if (end - start >= 3) {
                result.push_back({start, end - 1});
            }
            start = end;
            end += 1;
        }
        return result;
    }
};