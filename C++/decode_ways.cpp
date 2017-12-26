#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <cmath>
using namespace std;

  int numDecodings(string s) {
        if (s.empty()) {
            return 0;
        }
        if (s[0] == '0') {
            return 0;
        }
        if (s.size() == 1) {
            return 1;
        }
        
        vector<int> dp(s.size() + 1, 0);
        dp[0] = 1;
        dp[1] = 1;
        
        for (int i = 2; i < s.size(); i++) {
            int num = (s[i - 2] - '0') * 10 + (s[i - 1] - '0');
            if (num == 0) {
                return 0;
            }
            else if (num < 10) {
                dp[i] = dp[i - 1];
            }
            else if (num == 10 || num == 20) {
                dp[i] = dp[i - 2];
            }
            else if (num <= 26) {
                dp[i] = dp[i - 1] + dp[i - 2];
            }
            else if (num % 10 == 0) {
                return 0;
            }
            else {
                dp[i] = dp[i - 1];
            }
        }
        
        return dp[s.size()];
    }

int main() {
	string s = "10";
	numDecodings(s);
	return 0;
}