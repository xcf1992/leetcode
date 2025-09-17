//
//  letter_case_permutation.cpp
//  C++
//
//  Created by Chenfu Xie on 2/17/18.
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

class Solution {
private:
    void addString(string s, vector<string>& result, int pos, string cur) {
        if (pos == s.size()) {
            result.push_back(cur);
            return;
        }

        cur.push_back(s[pos]);
        if (s[pos] >= '0' and s[pos] <= '9') {
            addString(s, result, pos + 1, cur);
            return;
        }

        addString(s, result, pos + 1, cur);
        if (s[pos] >= 'a' and s[pos] <= 'z') {
            cur.back() = 'A' + s[pos] - 'a';
        }
        else {
            cur.back() = 'a' + s[pos] - 'A';
        }
        addString(s, result, pos + 1, cur);
        return;
    }
public:
    vector<string> letterCasePermutation(string S) {
        vector<string> result;
        string cur = "";
        addString(S, result, 0, cur);
        return result;
    }
};
