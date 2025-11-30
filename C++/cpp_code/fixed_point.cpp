/*
 1064. Fixed Point
 Given an array A of distinct integers sorted in ascending order,
 return the smallest index i that satisfies A[i] == i.  Return -1 if no such i exists.

 Example 1:

 Input: [-10,-5,0,3,7]
 Output: 3
 Explanation:
 For the given array, A[0] = -10, A[1] = -5, A[2] = 0, A[3] = 3, thus the output is 3.
 Example 2:

 Input: [0,2,5,8,17]
 Output: 0
 Explanation:
 A[0] = 0, thus the output is 0.
 Example 3:

 Input: [-10,-5,3,4,7,9]
 Output: -1
 Explanation:
 There is no such i that A[i] = i, thus the output is -1.


 Note:

 1 <= A.length < 10^4
 -10^9 <= A[i] <= 10^9
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
#include <set>
#include <numeric>
using namespace std;

/*
Test Cases
It said that "return the smallest index i that satisfies A[i] == i".
Many solution just "return an whatever index that satisfies A[i] == i".
Tough it can get accepted.

Update
I used to return any index that A[i] == i.
It got a false accepted due to weak test cases.
Thanks to @dibdidib for reminding me and now I fixed it.
*/

class Solution {
public:
    int fixedPoint(vector<int>& A) {
        int left = 0;
        int right = A.size() - 1;
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (A[mid] < mid) {
                left = mid + 1;
            } else {
                right = mid;
            }
        }
        return A[left] == left ? left : -1;
    }
};