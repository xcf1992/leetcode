/*
 976. Largest Perimeter Triangle
 Given an array A of positive lengths,
 return the largest perimeter of a triangle with non-zero area,
 formed from 3 of these lengths.

 If it is impossible to form any triangle of non-zero area, return 0.

 Example 1:

 Input: [2,1,2]
 Output: 5
 Example 2:

 Input: [1,2,1]
 Output: 0
 Example 3:

 Input: [3,2,3,4]
 Output: 10
 Example 4:

 Input: [3,6,2,3]
 Output: 8


 Note:

 3 <= A.length <= 10000
 1 <= A[i] <= 10^6
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

/*
 First we can sort the array in non-increasing order.
 So, the first element will be maximum and the last will be minimum.
 Now if the first 3 elements of this sorted array forms a triangle then it will be the maximum perimeter triangle,
 as for all other combination the sum of elements(i.e. the perimeter of that triangle) will be = b >= c).

 a, b, c can not form a triangle, so a >= b + c.
 As, b and c = c+d (if we drop b and take d)
 or a >= b+d (if we drop c and take d).
 So, we have to drop a and pick up d.

 Again same set of analysis for b, c and d.
 We can continue this till last and whenever we find a triangle forming triple then we can stop checking,
 as this triple gives maximum perimeter.
 Hence, if arr[i] < arr[i+1] + arr[i+2] (0 <= i <= n-3)in the sorted array then arr[i], arr[i+1] and arr[i+2] forms a triangle.
 Below is the simple implementation of this concept:
*/
class Solution {
public:
    int largestPerimeter(vector<int>& A) {
        int n = A.size();
        if (n < 3) {
            return 0;
        }

        sort(A.begin(), A.end());
        for (int i = n - 1; i >= 2; --i) if (A[i] < A[i - 1] + A[i - 2]) {
            return A[i] + A[i - 1] + A[i - 2];
        }
        return 0;
    }
};

// TLE
class Solution1 {
public:
    int largestPerimeter(vector<int>& A) {
        int n = A.size();
        if (n < 3) {
            return 0;
        }

        int result = 0;
        sort(A.begin(), A.end());
        for (int i = 0; i < n; i++) {
            int l1 = A[i];
            for (int j = i + 1; j < n; j++) {
                int l2 = A[j];
                for (int k = j + 1; k < n; k++) {
                    int l3 = A[k];
                    if (l1 + l2 <= l3) {
                        break;
                    }
                    result = max(result, l1 + l2 + l3);
                 }
            }
        }
        return result;
    }
};
