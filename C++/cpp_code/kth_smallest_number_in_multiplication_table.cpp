/*
668. Kth Smallest Number in Multiplication Table
https://leetcode.com/problems/kth-smallest-number-in-multiplication-table/

Nearly every one have used the Multiplication Table.
But could you find out the k-th smallest number quickly from the multiplication table?

Given the height m and the length n of a m * n Multiplication Table, and a positive integer k,
you need to return the k-th smallest number in this table.

Example 1:
Input: m = 3, n = 3, k = 5
Output:
Explanation:
The Multiplication Table:
1   2   3
2   4   6
3   6   9
The 5-th smallest number is 3 (1, 2, 2, 3, 3).

Example 2:
Input: m = 2, n = 3, k = 6
Output:
Explanation:
The Multiplication Table:
1    2    3
2    4    6
The 6-th smallest number is 6 (1, 2, 2, 3, 4, 6).

Note:
The m and n will be in the range [1, 30000].
The k will be in the range [1, m * n]
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
using namespace std;

class Solution {
private:
    int getCount(int m, int n, int limit) {
        int result = 0;
        for (int i = 1; i <= m; i++) {
            /*
             * count of number <= mid
             * each row is like 1*i, 2*i, 3*i...n*i
             * so the count of number <= m would be mid / i
             */
            result += min(limit / i, n);
        }
        return result;
    }

public:
    int findKthNumber(int m, int n, int k) {
        int left = 1;
        int right = m * n;
        while (left < right) {
            int mid = left + (right - left) / 2;
            int count = getCount(m, n, mid);
            if (count >= k) {
                right = mid;
            } else {
                left = mid + 1;
            }
        }
        return left;
    }
};
