/*
 922. Sort Array By Parity II
 Given an array A of non-negative integers,
 half of the integers in A are odd, and half of the integers are even.

 Sort the array so that whenever A[i] is odd, i is odd;
 and whenever A[i] is even, i is even.

 You may return any answer array that satisfies this condition.

 Example 1:

 Input: [4,2,5,7]
 Output: [4,5,2,7]
 Explanation: [4,7,2,5], [2,5,4,7], [2,7,4,5] would also have been accepted.


 Note:

 2 <= A.length <= 20000
 A.length % 2 == 0
 0 <= A[i] <= 1000
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
#include <numeric>
using namespace std;

class Solution {
public:
    vector<int> sortArrayByParityII(vector<int>& A) {
        int odd = 1;
        int even = 0;
        int n = A.size();
        while (odd < n and even < n) {
            while (odd < n and A[odd] % 2 == 1) {
                odd += 2;
            }
            while (even < n and A[even] % 2 == 0) {
                even += 2;
            }
            if (odd < n and even < n) {
                swap(A[odd], A[even]);
            }
        }
        return A;
    }
};