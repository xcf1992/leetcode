/*
 Given a list of strings, you could concatenate these strings together into a loop, where for each string you could choose to reverse it or not. Among all the possible loops, you need to find the lexicographically biggest string after cutting the loop, which will make the looped string into a regular one.
 
 Specifically, to find the lexicographically biggest string, you need to experience two phases:
 
 Concatenate all the strings into a loop, where you can reverse some strings or not and connect them in the same order as given.
 Cut and make one breakpoint in any place of the loop, which will make the looped string into a regular one starting from the character at the cutpoint.
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
        
        string str1 = "";
        string str2 = "";
        for (int j = 0; j < i; j++) {
            str1 += strs[j];
        }
        for (int j = i + 1; j < strs.size(); j++) {
            str2 += strs[j];
        }
        
        for (int k = 0; k < str.size(); k++) {
            string cur = str.substr(k) + str2 + str1 + str.substr(0, k);
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
