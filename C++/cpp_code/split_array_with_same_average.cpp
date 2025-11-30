/*
805. Split Array With Same Average

In a given integer array A,
we must move every element of A to either list B or list C.
(B and C initially start empty.)

Return true if and only if after such a move,
it is possible that the average value of B is equal to the average value of C,
and B and C are both non-empty.

Example :
Input:
[1,2,3,4,5,6,7,8]
Output: true
Explanation: We can split the array into [1,4,5,8] and [2,3,6,7], and both of them have the average of 4.5.

Note:
The length of A will be in the range [1, 30].
A[i] will be in the range of [0, 10000].
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
/*
we can know that AV_a == AV_b == AV_c
if s1/n1 == s2/n2 then s1/n1 = s2/n2 = (s1+s2)/(n1+n2).

To find if
1 element with sum = 1 * avg or
2 elements with sum = 2 * avg or
i elements with sum = i * avg

The size of smaller list between B and C will be less than N/2+1, so 0 < i < N/2+1

The part if ((sum * i) % len == 0 is a screening to avoid unnecessary calculations because A is an array of integers,
for a subarray of length i to have equal average as A,
the sum of this subarray is sum(A)/len(A) * i,
and this needs to be an integer number,
which equivalently means ((sum(A) * i) % len(A) == 0.

The second part is to call the recursive function find(parameters) to see if a subarray of length i will have equal
average as A.
*/
class Solution {
private:
    bool find(int target, int count, int sum, int index, vector<int>& A) {
        if (index + count > A.size()) {
            return false;
        }
        if (count == 0) {
            return sum == target;
        }
        // if we pick current number than the left num need minus 1 and add value to current sum
        return find(target, count - 1, sum + A[index], index + 1, A) or find(target, count, sum, index + 1, A);
    }

public:
    bool splitArraySameAverage(vector<int>& A) {
        int n = A.size();
        int sum = accumulate(A.begin(), A.end(), 0);
        double avrg = sum / (double)n;
        int count = 0;
        for (int a : A) {
            if (a >= avrg) {
                count += 1;
            }
        }
        if (count < 2) {
            return false;
        }

        for (int i = 1; i <= n / 2; i++) {
            // we need to check if we can have i number from A that have average sum * i / n
            if ((sum * i) % n == 0 and find(sum * i / n, i, 0, 0, A)) {
                return true;
            }
        }
        return false;
    }
};