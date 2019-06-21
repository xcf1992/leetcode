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
#include <set>
#include <numeric>
using namespace std;

class Solution { // dp
public:
    vector<string> wordBreak(string s, vector<string>& wordDict) {
        unordered_set<string> dict(wordDict.begin(), wordDict.end());
        int n = s.size();
        vector<vector<string>> dp(n + 1);

        dp[0].push_back("");
        for (int i = 1; i <= n; ++i) {
            for (int j = 0; j < i; ++j) {
                string word = s.substr(j, i);
                if (dp[j].size() > 0 and dict.find(word) != dict.end()) {
                    for (string& bw : dp[j]) {
                        dp[i].push_back(bw + (bw == "" ? "" : " ") + word);
                    }
                }
            }
        }
        return dp[n];
    }
};

int main() {
    Solution s;
    vector<int> temp({5,4,3,2,1});
    vector<int> temp1({1,3,3,3,2});
    vector<vector<char>> matrix({
        {'1','0','1','0','0'},
        {'1','0','1','1','1'},
        {'1','1','1','1','1'},
        {'1','0','0','1','0'}
    });
    vector<string> words({"cat","cats","and","sand","dog"});
    s.wordBreak("catsanddog", words);
}
