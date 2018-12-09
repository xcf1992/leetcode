/*
 We are given an array A of N lowercase letter strings, all of the same length.

 Now, we may choose any set of deletion indices, and for each string, we delete all the characters in those indices.

 For example, if we have an array A = ["abcdef","uvwxyz"] and deletion indices {0, 2, 3}, then the final array after deletions is ["bef","vyz"].

 Suppose we chose a set of deletion indices D such that after deletions, the final array has its elements in lexicographic order (A[0] <= A[1] <= A[2] ... <= A[A.length - 1]).

 Return the minimum possible value of D.length.



 Example 1:

 Input: ["ca","bb","ac"]
 Output: 1
 Explanation:
 After deleting the first column, A = ["a", "b", "c"].
 Now A is in lexicographic order (ie. A[0] <= A[1] <= A[2]).
 We require at least 1 deletion since initially A was not in lexicographic order, so the answer is 1.
 Example 2:

 Input: ["xc","yb","za"]
 Output: 0
 Explanation:
 A is already in lexicographic order, so we don't need to delete anything.
 Note that the rows of A are not necessarily in lexicographic order:
 ie. it is NOT necessarily true that (A[0][0] <= A[0][1] <= ...)
 Example 3:

 Input: ["zyx","wvu","tsr"]
 Output: 3
 Explanation:
 We have to delete every column.


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

class Solution {
public:
    int minDeletionSize(vector<string>& A) {
        int result = 0;
        int n = A[0].size();
        for (int col = 0; col < n; col++) {
            bool pass = true;
            int equal = 0;
            for (int row = 1; row < A.size(); row++) {
                if (A[row].substr(0, col + 1) < A[row - 1].substr(0, col + 1)) {
                    pass = false;
                    break;
                }
                else if (A[row].substr(0, col + 1) == A[row - 1].substr(0, col + 1)) {
                    equal += 1;
                }
            }
            if (pass) {
                if (equal == 0) {
                    return result;
                }
            }
            else {
                for (int row = 0; row < A.size(); row++) {
                    A[row][col] = 'a';
                }
                result += 1;
            }
        }
        return result;
    }
};
