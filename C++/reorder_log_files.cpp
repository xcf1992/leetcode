/*
 937. Reorder Log Files
 You have an array of logs.
 Each log is a space delimited string of words.

 For each log, the first word in each log is an alphanumeric identifier.
 Then, either:
    Each word after the identifier will consist only of lowercase letters, or;
    Each word after the identifier will consist only of digits.
 We will call these two varieties of logs letter-logs and digit-logs.
 It is guaranteed that each log has at least one word after its identifier.

 Reorder the logs so that all of the letter-logs come before any digit-log.
 The letter-logs are ordered lexicographically ignoring identifier,
 with the identifier used in case of ties.
 The digit-logs should be put in their original order.

 Return the final order of the logs.



 Example 1:

 Input: ["a1 9 2 3 1","g1 act car","zo4 4 7","ab1 off key dog","a8 act zoo"]
 Output: ["g1 act car","a8 act zoo","ab1 off key dog","a1 9 2 3 1","zo4 4 7"]


 Note:

 0 <= logs.length <= 100
 3 <= logs[i].length <= 100
 logs[i] is guaranteed to have an identifier, and a word after the identifier.
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
public:
    vector<string> reorderLogFiles(vector<string>& logs) {
        vector<string> letterLogs;
        vector<string> digitLogs;
        for (string log : logs) {
            int found = log.find(" ");
            if (isdigit(log[found + 1])) {
                digitLogs.push_back(log);
            }
            else {
                letterLogs.push_back(log);
            }
        }

        sort(letterLogs.begin(), letterLogs.end(), [](string& a, string& b) {
            string tempa = a.substr(a.find(" ") + 1);
            string tempb = b.substr(b.find(" ") + 1);
            if (tempa == tempb) {
                return a < b;
            }
            return tempa < tempb;
        });

        for (string log : digitLogs) {
            letterLogs.push_back(log);
        }
        return letterLogs;
    }
};
