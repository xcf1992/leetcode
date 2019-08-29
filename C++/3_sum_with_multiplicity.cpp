/*
923. 3Sum With Multiplicity
Given an integer array A, and an integer target,
return the number of tuples i, j, k
such that i < j < k and A[i] + A[j] + A[k] == target.

As the answer can be very large, return it modulo 10^9 + 7.

Example 1:

Input: A = [1,1,2,2,3,3,4,4,5,5], target = 8
Output: 20
Explanation:
Enumerating by the values (A[i], A[j], A[k]):
(1, 2, 5) occurs 8 times;
(1, 3, 4) occurs 8 times;
(2, 2, 4) occurs 2 times;
(2, 3, 3) occurs 2 times.
Example 2:

Input: A = [1,1,2,2,2,2], target = 5
Output: 12
Explanation:
A[i] = 1, A[j] = A[k] = 2 occurs 12 times:
We choose one 1 from [1,1] in 2 ways,
and two 2s from [2,2,2,2] in 6 ways.


Note:

3 <= A.length <= 3000
0 <= A[i] <= 100
0 <= target <= 300
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

class Solution {
public:
    int threeSumMulti(vector<int>& A, int target) {
        int MOD = 1e9 + 7;
        unordered_map<int, long> count;
        for (int a : A) {
            count[a] += 1;
        }

        long result = 0;
        for (auto it : count) {
            for (auto it2 : count) {
                int i = it.first;
                int j = it2.first;
                int k = target - i - j;
                if (count.find(k) == count.end()) {
                    continue;
                }

                if (i == j and j == k) {
                    result += count[i] * (count[i] - 1) * (count[i] - 2) / 6;
                }
                else if (i == j and j != k) {
                    result += count[i] * (count[i] - 1) * count[k] / 2;
                }
                else if (i < j and j < k) {
                    result += count[i] * count[j] * count[k];
                }
                result %= MOD;
            }
        }
        return result % MOD;
    }
};

class Solution1 {
private:
    int MOD = 1e9 + 7;
public:
    int threeSumMulti(vector<int>& A, int target) {
        sort(A.begin(), A.end()); // we only need to find 3 different indices, so we can sort without worrying about the actual order of each number's indices
        long result = 0;
        int n = A.size();
        for (int i = 0; i < n; i++) {
            int needed = target - A[i];
            int left = i + 1;
            int right = n - 1;
            while (left < right) {
                if (A[left] + A[right] == needed) {
                    if (A[left] != A[right]) {
                        int lCount = 1;
                        int rCount = 1;
                        while (left + 1 < right and A[left + 1] == A[left]) {
                            left += 1;
                            lCount += 1;
                        }
                        while (right - 1 > left and A[right - 1] == A[right]) {
                            right -= 1;
                            rCount += 1;
                        }
                        result += lCount * rCount;
                        result %= MOD;
                        right -= 1;
                        left += 1;
                    }
                    else {
                        result += (right - left + 1) * (right - left) / 2;
                        result %= MOD;
                        break;
                    }
                }
                else if (A[left] + A[right] < needed) {
                    left += 1;
                }
                else {
                    right -= 1;
                }
            }
        }
        return result;
    }
};
