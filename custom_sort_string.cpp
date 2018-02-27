//
//  custom_sort_string.cpp
//  C++
//
//  Created by Chenfu Xie on 2/26/18.
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
using namespace std;

/*
 S and T are strings composed of lowercase letters. In S, no letter occurs more than once.
 
 S was sorted in some custom order previously. We want to permute the characters of T so that they match the order that S was sorted. More specifically, if x occurs before y in S, then x should occur before y in the returned string.
 
 Return any permutation of T (as a string) that satisfies this property.
 
 Example :
 Input:
 S = "cba"
 T = "abcd"
 Output: "cbad"
 Explanation:
 "a", "b", "c" appear in S, so the order of "a", "b", "c" should be "c", "b", and "a".
 Since "d" does not appear in S, it can be at any position in T. "dcba", "cdba", "cbda" are also valid outputs.
 
 
 Note:
 
 S has length at most 26, and no character is repeated in S.
 T has length at most 200.
 S and T consist of lowercase letters only.
 */

class Solution {
public:
    string customSortString(string S, string T) {
        unordered_map<char, int> dict;
        for (int i = 0; i < S.size(); i++) {
            dict[S[i]] = i;
        }
        
        sort(T.begin(), T.end(), [&](char a, char b) {return dict[a] < dict[b];});
        return T;
    }
};
