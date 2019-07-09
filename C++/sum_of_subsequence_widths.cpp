/*
 891. Sum of Subsequence Widths
 Given an array of integers A, consider all non-empty subsequences of A.

 For any sequence S, let the width of S be the difference between the maximum and minimum element of S.

 Return the sum of the widths of all subsequences of A.

 As the answer may be very large, return the answer modulo 10^9 + 7.



 Example 1:

 Input: [2,1,3]
 Output: 6
 Explanation:
 Subsequences are [1], [2], [3], [2,1], [2,3], [1,3], [2,1,3].
 The corresponding widths are 0, 0, 0, 1, 1, 2, 2.
 The sum of these widths is 6.


 Note:

 1 <= A.length <= 20000
 1 <= A[i] <= 20000
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
 For A[i]:
 There are i smaller numbers,
 so there are 2 ^ i sequences in which A[i] is maximum.
 we should do res += A[i] * (2 ^ i), since we will have A[i] - X

 There are n - i - 1 bigger numbers,
 so there are 2 ^ (n - i - 1) sequences in which A[i] is minimum.
 we should do res -= A[i] * 2 ^ (n - i - 1), since we will have X - A[i]

 Q. why do we plus mod before return?
 A: in Cpp and Java, mod on negative number will still get a negative number.
 */
class Solution {
private:
    int mod = 1e9 + 7;
public:
    int sumSubseqWidths(vector<int>& A) {
        int n = A.size();
        sort(A.begin(), A.end());

        long result = 0;
        long count = 1;
        for (int i = 0; i < n; i++) {
            // here we write in a simplified way
            // as for the count for A[i] is maximum is the same as the number A[n - i - 1] is the minimum
            // so we can use only one count to loop through the array
            result = (result + A[i] * count - A[n - i - 1] * count) % mod;
            count = (count << 1) % mod;
        }
        return (result + mod) % mod;
    }
};

/*
 1. We sort the array.
 2. We loop from smallest to largest number.
 3. For each number we calculate in how many subsequences we can have when we pick minimum and maximum, A[i] and A[j] in the code, the number will be pow(2, j - i - 1)

 It seems I have passed other cases, but failed at:
 [5,69,89,92,31,16,25,45,63,40,16,56,24,40,75,82,40,12,50,62,92,44,67,38,92,22,91,24,26,21,100,42,23,56,64,43,95,76,84,79,89,4,16,94,16,77,92,9,30,13]
 my outcome is: 857876213
 the expected is: 857876214
 */
class Solution1 {
private:
    int mod = 1e9 + 7;
public:
    int sumSubseqWidths(vector<int>& A) {
        sort(A.begin(), A.end());
        long result = 0;
        for (int i = 0; i < A.size(); i++) {
            for (int j = i + 1; j < A.size(); j++) {
                int gap = A[j] - A[i];
                result += pow(2, j - i - 1) * gap;
                result %= mod;
            }
        }
        return result;
    }
};
