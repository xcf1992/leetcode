/*
 Alice plays the following game, loosely based on the card game "21".
 
 Alice starts with 0 points, and draws numbers while she has less than K points.  During each draw, she gains an integer number of points randomly from the range [1, W], where W is an integer.  Each draw is independent and the outcomes have equal probabilities.
 
 Alice stops drawing numbers when she gets K or more points.  What is the probability that she has N or less points?
 
 Example 1:
 
 Input: N = 10, K = 1, W = 10
 Output: 1.00000
 Explanation:  Alice gets a single card, then stops.
 Example 2:
 
 Input: N = 6, K = 1, W = 10
 Output: 0.60000
 Explanation:  Alice gets a single card, then stops.
 In 6 out of W = 10 possibilities, she is at or below N = 6 points.
 Example 3:
 
 Input: N = 21, K = 17, W = 10
 Output: 0.73278
 Note:
 
 0 <= K <= N <= 10000
 1 <= W <= 10000
 Answers will be accepted as correct if they are within 10^-5 of the correct answer.
 The judging time limit has been reduced for this question.
 */

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <map>
#include <unordered_set>
#include <algorithm>
#include <cmath>
#include <queue>
#include <stack>
#include <stdio.h>
#include <set>
using namespace std;

/*
 the transition equation dp[i] = (dp[i - W] + dp[i - W + 1] + ... + dp[i - 1]) / W could be simplified to dp[i] = (sum[i - 1] - sum[i - W - 1]) / W.
 
 dp[i] = (sum[i - 1] - sum[i - W - 1]) / W
 sum[i] = sum[i - 1] + dp[i]
 => sum[i] = sum[i - 1] + (sum[i - 1] - sum[i - W - 1]) / W
 
 Furthermore, if we use dp[i] to directly represent the sum[i],
 we can get dp[i] = dp[i - 1] + (dp[i - 1] - dp[i - W - 1]) / W. This equation takes us to the final O(K + W) solution. Just take care with the beginning and the end of the array.
 */
class Solution {
public:
    double new21Game(int N, int K, int W) {
        if (N >= K + W - 1) {
            return 1.0;
        }

        vector<double> dp(K + W, 0.0);
        dp[0] = 1.0;
        for (int i = 1; i < K + W; i++) {
            dp[i] = dp[i - 1];
            
            if (i <= W) {
                dp[i] += dp[i - 1] / W;
            }
            else {
                dp[i] += (dp[i - 1] - dp[i - W - 1]) / W;
            }
            
            if (i > K) {
                dp[i] -= (dp[i - 1] - dp[K - 1]) / W;
            }
        }
        
        return dp[N] - dp[K - 1];
    }
};

/*
 The maximum result one can get is K + W - 1, since if one get K points already he will gain any point anymore
 and if N >= K + W - 1 then it will always succeed
 so to caculate Probability(X) = Sum(Probability(X - i)), while i >= 1, i <= W && X - i >= 0 && X - i < K, since we
 will stop when X - i >= K
 the final result is Sum(Probability(j)), j >= K, j<= N
 the naive implementation is below. But it exceeds time limit
 */
class Solution1 {
public:
    double new21Game(int N, int K, int W) {
        if (N >= K + W - 1) {
            return 1.0;
        }
        double probability = 1.0 / W;
        vector<double> dp(K + W, 0.0);
        dp[0] = 1.0;
        for (int i = 1; i < K + W; i++) {
            for (int j = 1; j <= W; j++) {
                if (i - j >= 0 && i - j < K) {
                    dp[i] += probability * dp[i - j];
                }
            }
        }
        
        double result = 0.0;
        for (int i = K; i <= N; i++) {
            result += dp[i];
        }
        return result;
    }
};
