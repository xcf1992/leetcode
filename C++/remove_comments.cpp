/*
 It is guaranteed that every open block comment will eventually be closed, so /* outside of a line or block comment always starts a new comment.
 
 Finally, implicit newline characters can be deleted by block comments. Please see the examples below for details.
 
 After removing the comments from the source code, return the source code in the same format.
 
 The length of source is in the range [1, 100].
 The length of source[i] is in the range [0, 80].
 Every open block comment is eventually closed.
 There are no single-quote, double-quote, or control characters in the source code.
 */

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <map>
#include <unordered_set>
#include <algorithm>
#include <cmath>
#include <queue>
#include <stack>
#include <stdio.h>
#include <set>
using namespace std;

class Solution {
public:
    vector<string> removeComments(vector<string>& source) {
        
        vector<string> result;
        bool inComment = false;
        string line = "";
        for (int i = 0; i < source.size(); i++) {
            for (int j = 0; j < source[i].size(); j++) {
                if (!inComment && source[i][j] == '/' && j + 1 < source[i].size() && source[i][j + 1] == '/') {
                    break;
                }
                else if (!inComment && source[i][j] == '/' && j + 1 < source[i].size() && source[i][j + 1] == '*') {
                    inComment = true;
                    j += 1;
                }
                else if (inComment && source[i][j] == '*' && j + 1 < source[i].size() && source[i][j + 1] == '/') {
                    inComment = false;
                    j += 1;
                }
                else if (!inComment) {
                    line.push_back(source[i][j]);
                }
            }
            
            if (!inComment && !line.empty()) {
                result.push_back(line);
                line = "";
            }
        }
        return result;
    }
};
