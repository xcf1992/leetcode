#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

int diff(char a, char b) {
    if (a == b) {
        return 0;
    }
    return 1;
}

int mindp(string word1, string word2) {
    int m = word1.size();
    int n = word2.size();
    if (m == 0 || n == 0) {
        return abs(m - n);
    }

    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
    dp[0][0] = 0;

    for (int i = 1; i < m + 1; i++) {
        dp[i][0] = i;
    }
    for (int j = 1; j < n + 1; j++) {
        dp[0][j] = j;
    }
    for (int i = 1; i < m + 1; i++) {
        for (int j = 1; j < n + 1; j++) {
            dp[i][j] = min(dp[i - 1][j - 1] + diff(word1[i - 1], word2[j - 1]),
                min(dp[i][j - 1] + 1, dp[i - 1][j] + 1));
        }
    }

    return dp[m][n];
}

int main() {
	string a = "a";
	string b= "a";
	int result = mindp(a, b);
	return 0;
}