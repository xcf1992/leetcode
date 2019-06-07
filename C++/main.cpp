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
    bool findRepeat(string S, int len) {
        unordered_set<long long> visited;
        size_t p = 113;
        size_t mod = 1e9 + 7;
        
        long long value = 0;
        long long power = 1;
        for (int i = 0; i < len; ++i) {
            value = (value * p + S[i]) ;
            power = (power * p) ;
        }
        
        visited.insert(value);
        for (int i = len; i < S.size(); ++i) {
            value = (value * p + S[i]) % mod;
            value = value - power * S[i - len];
            while (value < 0) {
                value += mod;
            }
            value %= mod;
            if (visited.find(value) != visited.end()) {
                return true;
            }
        }
        return false;
    }
public:
    int longestRepeatingSubstring(string S) {
        int n = S.size();
        if (n <= 1) {
            return 0;
        }
        
        for (int len = n - 1; len >= 1; --len) {
            if (findRepeat(S, len)) {
                return len;
            }
        }
        return 0;
    }
};

int main() {
    Solution s;
    vector<int> temp({1,15,7,9,2,5,10});
    vector<vector<int>> matrix({
        {0,1,0},
        {1,1,1},
        {0,1,0}
    });
    s.longestRepeatingSubstring("aaaaa");
}
