/*
1089. Duplicate Zeros
Given a fixed length array arr of integers, duplicate each occurrence of zero, shifting the remaining elements to the right.

Note that elements beyond the length of the original array are not written.

Do the above modifications to the input array in place, do not return anything from your function.



Example 1:

Input: [1,0,2,3,0,4,5,0]
Output: null
Explanation: After calling your function, the input array is modified to: [1,0,0,2,3,0,0,4]
Example 2:

Input: [1,2,3]
Output: null
Explanation: After calling your function, the input array is modified to: [1,2,3]


Note:

1 <= arr.length <= 10000
0 <= arr[i] <= 9
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
    void duplicateZeros(vector<int>& arr) {
        int n = arr.size();
        int index = 0;
        for (int i = 0; i < n; ++i, ++index) {
            if (arr[i] == 0) {
                index += 1;
            }
        }
        index -= 1; // in case [1,0,2,3,0,4,5,0], after loop, index will be 11, minus 1 here so it will be the last available index

        for (int i = n - 1; i >= 0; --i) {
            if (index <= n - 1) {
                arr[index] = arr[i];
            }
            index -= 1;
            if (arr[i] == 0) {
                if (index <= n - 1) {
                    arr[index] = 0;
                }
                index -= 1;
            }
        }
    }
};

/*
Wrong Answer
Input
[8,4,5,0,0,0,0,7]
Output
[8,8,4,5,0,0,0,0]
Expected
[8,4,5,0,0,0,0,0]
*/
class Solution1 {
public:
    void duplicateZeros(vector<int>& arr) {
        int n = arr.size();
        if (n <= 1) {
            return;
        }

        int count = 0;
        int index = 0;
        while (index + count < n) {
            if (arr[index] == 0) {
                count += 1;
            }
            index += 1;
        }

        int right = n - 1;
        int left = n - count - 1;
        while (left >= 0 and count > 0) {
            if (arr[left] == 0) {
                arr[right] = 0;
                right -= 1;
                count -= 1;
            }
            arr[right] = arr[left];
            left -= 1;
            right -= 1;
        }
        return;
    }
};
