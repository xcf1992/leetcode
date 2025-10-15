/*
1534. Count Good Triplets
https://leetcode.com/problems/count-good-triplets/

Given an array of integers arr, and three integers a, b and c.
You need to find the number of good triplets.

A triplet (arr[i], arr[j], arr[k]) is good if the following conditions are true:
0 <= i < j < k < arr.length
|arr[i] - arr[j]| <= a
|arr[j] - arr[k]| <= b
|arr[i] - arr[k]| <= c
Where |x| denotes the absolute value of x.

Return the number of good triplets.

Example 1:
Input: arr = [3,0,1,1,9,7], a = 7, b = 2, c = 3
Output: 4
Explanation: There are 4 good triplets: [(3,0,1), (3,0,1), (3,1,1), (0,1,1)].

Example 2:
Input: arr = [1,1,2,2,3], a = 0, b = 0, c = 1
Output: 0
Explanation: No triplet satisfies all conditions.

Constraints:
3 <= arr.length <= 100
0 <= arr[i] <= 1000
0 <= a, b, c <= 1000
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
/*
Intuition
If need to win k times with k >= n-1, it needs to win all elements.
So it will be max(A)

Explanation
cur is the current winner, wich is the current biggest element.
win is the number of games it has won.
If max(A) conpetes, it will be the winner.

Complexity
Time O(N)
Space O(1)
*/
class Solution {
public:
    int countGoodTriplets(vector<int>& arr, int a, int b, int c) {
        const int n = arr.size();
        int ans = 0;
        for (int i = 0; i < n - 2; i++) {
            for (int j = i + 1; j < n - 1 ; j++) {
                for (int k = j + 1; k < n && abs(arr[i] - arr[j]) <= a; k++) {
                    if (abs(arr[j] -  arr[k]) <= b and abs(arr[i] -  arr[k]) <= c) {
                        ans++;
                    }
                }
            }
        }
        return ans;
    }
};