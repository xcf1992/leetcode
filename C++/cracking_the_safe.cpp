/*
753. Cracking the Safe
There is a box protected by a password. The password is n digits,
where each letter can be one of the first k digits 0, 1, ..., k-1.

You can keep inputting the password, the password will automatically be matched against the last n digits entered.

For example, assuming the password is "345", I can open it when I type "012345", but I enter a total of 6 digits.

Please return any string of minimum length that is guaranteed to open the box after the entire string is inputted.

Example 1:
Input: n = 1, k = 2
Output: "01"
Note: "10" will be accepted too.
Example 2:
Input: n = 2, k = 2
Output: "00110"
Note: "01100", "10011", "11001" will be accepted too.
Note:
n will be in the range [1, 4].
k will be in the range [1, 10].
k^n will be at most 4096.
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
using namespace std;

/*
https://www.youtube.com/watch?v=iPLQgXUiU14

In order to guarantee to open the box at last,
the input password ought to contain all length-n combinations on digits [0..k-1] -
there should be k^n combinations in total.

To make the input password as short as possible,
we'd better make each possible length-n combination on digits [0..k-1]
occurs exactly once as a substring of the password.
The existence of such a password is proved by De Bruijn sequence:

A de Bruijn sequence of order n on a size-k alphabet A
is a cyclic sequence in which every possible length-n string on A occurs exactly
once as a substring. It has length k^n, which is also the number of distinct substrings
of length n on a size-k alphabet; de Bruijn sequences are therefore optimally short.

We reuse last n-1 digits of the input-so-far password as below:
*/
class Solution {
private:
    bool dfs(string& result, int n, int k, int total, unordered_set<string>& visited) {
        if (visited.size() == total) {
            return true;
        }

        string prefix = result.substr(result.size() - n + 1, n - 1); // reuse last n - 1 digits
        prefix.push_back('0');
        for (int i = 0; i < k; i++) {
            prefix.back() = '0' + i;
            if (visited.find(prefix) == visited.end()) { // we get a new possible pwd by using last n - 1 digit and a new digit
                visited.insert(prefix);
                result.push_back(prefix.back());
                if (dfs(result , n, k, total, visited)) {
                    return true;
                }
                visited.erase(prefix);
                result.pop_back();
            }
        }
        return false;
    }
public:
    string crackSafe(int n, int k) {
        string result(n, '0');
        int total = pow(k, n);
        unordered_set<string> visited;
        visited.insert(result);
        dfs(result , n, k, total, visited);
        return result;
    }
};
