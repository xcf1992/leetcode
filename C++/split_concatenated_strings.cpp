/*
555. Split Concatenated Strings
Given a list of strings,
you could concatenate these strings together into a loop,
where for each string you could choose to reverse it or not.
Among all the possible loops, you need to find the lexicographically biggest string after cutting the loop,
which will make the looped string into a regular one.

Specifically, to find the lexicographically biggest string, you need to experience two phases:

1. Concatenate all the strings into a loop,
   where you can reverse some strings or not and connect them in the same order as given.
2. Cut and make one breakpoint in any place of the loop,
   which will make the looped string into a regular one starting from the character at the cutpoint.

And your job is to find the lexicographically biggest one among all the possible regular strings.

Example:
Input: "abc", "xyz"
Output: "zyxcba"
Explanation: You can get the looped string "-abcxyz-", "-abczyx-", "-cbaxyz-", "-cbazyx-",
where '-' represents the looped status.
The answer string came from the fourth looped one,
where you could cut from the middle character 'a' and get "zyxcba".
Note:
The input strings will only contain lowercase letters.
The total length of all the strings will not over 1,000.
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
using namespace std;

/*
To solve this problem, we must keep in heart the following points:

1. We know the cut point must come from the one string, assumed it is called c-string.
2. Then except the c-string, all the other string must become its lexicographically biggest status,
   assumed it is called b-status. Since only in this situation,
   we could get the lexicographically biggest string after cutting.
3. To reach the point 2,
   we need to first let all the string reach its b-status for the convenience of traversing all the strings afterward.
4. Then, for each string's traversal procedure,
   we need to decide whether it should be reversed or not since we don't know which might generate the final answer,
   and then we enumerated all the characters in this string.
*/
class Solution {
private:
    void findMaxStrings(vector<string>& strs) {
        for (string& str : strs) {
            string temp = str;
            reverse(temp.begin(), temp.end());
            str = str > temp ? str : temp;
        }
    }

    void solve(vector<string>& strs, int i, bool flag, string& result) {
        string str = strs[i];
        if (flag) {
            reverse(str.begin(), str.end());
        }

        string before = "";
        string after = "";
        for (int j = 0; j < i; j++) {
            before += strs[j];
        }
        for (int j = i + 1; j < strs.size(); j++) {
            after += strs[j];
        }

        for (int k = 0; k < str.size(); k++) {
            string cur = str.substr(k) + after + before + str.substr(0, k);
            result = result == "" ? cur : max(result, cur);
        }
    }
public:
    string splitLoopedString(vector<string>& strs) {
        if (strs.empty()) {
            return "";
        }

        findMaxStrings(strs);
        string result = "";
        for (int i = 0; i < strs.size(); i++) {
            solve(strs, i, true, result);
            solve(strs, i, false, result);
        }
        return result;
    }
};
