/*
38. Count and Say
https://leetcode.com/problems/count-and-say/

The count-and-say sequence is the sequence of integers with the first five terms as following:
1.     1
2.     11
3.     21
4.     1211
5.     111221
1 is read off as "one 1" or 11.
11 is read off as "two 1s" or 21.
21 is read off as "one 2, then one 1" or 1211.

Given an integer n where 1 ≤ n ≤ 30, generate the nth term of the count-and-say sequence.

Note:
Each term of the sequence of integers will be represented as a string.

Example 1:
Input: 1
Output: "1"

Example 2:
Input: 4
Output: "1211"
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
#include <climits>
using namespace std;

class Solution {
private:
    string constuct(string say) {
        vector<int> num;
        char digit = say[0];
        int count = 1;
        string result = "";
        for (int i = 1; i < say.size(); ++i) {
            if (say[i] == digit) {
                count += 1;
            } else {
                result += to_string(count) + digit;
                count = 1;
                digit = say[i];
            }
        }
        result += to_string(count) + digit;
        return result;
    }

public:
    string countAndSay(int n) {
        if (n <= 0) {
            return "";
        }

        string say = "1";
        for (int i = 1; i < n; i++) {
            say = constuct(say);
        }
        return say;
    }
};