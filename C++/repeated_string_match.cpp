/*
 Given two strings A and B, find the minimum number of times A has to be repeated such that B is a substring of it. If no such solution, return -1.
 
 For example, with A = "abcd" and B = "cdabcdab".
 
 Return 3, because by repeating A three times (“abcdabcdabcd”), B is a substring of it; and B is not a substring of A repeated two times ("abcdabcd").
 
 Note:
 The length of A and B will be between 1 and 10000.
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
#include <set>
using namespace std;

class Solution {
public:
    int repeatedStringMatch(string A, string B) {
        int lengthA = A.size();
        if (lengthA == 0) {
            return -1;
        }
        int legnthB = B.size();
        
        string temp = A;
        for (int i = 0; i <= legnthB / lengthA + 1; i++) {
            if (temp.find(B) != string::npos) {
                return i + 1;
            }
            temp += A;
        }
        return -1;
    }
};
