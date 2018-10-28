/*
 For some fixed N, an array A is beautiful if it is a permutation of the integers 1, 2, ..., N, such that:
 
 For every i < j, there is no k with i < k < j such that A[k] * 2 = A[i] + A[j].
 
 Given N, return any beautiful array A.  (It is guaranteed that one exists.)
 
 
 
 Example 1:
 
 Input: 4
 Output: [2,1,4,3]
 Example 2:
 
 Input: 5
 Output: [3,1,2,5,4]
 
 
 Note:
 
 1 <= N <= 1000
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
 Intuition
 
 This answer is quite unintuitive.
 
 First, notice that the condition is equivalent to saying that A has no arithmetic subsequence. We'll use the term "arithmetic-free" interchangeably with "beautiful".
 
 One way is to guess that we should divide and conquer. One reason for this is that the condition is linear, so if the condition is satisfied by variables taking on values (1, 2, ..., n), it is satisfied by those variables taking on values (a + b, a + 2*b, a + 3*b, ..., a + (n-1)*b) instead.
 
 If we perform a divide and conquer, then we have two parts left and right, such that each part is arithmetic-free, and we only want that a triple from both parts is not arithmetic. Looking at the conditions:
 
 2*A[k] = A[i] + A[j]
 (i < k < j), i from left, j from right
 we can guess that because the left hand side 2*A[k] is even, we can choose left to have all odd elements, and right to have all even elements.
 
 Another way we could arrive at this is to try to place a number in the middle, like 5. We will have 4 and 6 say, to the left of 5, and 7 to the right of 6, etc. We see that in general, odd numbers move towards one direction and even numbers towards another direction.
 
 One final way we could arrive at this is to inspect possible answers arrived at by brute force. On experimentation, we see that many answers have all the odd elements to one side, and all the even elements to the other side, with only minor variation.
 
 Algorithm
 
 Looking at the elements 1, 2, ..., N, there are (N+1) / 2 odd numbers and N / 2 even numbers.
 
 We solve for elements 1, 2, ..., (N+1) / 2 and map these numbers onto 1, 3, 5, .... Similarly, we solve for elements 1, 2, ..., N/2 and map these numbers onto 2, 4, 6, ....
 
 We can compose these solutions by concatenating them, since an arithmetic sequence never starts and ends with elements of different parity.
 
 We memoize the result to arrive at the answer quicker.
 */
class Solution {
private:
    vector<int> getArray(int N, unordered_map<int, vector<int>>& memo) {
        if (N == 1) {
            return {1};
        }
        
        if (memo.find(N) != memo.end()) {
            return memo[N];
        }
        
        vector<int> beautifulArray(N, 0);
        int i = 0;
        for (int num : getArray((N + 1) / 2, memo)) {
            beautifulArray[i++] = 2 * num - 1;
        }
        for (int num : getArray(N / 2, memo)) {
            beautifulArray[i++] = 2 * num;
        }
        memo[N] = beautifulArray;
        return beautifulArray;
    }
public:
    vector<int> beautifulArray(int N) {
        unordered_map<int, vector<int>> memo;
        return getArray(N, memo);
    }
};
