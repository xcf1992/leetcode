/*
The string "PAYPALISHIRING" is written in a zigzag pattern on a given number of rows like this: (you may want to display this pattern in a fixed font for better legibility)

P   A   H   N
A P L S I I G
Y   I   R
And then read line by line: "PAHNAPLSIIGYIR"

Write the code that will take a string and make this conversion given a number of rows:

string convert(string s, int numRows);
Example 1:

Input: s = "PAYPALISHIRING", numRows = 3
Output: "PAHNAPLSIIGYIR"
Example 2:

Input: s = "PAYPALISHIRING", numRows = 4
Output: "PINALSIGYAHRPI"
Explanation:

P     I    N
A   L S  I G
Y A   H R
P     I
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
public:
    string convert(string s, int nRows) {
        if (s.empty() || s.size() <= nRows || nRows == 1) {
            return s;
        }
        
        string result = "";
        for (int i = 0; i != nRows; i++) {
            int gap1 = 2 * nRows - 2 - 2 * i;
            int gap2 = 2 * i;
            
            int j = i;
            result.push_back(s[i]);
            while (j < s.size()) {
                if (gap1 != 0) {
                    j += gap1;
                    if (j < s.size()) {
                        result.push_back(s[j]);
                    }
                }
                
                if (gap2 != 0) {
                    j += gap2;
                    if (j < s.size()) {
                        result.push_back(s[j]);
                    }
                }
            }
        }    
        return result;
    }
};