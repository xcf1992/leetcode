/*
https://leetcode.com/problems/put-marbles-in-bags/description/
2551. Put Marbles in Bags

You have k bags. You are given a 0-indexed integer array weights where weights[i] is the weight of the ith marble. You
are also given the integer k.

Divide the marbles into the k bags according to the following rules:

No bag is empty.
If the ith marble and jth marble are in a bag, then all marbles with an index between the ith and jth indices should
also be in that same bag. If a bag consists of all the marbles with an index from i to j inclusively, then the cost of
the bag is weights[i] + weights[j]. The score after distributing the marbles is the sum of the costs of all the k bags.

Return the difference between the maximum and minimum scores among marble distributions.



Example 1:

Input: weights = [1,3,5,1], k = 2
Output: 4
Explanation:
The distribution [1],[3,5,1] results in the minimal score of (1+1) + (3+1) = 6.
The distribution [1,3],[5,1], results in the maximal score of (1+3) + (5+1) = 10.
Thus, we return their difference 10 - 6 = 4.
Example 2:

Input: weights = [1, 3], k = 2
Output: 0
Explanation: The only distribution possible is [1],[3].
Since both the maximal and minimal score are the same, we return 0.


Constraints:

1 <= k <= weights.length <= 105
1 <= weights[i] <= 109
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
#include <climits>

using namespace std;

/*
Approach
First, there are two special cases: when k=1 or n=k, there is just one possible distribution. When k=1 we can do nothing
but put all marbles in one bag. When n=k, we can only put one marble in each bag. Since there is just one possible
distribution, the difference between the one with maximum score and the one with minimum score would obviously be 0.

Now let's think about the general case. Suppose there are n marbles and k bags. We can observe that regardless how we
put the marbles, the weight of the first marble and the last marble would always be counted. The score differs among
different distributions which depends on how we split the marbles in the middle.

Consider the marbles (I will just note the indices below): [0,1,2,...,n−1]. To split them into k different bags, we just
need to put k−1 bars in the gaps of the marbles. That being said, we have n−1 gaps, and we put k−1 bars there. When we
put a bar after i-th marble, the score of such distribution would increase by weights[i]+weights[i+1]

Taking n=10,k=3 as an example, One possible distribution is [0,1,2,∣3,4,5,6,7,∣8,9]. When we put a bar after marble 2,
the score increases by weights[2]+weights[3].

Hence, the problem turns into that, with n−1 gaps, and the score added after placing a bar after i-th marble is
weights[i]+weights[i+1], we want to find the minimum/maximum score after placing k−1 bars.

With this understanding, the solution is simple: record weights[i]+weights[i+1] for each 0≤i<n−1, sort them, select k−1
smallest/largest ones from them, and find the difference in score.
*/
class Solution {
public:
    long long putMarbles(vector<int>& weights, int k) {
        int n = weights.size();
        if (k == 1 || k == n) {
            return 0;
        }

        vector<long long> candidates;
        for (int i = 0; i < n - 1; i++) {
            candidates.push_back(weights[i] + weights[i + 1]);
        }
        sort(candidates.begin(), candidates.end());

        long long max_w = 0;
        long long min_w = 0;
        int cnt = candidates.size();
        for (int i = 0; i < k - 1; i++) {
            min_w += candidates[i];
            max_w += candidates[cnt - 1 - i];
        }
        return max_w - min_w;
    }
};