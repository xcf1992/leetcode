/*
1073. Adding Two Negabinary Numbers
Given two numbers arr1 and arr2 in base -2, return the result of adding them together.

Each number is given in array format:  as an array of 0s and 1s, from most significant bit to least significant bit.  For example, arr = [1,1,0,1] represents the number (-2)^3 + (-2)^2 + (-2)^0 = -3.  A number arr in array format is also guaranteed to have no leading zeros: either arr == [0] or arr[0] == 1.

Return the result of adding arr1 and arr2 in the same format: as an array of 0s and 1s with no leading zeros.

 

Example 1:

Input: arr1 = [1,1,1,1,1], arr2 = [1,0,1]
Output: [1,0,0,0,0]
Explanation: arr1 represents 11, arr2 represents 5, the output represents 16.
 

Note:

1 <= arr1.length <= 1000
1 <= arr2.length <= 1000
arr1 and arr2 have no leading zeros
arr1[i] is 0 or 1
arr2[i] is 0 or 1
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
using namespace std;

class Solution {
public:
    vector<int> addNegabinary(vector<int>& arr1, vector<int>& arr2) {
        vector<int> result;
        int n1 = arr1.size();
        int n2 = arr2.size();
        int add = 0;
        int p1 = n1 - 1;
        int p2 = n2 - 1;
        while (p1 >= 0 or p2 >= 0 or add != 0) {
            if (p1 >= 0) {
                add += arr1[p1--];
            }
            if (p2 >= 0) {
                add += arr2[p2--];
            }

            result.push_back(add & 1);
            add = -(add >> 1);
        }

        while (result.size() > 1 and result.back() == 0) {
            result.pop_back();
        }
        reverse(result.begin(), result.end());
        return result;
    }
};
