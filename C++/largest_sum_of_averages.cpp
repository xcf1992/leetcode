/*
 We partition a row of numbers A into at most K adjacent (non-empty) groups, then our score is the sum of the average of each group. What is the largest score we can achieve?
 
 Note that our partition must use every number in A, and that scores are not necessarily integers.
 
 Example:
 Input:
 A = [9,1,2,3,9]
 K = 3
 Output: 20
 Explanation:
 The best choice is to partition A into [9], [1, 2, 3], [9]. The answer is 9 + (1 + 2 + 3) / 3 + 9 = 20.
 We could have also partitioned A into [9, 1], [2], [3, 9], for example.
 That partition would lead to a score of 5 + 2 + 6 = 13, which is worse.
 
 Note:
 1 <= A.length <= 100.
 1 <= A[i] <= 10000.
 1 <= K <= A.length.
 Answers within 10^-6 of the correct answer will be accepted as correct.
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
using namespace std;

class Solution {
public:
    double largestSumOfAverages(vector<int>& A, int K) {
        int n = A.size();
        if(A.empty() || K == 0)
            return 0;
        vector<vector<double>> dp(K+1,vector<double>(A.size(),0));
        vector<int> sum;
        sum.push_back(A[0]);
        for(int i = 1; i < A.size(); i++)
            sum.push_back(A[i] + sum.back());
        
        for (int k = 1; k <= K; k++) {
            for (int i = k - 1; i < n; i++) {
                if (k == 1) {
                    dp[k][i] = double (sum[i]) / (i + 1);
                }
                else {
                    for (int j = k - 2; j < i; j++) {
                        dp[k][i] = max(dp[k][i], dp[k - 1][j] + double(sum[i] - sum[j]) / (i - j));
                    }
                }
            }
        }
        return dp[K][A.size()-1];
    }
};
