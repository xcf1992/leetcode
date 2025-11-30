/*
786. K-th Smallest Prime Fraction

A sorted list A contains 1, plus some number of primes.
Then, for every p < q in the list, we consider the fraction p/q.

What is the K-th smallest fraction considered?
Return your answer as an array of ints, where answer[0] = p and answer[1] = q.

Examples:
Input: A = [1, 2, 3, 5], K = 3
Output: [2, 5]
Explanation:
The fractions to be considered in sorted order are:
1/5, 1/3, 2/5, 1/2, 3/5, 2/3.
The third fraction is 2/5.

Input: A = [1, 7], K = 1
Output: [1, 7]

Note:
A will have length between 2 and 2000.
Each A[i] will be between 1 and 30000.
K will be between 1 and A.length * (A.length - 1) / 2.
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
#include <map>
#include <numeric>
using namespace std;
/*
Intuition

Let under(x) be the number of fractions below x.
It's an increasing function on x, so we can binary search for the correct answer.

Algorithm

Let's binary search for x such that there are exactly K fractions below x.
At the same time, we'll record the largest such fraction seen that was still below x.

Our binary search follows a similar template as other binary searches:
we have some interval [lo, hi] and a midpoint mi = (lo + hi) / 2.0.
If the number of fractions below mi is less than K,
then we will now consider the interval [mi, hi];
otherwise we will consider the interval [lo, mi].

Our under(x) function has two objectives:
to return the number of fractions below x,
as well as the maximum such fraction below x.
To count this, we will use a sliding window approach:
for each primes[j], we'll find the largest i so that primes[i] / primes[j] < x.
These is are necessarily increasing as j (and primes[j]) increases, so this check is linear.
*/
class Solution {
    // binary search
private:
    vector<int> under(double limit, vector<int>& A) {
        int numer = 0;
        int denom = 1;
        int count = 0;
        int i = -1;
        int n = A.size();
        for (int j = 1; j < n; ++j) {
            // For each j, find the largest i so that primes[i] / primes[j] < x
            // It has to be at least as big as the previous i, so reuse it ("two pointer")
            while (A[i + 1] < A[j] * limit) {
                i += 1;
            }
            count += i + 1;
            // There are i+1 fractions: (primes[0], primes[j]),
            // (primes[1], primes[j]), ..., (primes[i], primes[j])
            if (i >= 0 and numer * A[j] < denom * A[i]) {
                numer = A[i];
                denom = A[j];
            }
        }
        return {count, numer, denom};
    }

public:
    vector<int> kthSmallestPrimeFraction(vector<int>& A, int K) {
        double left = 0;
        double right = 1;
        vector<int> result({0, 1});
        while (right - left > 1e-9) {
            double mid = left + (right - left) / 2;
            vector<int> smaller = under(mid, A);
            if (smaller[0] < K) {
                left = mid;
            } else {
                right = mid;
                result[0] = smaller[1];
                result[1] = smaller[2];
            }
        }
        return result;
    }
};

/*
 when we put element into the pq, we just need to make sure
 1. we first put all the smallest elments, with A[0] / A[i]
 2. then for each poped item x, we put x.first + 1/ x.second,
    and we sure x.first / x.second or x.first / x.second + 1 already in or will be in the pq
*/
class Solution1 {
    // 6.61%
public:
    vector<int> kthSmallestPrimeFraction(vector<int>& A, int K) {
        auto cmp = [&A](auto& a, auto& b) { return A[a.first] * A[b.second] > A[a.second] * A[b.first]; };
        priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(cmp)> pq(cmp);

        for (int i = 1; i < A.size(); i++) {
            pq.push({0, i});
        }

        int count = 1;
        while (count < K) {
            count += 1;
            pair<int, int> cur = pq.top();
            pq.pop();

            if (cur.first + 1 < cur.second) {
                pq.push({cur.first + 1, cur.second});
            }
        }
        return {A[pq.top().first], A[pq.top().second]};
    }
};