/*
823. Binary Trees With Factors
Given an array of unique integers, each integer is strictly greater than 1.

We make a binary tree using these integers and each number may be used for any number of times.

Each non-leaf node's value should be equal to the product of the values of it's children.

How many binary trees can we make?
Return the answer modulo 10 ** 9 + 7.

Example 1:

Input: A = [2, 4]
Output: 3
Explanation: We can make these trees: [2], [4], [4, 2, 2]
Example 2:

Input: A = [2, 4, 5, 10]
Output: 7
Explanation: We can make these trees: [2], [4], [5], [10], [4, 2, 2], [10, 2, 5], [10, 5, 2].


Note:

1 <= A.length <= 1000.
2 <= A[i] <= 10 ^ 9.
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

class Solution {
private:
    int mod = 1e9 + 7;

    void buildTrees(vector<int>& A, unordered_map<int, long>& count, int index) {
        count[A[index]] += 1;
        for (int i = 0; i < index; i++) {
            if (A[index] % A[i] == 0 and count.find(A[index] / A[i]) != count.end()) {
                count[A[index]] += count[A[i]] * count[A[index] / A[i]];
                count[A[index]] %= mod;
            }
        }
    }
public:
    int numFactoredBinaryTrees(vector<int>& A) {
        sort(A.begin(), A.end());
        unordered_map<int, long> count;
        for (int i = 0; i < A.size(); i++) {
            buildTrees(A, count, i);
        }

        int result = 0;
        for (auto it = count.begin(); it != count.end(); it++) {
            result += it -> second;
            result %= mod;
        }
        return result;
    }
};
