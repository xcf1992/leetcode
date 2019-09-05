/*
 Given an array A of non-negative integers, return an array consisting of all the even elements of A, followed by all the odd elements of A.

 You may return any answer array that satisfies this condition.



 Example 1:

 Input: [3,1,2,4]
 Output: [2,4,3,1]
 The outputs [4,2,3,1], [2,4,1,3], and [4,2,1,3] would also be accepted.


 Note:

 1 <= A.length <= 5000
 0 <= A[i] <= 5000
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
    vector<int> sortArrayByParity(vector<int>& A) {
        int even = 0;
        int odd = A.size() - 1;
        while (even < odd) {
            while (A[even] % 2 == 0) {
                even += 1;
            }
            while (A[odd] % 2 == 1) {
                odd -= 1;
            }
            if (even < odd) {
                swap(A[even], A[odd]);
            }
        }
        return A;
    }
};
