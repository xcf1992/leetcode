//
//  remove_invalid_parenthese.cpp
//  C++
//
//  Created by Chenfu Xie on 2/28/18.
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
 Remove the minimum number of invalid parentheses in order to make the input string valid. Return all possible results.
 
 Note: The input string may contain letters other than the parentheses ( and ).
 
 Examples:
 "()())()" -> ["()()()", "(())()"]
 "(a)())()" -> ["(a)()()", "(a())()"]
 ")(" -> [""]
 */

class Solution {
private:
    bool isValid(string s) {
        int count = 0;
        for (char c : s) {
            if (c == '(') {
                count += 1;
            }
            if (c == ')') {
                count -= 1;
            }
            if (count < 0) {
                return false;
            }
        }
        return count == 0;
    }
public:
    vector<string> removeInvalidParentheses(string s) {
        queue<string> bfs;
        unordered_set<string> visit;
        
        bfs.push(s);
        visit.insert(s);
        
        vector<string> result;
        bool found = false;
        while (!bfs.empty()) {
            string curS = bfs.front();
            bfs.pop();
            
            if (isValid(curS)) {
                result.push_back(curS);
                found = true;
            }
            
            if (found) {
                continue;
            }
            
            for (int i = 0; i < curS.size(); i++) {
                if (curS[i] != '(' && curS[i] != ')') {
                    continue;
                }
                
                string newS = curS.substr(0, i) + curS.substr(i + 1);
                if (visit.find(newS) == visit.end()) {
                    visit.insert(newS);
                    bfs.push(newS);
                }
            }
        }
        return result;
    }
};
