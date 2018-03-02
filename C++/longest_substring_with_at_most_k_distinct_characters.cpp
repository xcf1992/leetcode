//
//  longest_substring_with_at_most_k_distinct_characters.cpp
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
 Given a string, find the length of the longest substring T that contains at most k distinct characters.
 
 For example, Given s = “eceba” and k = 2,
 
 T is "ece" which its length is 3.
 */

class Solution {
public:
    int lengthOfLongestSubstringKDistinct(string s, int k) {
        unordered_map<char, int> pos;
        int start = 0;
        int end = 0;
        int count = 0;
        int result = 0;
        while (end < s.size()) {
            if (pos.find(s[end]) == pos.end() || pos[s[end]] < start) {
                count += 1;
            }
            pos[s[end]] = end;
            
            while (count > k) {
                if (start == pos[s[start]]) {
                    count -= 1;
                }
                start += 1;
            }
            
            result = max(result, end - start + 1);
        }
        return result;
    }
};
