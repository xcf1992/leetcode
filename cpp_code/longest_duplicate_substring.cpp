/*
1044. Longest Duplicate Substring

Given a string S, consider all duplicated substrings:
(contiguous) substrings of S that occur 2 or more times.
(The occurrences may overlap.)

Return any duplicated substring that has the longest possible length.
(If S does not have a duplicated substring, the answer is "".)

Example 1:
Input: "banana"
Output: "ana"

Example 2:
Input: "abcd"
Output: ""

Note:
2 <= S.length <= 10^5
S consists of lowercase English letters.
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
    int q = 6 * (1 << 20) + 1;
    int b = 31;

    int check(string &s, int k) {
        int n = s.size();
        int power = 1;
        for (int i = 1; i < k; ++i) {
            power = (power * b) % q;
        }
        int hash = 0;
        for (int i = 0; i < k; ++i) {
            hash = (hash * b % q + s[i]) % q;
        }

        unordered_map<int, vector<int>> seen;
        seen[hash].push_back(0);
        for (int i = k; i < n; ++i) {
            hash = (hash - power * s[i - k] % q + q) % q;
            hash = (hash * b % q + s[i]) % q;
            if (seen.find(hash) != seen.end()) {
                for (int index : seen[hash]) {
                    if (s.substr(index, k) == s.substr(i - k + 1, k)) {
                        return index;
                    }
                }
            }
            seen[hash].push_back(i - k + 1);
        }
        return -1;
    }
public:
    string longestDupSubstring(string S) {
        int n = S.size();
        int lo = 0;
        int hi = n;
        int startIndex = -1;
        int k = 0;
        while (lo < hi) {
            int mid = lo + (hi - lo) / 2;
            int index = check(S, mid);

            if (index != -1) {
                startIndex = index;
                k = mid;
                lo = mid + 1;
            }
            else {
                hi = mid;
            }
        }
        return k == 0 ? "" : S.substr(startIndex, k);
    }
};
