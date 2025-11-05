/*
930. Binary Subarrays With Sum
In an array A of 0s and 1s, how many non-empty subarrays have sum S?

Example 1:
Input: A = [1,0,1,0,1], S = 2
Output: 4
Explanation:
The 4 subarrays are bolded below:
[1,0,1,0,1]
[1,0,1,0,1]
[1,0,1,0,1]
[1,0,1,0,1]

Note:
A.length <= 30000
0 <= S <= A.length
A[i] is either 0 or 1.
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
another solution:
Intuition

Let P[i] = A[0] + A[1] + ... + A[i-1].
Then P[j+1] - P[i] = A[i] + A[i+1] + ... + A[j],
the sum of the subarray [i, j].

Hence, we are looking for the number of i < j with P[j] - P[i] = S.

Algorithm

For each j, let's count the number of i with P[j] = P[i] + S.
This is analogous to counting the number of subarrays ending in j with sum S.

It comes down to counting how many P[i] + S we've seen before.
We can keep this count on the side to help us find the final answer.

the key point is to count the number of one between each 1
*/
class Solution {
public:
    int numSubarraysWithSum(vector<int> &A, int S) {
        int curSum = 0;
        int result = 0;
        unordered_map<int, int> count;
        count[0] = 1;
        for (int num: A) {
            curSum += num;
            result += count[curSum - S];
            count[curSum] += 1;
        }
        return result;
    }
};

class Solution1 {
public:
    int numSubarraysWithSum(vector<int> &A, int S) {
        int n = A.size();
        if (S == 0) {
            int result = 0;
            int lastOne = -1;
            for (int i = 0; i < n; i++) {
                if (A[i] == 1) {
                    int count = i - lastOne - 1;
                    result += (count + 1) * count / 2;
                    lastOne = i;
                }
            }
            int count = n - 1 - lastOne;
            return result + (count + 1) * count / 2;
        }
        vector<int> onePos;
        onePos.push_back(-1);
        for (int i = 0; i < A.size(); i++) {
            if (A[i] == 1) {
                onePos.push_back(i);
            }
        }
        onePos.push_back(A.size());

        int result = 0;
        for (int i = 1; i < onePos.size() - 1; i++) {
            int j = i + S - 1;
            if (j < onePos.size() - 1) {
                result += (onePos[i] - onePos[i - 1]) * (onePos[j + 1] - onePos[j]);
            } else {
                break;
            }
        }
        return result;
    }
};

// time limit exceeded
class Solution1 {
public:
    int numSubarraysWithSum(vector<int> &A, int S) {
        int n = A.size();
        vector<int> rightSum(n + 1, 0);
        for (int i = n - 1; i >= 0; i--) {
            rightSum[i] = A[i] + rightSum[i + 1];
        }

        int result = 0;
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n + 1; j++) {
                if (rightSum[i] - rightSum[j] == S) {
                    result += 1;
                }
            }
        }
        return result;
    }
};