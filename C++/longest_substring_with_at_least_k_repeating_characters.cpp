//
//  longest_substring_with_at_least_k_repeating_characters.cpp
//  C++
//
//  Created by Chenfu Xie on 2/5/18.
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
    int find(string s, int k, int start, int end) {
        unordered_map<char, int> count;
        for (int i = start; i < end; i++) {
            count[s[i]] += 1;
        }
        
        int result = 0;
        int left = start;
        while (left < end) {
            while (left < end && count[s[left]] < k) {
                left += 1;
            }
            
            int right = left;
            
            while (right < end && count[s[right]] >= k) {
                right += 1;
            }
            
            if (left == start && right == end) {
                return right - left;
            }
            result = max(result, find(s, k, left, right));
            left = right;
        }
        return result;
    }
public:
    int longestSubstring(string s, int k) {
        return find(s, k, 0, s.size());
    }
};
