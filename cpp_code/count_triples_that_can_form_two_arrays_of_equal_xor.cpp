/*
1442. Count Triplets That Can Form Two Arrays of Equal XOR
https://leetcode.com/problems/count-triplets-that-can-form-two-arrays-of-equal-xor/

Given an array of integers arr.
We want to select three indices i, j and k where (0 <= i < j <= k < arr.length).

Let's define a and b as follows:
a = arr[i] ^ arr[i + 1] ^ ... ^ arr[j - 1]
b = arr[j] ^ arr[j + 1] ^ ... ^ arr[k]
Note that ^ denotes the bitwise-xor operation.

Return the number of triplets (i, j and k) Where a == b.

Example 1:
Input: arr = [2,3,1,6,7]
Output: 4
Explanation: The triplets are (0,1,2), (0,2,2), (2,3,4) and (2,4,4)

Example 2:
Input: arr = [1,1,1,1,1]
Output: 10

Example 3:
Input: arr = [2,3]
Output: 0

Example 4:
Input: arr = [1,3,5,7,9]
Output: 3

Example 5:
Input: arr = [7,11,12,9,5,2,7,17,22]
Output: 8

Constraints:
1 <= arr.length <= 300
1 <= arr[i] <= 10^8
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

/*
a = arr[i] ^ arr[i + 1] ^ ... ^ arr[j - 1]
b = arr[j] ^ arr[j + 1] ^ ... ^ arr[k]

Assume a == b, thus
a ^ a = b ^ a, thus
0 = b ^ a, thus
arr[i] ^ arr[i + 1] ^ ... ^ arr[j - 1] ^ arr[j] ^ arr[j + 1] ^ ... ^ arr[k] = 0
prefix[k+1] = prefix[i]

We only need to find out how many pair (i, k) of prefix value are equal.
So we can calculate the prefix array first,
then brute force count the pair.

Because we once we determine the pair (i,k),
j can be any number that i < j <= k,
so we need to plus k - i - 1 to the result res.

Time O(N^2)
Space O(N)
Space O(1) if changing the input
*/
class Solution {
public:
    int countTriplets(vector<int>& A) {
        A.insert(A.begin(), 0);
        int n = A.size();
        int res = 0;
        for (int i = 1; i < n; ++i) {
            A[i] ^= A[i - 1];
        }

        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                if (A[i] == A[j]) {
                    res += j - i - 1;
                }
            }
        }
        return res;
    }
};

/*
The problem now is, given an array,
find out the sum of index distance with A[i] = A[j].
Let me know if there is a duplicate problem on LeetCode,
so I can attach a link to help explain.

Basicly, for the same value in the array,
we need to count the frequncy and the total value at the same time.

Time O(N)
Space O(N)
Space O(1) if changing the input

C++

int countTriplets(vector<int>& A) {
    A.insert(A.begin(), 0);
    int n = A.size(), res = 0;
    for (int i = 1; i < n; ++i) {
        A[i] ^= A[i - 1];
    }

    unordered_map<int, int> count, total;
    for (int i = 0; i < n; ++i) {
        count[A[i]]++;
        res += count[A[i]] * (i - 1) - total[A[i]];
        total[A[i]] += i;
    }
    return res;
}
*/
