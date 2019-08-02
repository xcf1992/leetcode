/*
 960. Delete Columns to Make Sorted III
 We are given an array A of N lowercase letter strings, all of the same length.

 Now, we may choose any set of deletion indices, and for each string, we delete all the characters in those indices.

 For example, if we have an array A = ["babca","bbazb"] and deletion indices {0, 1, 4},
 then the final array after deletions is ["bc","az"].

 Suppose we chose a set of deletion indices D such that after deletions,
 the final array has every element (row) in lexicographic order.

 For clarity, A[0] is in lexicographic order (ie. A[0][0] <= A[0][1] <= ... <= A[0][A[0].length - 1]),
 A[1] is in lexicographic order (ie. A[1][0] <= A[1][1] <= ... <= A[1][A[1].length - 1]), and so on.

 Return the minimum possible value of D.length.

 Example 1:

 Input: ["babca","bbazb"]
 Output: 3
 Explanation: After deleting columns 0, 1, and 4, the final array is A = ["bc", "az"].
 Both these rows are individually in lexicographic order (ie. A[0][0] <= A[0][1] and A[1][0] <= A[1][1]).
 Note that A[0] > A[1] - the array A isn't necessarily in lexicographic order.
 Example 2:

 Input: ["edcba"]
 Output: 4
 Explanation: If we delete less than 4 columns, the only row won't be lexicographically sorted.
 Example 3:

 Input: ["ghi","def","abc"]
 Output: 0
 Explanation: All rows are already lexicographically sorted.


 Note:

 1 <= A.length <= 100
 1 <= A[i].length <= 100
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
 Take n cols as n elements, so we have an array of n elements.
 => The final array has every row in lexicographic order.
 => The elements in final state is in increasing order.
 => The final elements is a sub sequence of initial array.
 => Transform the problem to find the maximum increasing sub sequence.

 Now let's talking about how to find maximum increasing subsequence.
 Here we apply a O(N^2) dp solution.

 dp[i] means the longest subsequence ends with i-th element.
 For all j < i, if A[][j] < A[][i], then dp[j] = max(dp[j], dp[i] + 1)

 Time Complexity:
 O(MN^2)

 we cannot do by getting shortest subsequence from each longest increasing subsequence
 cause it may happen the deleted columns are interleaved with each other
 so the acutal possible remain columns could be much shorter
 */
class Solution {
public:
    int minDeletionSize(vector<string>& A) {
        int m = A.size();
        int n = A[0].size();
        int result = n - 1;
        vector<int> dp(n, 1); // the longest increasing subsequence ended with ith element, it will be at least 1 for itself
        for (int col = 0; col < n; col++) { // loop through each element to find the longest subsequence for each word end with col-th element
            for (int i = 0; i < col; i++) { // loop the element before last from 0 ~ col
                int row = 0;
                while (row < m) {
                    // loop through each words to find its longest increasing subsequence ended with ith element
                    // as we will have all words share the same columns
                    if (A[row][i] > A[row][col]) {
                        // ith element cannot be the one before last when ended with col-th element
                        break;
                    }
                    row += 1;
                }
                if (row == m and dp[i] + 1 > dp[col]) {
                    dp[col] = dp[i] + 1;
                }
            }
            result = min(result, n - dp[col]);
        }
        return result;
    }
};
