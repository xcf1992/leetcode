/*
 Given an array A of positive lengths, return the largest perimeter of a triangle with non-zero area, formed from 3 of these lengths.
 
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

class Solution {
public:
    int largestPerimeter(vector<int>& A) {
        int n = A.size();
        if (n < 3) {
            return 0;
        }
        
        int result = 0;
        sort(A.begin(), A.end());
        for (int i = n - 1; i >= 2; i--) {
            if (A[i] < A[i - 1] + A[i - 2]) {
                result = max(result, A[i] + A[i - 1] + A[i - 2]);
            }
        }
        return result;
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
