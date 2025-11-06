/*
898. Bitwise ORs of Subarrays

Given an integer array arr, return the number of distinct bitwise ORs of all the non-empty subarrays of arr.

The bitwise OR of a subarray is the bitwise OR of each integer in the subarray.
The bitwise OR of a subarray of one integer is that integer.

A subarray is a contiguous non-empty sequence of elements within an array.

Example 1:
Input: [0]
Output: 1
Explanation:
There is only one possible result: 0.

Example 2:
Input: [1,1,2]
Output: 3
Explanation:
The possible subarrays are [1], [1], [2], [1, 1], [1, 2], [1, 1, 2].
These yield the results 1, 1, 2, 1, 3, 3.
There are 3 unique values, so the answer is 3.

Example 3:
Input: [1,2,4]
Output: 6
Explanation:
The possible results are 1, 2, 3, 4, 6, and 7.

Note:
1 <= A.length <= 50000
0 <= A[i] <= 10^9
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
    // a better way to write the same solution
public:
    int subarrayBitwiseORs(vector<int> arr) {
        unordered_set<int> res;
        unordered_set<int> cur;
        for (int i : arr) {
            unordered_set<int> cur2;
            cur2.insert(i);
            for (int j : cur) {
                cur2.insert(i | j);
            }

            cur = cur2;
            for (int j : cur) {
                res.insert(j);
            }
        }
        return res.size();
    }
};

class Solution1 {
public:
    int subarrayBitwiseORs(vector<int>& A) {
        unordered_set<int> cur, result;
        cur.insert(A[0]);
        result.insert(A[0]);
        for (int i = 1; i < A.size(); i++) {
            unordered_set<int> cur2;
            cur2.insert(A[i]);
            result.insert(A[i]);
            for (int num : cur) {
                cur2.insert(num | A[i]);
                result.insert(num | A[i]);
            }
            cur = cur2;
        }
        return result.size();
    }
};