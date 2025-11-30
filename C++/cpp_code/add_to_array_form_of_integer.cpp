/*
 989. Add to Array-Form of Integer
 User Accepted: 0
 User Tried: 0
 Total Accepted: 0
 Total Submissions: 0
 Difficulty: Easy
 For a non-negative integer X, the array-form of X is an array of its digits in left to right order.  For example, if X
 = 1231, then the array form is [1,2,3,1].

 Given the array-form A of a non-negative integer X, return the array-form of the integer X+K.



 Example 1:

 Input: A = [1,2,0,0], K = 34
 Output: [1,2,3,4]
 Explanation: 1200 + 34 = 1234
 Example 2:

 Input: A = [2,7,4], K = 181
 Output: [4,5,5]
 Explanation: 274 + 181 = 455
 Example 3:

 Input: A = [2,1,5], K = 806
 Output: [1,0,2,1]
 Explanation: 215 + 806 = 1021
 Example 4:

 Input: A = [9,9,9,9,9,9,9,9,9,9], K = 1
 Output: [1,0,0,0,0,0,0,0,0,0,0]
 Explanation: 9999999999 + 1 = 10000000000


 Note：

 1 <= A.length <= 10000
 0 <= A[i] <= 9
 0 <= K <= 10000
 If A.length > 1, then A[0] != 0
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
    vector<int> addToArrayForm(vector<int>& A, int K) {
        vector<int> k;
        while (K != 0) {
            k.push_back(K % 10);
            K /= 10;
        }
        reverse(k.begin(), k.end());

        if (A.size() < k.size()) {
            swap(A, k);
        }

        int add = 0;
        int i = A.size() - 1;
        int j = k.size() - 1;
        while (i >= 0) {
            int sum = A[i] + add;
            if (j >= 0) {
                sum += k[j];
            }

            A[i] = sum % 10;
            add = sum / 10;
            i -= 1;
            j -= 1;
        }
        if (add > 0) {
            A.insert(A.begin(), add);
        }
        return A;
    }
};