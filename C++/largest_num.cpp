#include <iostream>
#include <string>
/*
179. Largest Number
Given a list of non negative integers, arrange them such that they form the largest number.

Example 1:

Input: [10,2]
Output: "210"
Example 2:

Input: [3,30,34,5,9]
Output: "9534330"
Note: The result may be very large, so you need to return a string instead of an integer.
*/
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

class Compare {
public:
    bool operator() (string s1, string s2) {
        return s1 + s2 < s2 + s1;
    }
};

class Solution {
public:
    string largestNumber(vector<int> &num) {
        if (num.empty()) {
            return "";
        }
        
        vector<string> allNum;
        for (int i = 0; i < num.size(); i++) {
            allNum.push_back(to_string(num[i]));
        }
        
        sort(allNum.begin(), allNum.end(), Compare());
        
        if (allNum.back()[0] == '0') {
            return "0";
        }
        
        string result = "";
        for (int i = allNum.size() - 1; i >= 0; i--) {
            result += allNum[i];
        }
        
        return result;
    }
};