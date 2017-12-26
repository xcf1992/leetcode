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

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    int diff(char a, char b) {
        int resut = a == b ? 0 : 1;
        return a == b ? 0 : 1;
    }
    
    int minDistance(string word1, string word2) {
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
                cout <<dp[i - 1][j - 1] + diff(word1[i], word2[j]) << endl;
                cout <<dp[i][j - 1] + 1 << endl;
                cout <<dp[i - 1][j] + 1 << endl;
                dp[i][j] = min(dp[i - 1][j - 1] + diff(word1[i], word2[j]),
                               min(dp[i][j - 1] + 1, dp[i - 1][j] + 1));
            }
        }
        
        return dp[m][n];
    }
};


int main() {
    ListNode * n1 = new ListNode(1);
    ListNode * n2 = new ListNode(2);
    ListNode * n3 = new ListNode(3);
    ListNode * n4 = new ListNode(4);
    n1 -> next = n2;
    n2 -> next = n3;
    n3 -> next = n4;
    Solution s;
    string a = "a";
    string b = "b";
    s.minDistance(a, b);
}
