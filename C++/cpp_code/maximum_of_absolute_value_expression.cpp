/*
1131. Maximum of Absolute Value Expression

Given two arrays of integers with equal lengths, return the maximum value of:
|arr1[i] - arr1[j]| + |arr2[i] - arr2[j]| + |i - j|
where the maximum is taken over all 0 <= i, j < arr1.length.

Example 1:
Input: arr1 = [1,2,3,4], arr2 = [-1,4,5,6]
Output: 13

Example 2:
Input: arr1 = [1,-2,-5,0,10], arr2 = [0,-2,-1,-7,-4]
Output: 20

Constraints:
2 <= arr1.length == arr2.length <= 40000
-10^6 <= arr1[i], arr2[i] <= 10^6
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
#include "extra_data_types.hpp"
using namespace std;
/*
https://leetcode.com/problems/maximum-of-absolute-value-expression/discuss/340070/topic
|a-b|可以看成是 Math.max(a-b,b-a)；

先将|arr1[i] - arr1[j]| + |arr2[i] - arr2[j]| + |i - j|写成|a1 - a2| + |b1 - b2| + |i1 - i2|， 以方便观看

我们将按索引顺序遍历数组，那么 |i - j|实际就是(i - j)

|a1 - a2| + |b1 - b2| + |i1 - i2|可以写成以下4个算式的最大值：

(a1 - a2) + (b1 - b2) + (i1 - i2)
(a1 - a2) + (b2 - b1) + (i1 - i2)
(a2 - a1) + (b1 - b2) + (i1 - i2)
(a2 - a1) + (b2 - b1) + (i1 - i2)
也可以写成:

(+a1 + b1 + i1) - (+a2 + b2 + i2)
(+a1 - b1 + i1) - (+a2 - b2 + i2)
(-a1 + b1 + i1) - (-a2 + b2 + i2)
(-a1 - b1 + i1) - (-a2 - b2 + i2)
a1,b1 / b1,b2对应的符号分别是
+,+
+,-
-,+
-,-
因此只需要遍历4中符号，然后取最大值。
*/
class Solution {
public:
    int maxAbsValExpr(vector<int>& arr1, vector<int>& arr2) {
        int n = arr1.size();
        int result = INT_MIN;
        for (int a = -1; a <= 1; a += 2) {
            for (int b = -1; b <= 1; b += 2) {
                int curMax = INT_MIN;
                int curMin = INT_MAX;
                for (int i = 0; i < n; ++i) {
                    int cur = arr1[i] * a + arr2[i] * b + i;
                    curMin = min(curMin, cur);
                    curMax = max(curMax, cur);
                    result = max(result, curMax - curMin);
                }
            }
        }
        return result;
    }
};
