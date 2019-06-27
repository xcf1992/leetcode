/*
 552. Student Attendance Record II
 Given a positive integer n, return the number of all possible attendance records with length n, which will be regarded as rewardable. The answer may be very large, return it after mod 109 + 7.

 A student attendance record is a string that only contains the following three characters:

 'A' : Absent.
 'L' : Late.
 'P' : Present.
 A record is regarded as rewardable if it doesn't contain more than one 'A' (absent) or more than two continuous 'L' (late).

 Example 1:
 Input: n = 2
 Output: 8
 Explanation:
 There are 8 records with length 2 will be regarded as rewardable:
 "PP" , "AP", "PA", "LP", "PL", "AL", "LA", "LL"
 Only "AA" won't be regarded as rewardable owing to more than one absent times.
 Note: The value of n won't exceed 100,000.
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
 A(n) = noAP(n - 1) + noAL(n - 1), n ≥ 2.
 noAP(n) = noAP(n - 1) + noAL(n - 1), n ≥ 2.
 noAL(n) = noAP(n - 1) + noAP(n - 2), n ≥ 3.

 We can get A(n) == noAP(n)
 because they are equal, we change noAP(n-1) to A(n-1)
 So here A(n-1) is noAP(n-1)

 A(n) = A(n - 1) + A(n - 2) + A(n - 3), n ≥ 4.
 */
class Solution {
private:
    int MOD = 1e9 + 7;
public:
    int checkRecord(int n) {
        if (n == 1) {
            return 3;
        }
        if (n == 2) {
            return 8;
        }

        vector<int> endWithA(n, 1);
        vector<int> endWithP(n, 1);
        vector<int> endWithL(n, 1);
        endWithL[1] = 3;
        endWithA[1] = 2;
        endWithA[2] = 4;

        for (int i = 1; i < n; i++) {
            endWithP[i] = ((endWithP[i - 1] + endWithL[i - 1]) % MOD + endWithA[i - 1]) % MOD;
            if (i >= 2) {
                endWithL[i] = ((endWithA[i - 1] + endWithP[i - 1]) % MOD + (endWithA[i - 2] + endWithP[i - 2]) % MOD) % MOD;
            }
            if (i >= 3) {
                endWithA[i] = ((endWithA[i - 1] + endWithA[i - 2]) % MOD + endWithA[i - 3]) % MOD;
            }
        }
        return ((endWithA[n - 1] + endWithP[n - 1]) % MOD + endWithL[n - 1]) % MOD;
    }
};
