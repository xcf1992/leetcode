//
//  group_shited_strings.cpp
//  C++
//
//  Created by Chenfu Xie on 3/1/18.
//  Copyright © 2018 Chenfu Xie. All rights reserved.
//

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
using namespace std;

/*
 Given a string, we can "shift" each of its letter to its successive letter, for example: "abc" -> "bcd". We can keep "shifting" which forms the sequence:

 "abc" -> "bcd" -> ... -> "xyz"
 Given a list of strings which contains only lowercase alphabets, group all strings that belong to the same shifting sequence.

 For example, given: ["abc", "bcd", "acef", "xyz", "az", "ba", "a", "z"],
 A solution is:

 [
 ["abc","bcd","xyz"],
 ["az","ba"],
 ["acef"],
 ["a","z"]
 ]
*/

class Solution {
private:
    string buildIndentity(string s) {
        string result = "";
        for (int i = 1; i < s.size(); i++) {
            result += to_string((s[i] - s[i - 1] + 26) % 26);
        }
        return result;
    }
public:
    vector<vector<string>> groupStrings(vector<string>& strings) {
        unordered_map<string, vector<string>> group;
        for (string s : strings) {
            group[buildIndentity(s)].push_back(s);
        }

        vector<vector<string>> result;
        for (auto g : group) {
            result.push_back(g.second);
        }

        return result;
    }
};
