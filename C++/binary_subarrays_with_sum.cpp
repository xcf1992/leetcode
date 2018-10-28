/*
 In an array A of 0s and 1s, how many non-empty subarrays have sum S?
 
 
 
 Example 1:
 
 Input: A = [1,0,1,0,1], S = 2
 Output: 4
 Explanation:
 The 4 subarrays are bolded below:
 [1,0,1,0,1]
 [1,0,1,0,1]
 [1,0,1,0,1]
 [1,0,1,0,1]
 
 
 Note:
 
 A.length <= 30000
 0 <= S <= A.length
 A[i] is either 0 or 1.

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
    int numSubarraysWithSum(vector<int>& A, int S) {
        int n = A.size();
        vector<int> rightSum(n + 1, 0);
        for (int i = n - 1; i >= 0; i--) {
            rightSum[i] = A[i] + rightSum[i + 1];
        }
        
        int result = 0;
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n + 1; j++) {
                if (rightSum[i] - rightSum[j] == S) {
                    result += 1;
                }
            }
        }
        return result;
    }
};

// time limit exceeded
class Solution1 {
public:
    int numSubarraysWithSum(vector<int>& A, int S) {
        int n = A.size();
        vector<int> rightSum(n + 1, 0);
        for (int i = n - 1; i >= 0; i--) {
            rightSum[i] = A[i] + rightSum[i + 1];
        }
        
        int result = 0;
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n + 1; j++) {
                if (rightSum[i] - rightSum[j] == S) {
                    result += 1;
                }
            }
        }
        return result;
    }
};
