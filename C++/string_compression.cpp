//
//  string_compression.cpp
//  C++
//
//  Created by Chenfu Xie on 2/4/18.
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
public:
    int compress(vector<char>& chars) {
        if (chars.empty()) {
            return 0;
        }
        int start = 0;
        int end = 0;
        int count = 0;
        while (end < chars.size()) {
            if (chars[end] == chars[start]) {
                count++;
                end++;
            }
            else {
                start += 1;
                if (count > 1) {
                    string num = to_string(count);
                    for (char c : num) {
                        chars[start] = c;
                        start += 1;
                    }
                }
                count = 1;
                chars[start] = chars[end];
                end++;
            }
        }
        start += 1;
        if (count > 1) {
            string num = to_string(count);
            for (char c : num) {
                chars[start] = c;
                start += 1;
            }
        }
        return start;
    }
};
