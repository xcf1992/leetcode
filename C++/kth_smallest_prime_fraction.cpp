/*
 A sorted list A contains 1, plus some number of primes.  Then, for every p < q in the list, we consider the fraction p/q.
 
 What is the K-th smallest fraction considered?  Return your answer as an array of ints, where answer[0] = p and answer[1] = q.
 
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
#include <stdio.h>
#include <map>
#include <numeric>
using namespace std;

/*
 when we put element into the pq, we just need to make sure
 1. we first put all the smallest elments, with A[0] / A[i]
 2. then for each poped item x, we put x.first + 1/ x.second, and we sure x.first / x.second or x.first / x.second + 1 already in or will be in the pq
 */
class Solution {
public:
    vector<int> kthSmallestPrimeFraction(vector<int>& A, int K) {
        auto cmp = [&A](auto& a, auto& b) {
            return A[a.first] * A[b.second] > A[a.second] * A[b.first];
        };
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
