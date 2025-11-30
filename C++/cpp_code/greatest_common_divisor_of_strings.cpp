/*
1071. Greatest Common Divisor of Strings

For strings S and T, we say "T divides S" if and only if S = T + ... + T  (T concatenated with itself 1 or more times)

Return the largest string X such that X divides str1 and X divides str2.

Example 1:

Input: str1 = "ABCABC", str2 = "ABC"
Output: "ABC"
Example 2:

Input: str1 = "ABABAB", str2 = "ABAB"
Output: "AB"
Example 3:

Input: str1 = "LEET", str2 = "CODE"
Output: ""


Note:

1 <= str1.length <= 1000
1 <= str2.length <= 1000
str1[i] and str2[i] are English uppercase letters.
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

/*
Try to explain it here:
Assume 2 strings are divided by T
Then:
str1 = nT
str2 = mT

n > m:
tempStr = str1-str2 = (n-m)T = kT
str2 - tempStr = (m-k)T = aT
....

At the end, there will be xT with one string, and empty with another string.
*/
class Solution {
public:
    string gcdOfStrings(string str1, string str2) {
        if (str1.size() < str2.size()) {
            swap(str1, str2);
        }

        if (str2.empty()) {
            return str1;
        }

        if (str1.substr(0, str2.size()) != str2) {
            return "";
        }
        return gcdOfStrings(str1.substr(str2.size()), str2);
    }
};

class Solution1 {
    // 5%
private:
    bool divisable(string str1, string str2) {
        int n1 = str1.size();
        int n2 = str2.size();
        if (n1 % n2 != 0) {
            return false;
        }

        for (int i = 0; i < n1; i += n2) {
            string temp = str1.substr(i, n2);
            if (temp != str2) {
                return false;
            }
        }
        return true;
    }

public:
    string gcdOfStrings(string str1, string str2) {
        if (str1.size() < str2.size()) {
            swap(str1, str2);
        }

        int n1 = str1.size();
        int n2 = str2.size();
        for (int i = n2; i >= 1; i--) {
            string temp = str2.substr(0, i);
            if (divisable(str1, temp) and divisable(str2, temp)) {
                return temp;
            }
        }
        return "";
    }
};