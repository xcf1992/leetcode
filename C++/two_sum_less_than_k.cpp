/*
1099. Two Sum Less Than K
Given an array A of integers and integer K,
return the maximum S such that there exists i < j with A[i] + A[j] = S and S < K.
If no i, j exist satisfying this equation, return -1.

Example 1:

Input: A = [34,23,1,24,75,33,54,8], K = 60
Output: 58
Explanation:
We can use 34 and 24 to sum 58 which is less than 60.
Example 2:

Input: A = [10,20,30], K = 15
Output: -1
Explanation:
In this case it's not possible to get a pair sum less that 15.


Note:

1 <= A.length <= 100
1 <= A[i] <= 1000
1 <= K <= 2000
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
#include <set>
#include <numeric>
using namespace std;

class Solution {
public:
    int twoSumLessThanK(vector<int>& A, int K) {
        sort(A.begin(), A.end());

        int i = 0;
        int j = A.size() - 1;
        int result = -1;
        while (i < j) {
            if (A[i] + A[j] < K) {
                result = max(result, A[i] + A[j]);
                i++;
            }
            else {
                j--;
            }
        }
        return result;
    }
};

class Solution1 { //40%
public:
    int twoSumLessThanK(vector<int>& A, int K) {
        set<int> nums;
        int result = -1;
        for (int a : A) {
            int target = K - a;
            auto it = nums.lower_bound(target);
            if (it != nums.begin()) {
                result = max(result, *prev(it) + a);
            }
            nums.insert(a);
        }
        return result;
    }
};
