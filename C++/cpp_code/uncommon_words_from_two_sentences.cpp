/*
 We are given two sentences A and B.  (A sentence is a string of space separated words.  Each word consists only of
 lowercase letters.)

 A word is uncommon if it appears exactly once in one of the sentences, and does not appear in the other sentence.

 Return a list of all uncommon words.

 You may return the list in any order.



 Example 1:

 Input: A = "this apple is sweet", B = "this apple is sour"
 Output: ["sweet","sour"]
 Example 2:

 Input: A = "apple apple", B = "banana"
 Output: ["banana"]


 Note:

 0 <= A.length <= 200
 0 <= B.length <= 200
 A and B both contain only spaces and lowercase letters.
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
#include <climits>
#include <set>
#include <numeric>
using namespace std;

class Solution {
public:
    vector<string> uncommonFromSentences(string A, string B) {
        unordered_map<string, int> words1;
        int pos;
        while ((pos = A.find(' ')) != string::npos) {
            words1[A.substr(0, pos)] += 1;
            A = A.substr(pos + 1);
        }
        words1[A] += 1;

        while ((pos = B.find(' ')) != string::npos) {
            words1[B.substr(0, pos)] += 1;
            B = B.substr(pos + 1);
        }
        words1[B] += 1;

        vector<string> result;
        for (auto it = words1.begin(); it != words1.end(); it++) {
            if (it->second == 1) {
                result.push_back(it->first);
            }
        }
        return result;
    }
};