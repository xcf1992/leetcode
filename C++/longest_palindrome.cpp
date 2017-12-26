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
using namespace std;


class Solution {
public:
    int longestPalindrome(string s) {
        int result = 0;
        vector<int> count(256, 0);
        
        for (char c : s) {
            count[c] += 1;
        }
        int odds = 0;
        for (int num : count) {
            odds += num & 1;
        }

        return s.size() - odds + (odds > 0);
    }
};

int main() {
    Solution s;
    return 0;
}