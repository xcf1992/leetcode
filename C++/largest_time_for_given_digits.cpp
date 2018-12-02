/*
 Given an array of 4 digits, return the largest 24 hour time that can be made.
 
 The smallest 24 hour time is 00:00, and the largest is 23:59.  Starting from 00:00, a time is larger if more time has elapsed since midnight.
 
 Return the answer as a string of length 5.  If no valid time can be made, return an empty string.
 
 
 
 Example 1:
 
 Input: [1,2,3,4]
 Output: "23:41"
 Example 2:
 
 Input: [5,5,5,5]
 Output: ""
 
 
 Note:
 
 A.length == 4
 0 <= A[i] <= 9
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
#include <map>
#include <numeric>
using namespace std;

class Solution {
private:
    bool valid(string A) {
        if (A[0] > '2') {
            return false;
        }
        
        if (A[0] == '2') {
            if (A[1] > '3') {
                return false;
            }
        }
        
        if (A[2] > '5') {
            return false;
        }
        return true;
    }
    
    bool firstValid(vector<int>& A, vector<bool>& used, string& result) {
        if (result.size() == 4) {
            return valid(result);
        }
        
        for (int i = 0; i < 4; i++) {
            if (!used[i]) {
                result += ('0' + A[i]);
                used[i] = true;
                if (firstValid(A, used, result)) {
                    return true;
                }
                result.pop_back();
                used[i] = false;
            }
        }
        return false;
    }
public:
    string largestTimeFromDigits(vector<int>& A) {
        sort(A.rbegin(), A.rend());
        vector<bool> used(4, false);
        string result = "";
        if (!firstValid(A, used, result)) {
            return "";
        }
        result.insert(2, ":");
        return result;
    }
};
