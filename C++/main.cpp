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
    string minWindow(string s, string t) {
        int m = s.size();
        int n = t.size();
        if (m == 0 or n == 0 or n > m) {
            return "";
        }

        unordered_map<char, int> count;
        for (char c : t) {
            count[c] += 1;
        }

        int result = m + 1;
        int left = 0;
        int start = 0;
        int i = 0;
        int required = n;
        while (i <= m and start <= m) {
            if (required > 0) {
                if (i == m) {
                    break;
                }
                /*
                 should not use count.find(s[i]) != count.end() to check, cause for cases like bba
                 */
                count[s[i]] -= 1;
                if (count[s[i]] >= 0) {
                    required -= 1;
                }
                i += 1;
            }
            else {
                if (i - start < result) {
                    result = i - start;
                    left = start;
                }
                count[s[start]] -= 1;
                if (count[s[start]] > 0) {
                    required += 1;
                }
                start += 1;
            }
        }
        return result == m + 1 ? "" : s.substr(left, result);
    }
};

int main() {
    Solution s;
    vector<int> temp({1,4,2,5,3});
    vector<vector<int>> matrix({
        {0,1,0},
        {1,1,1},
        {0,1,0}
    });
    s.minWindow("ADOBECODEBANC","ABC");
}
