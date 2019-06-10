/*
650. 2 Keys Keyboard
Initially on a notepad only one character 'A' is present. You can perform two operations on this notepad for each step:

Copy All: You can copy all the characters present on the notepad (partial copy is not allowed).
Paste: You can paste the characters which are copied last time.
 

Given a number n. You have to get exactly n 'A' on the notepad by performing the minimum number of steps permitted. Output the minimum number of steps to get n 'A'.

Example 1:

Input: 3
Output: 3
Explanation:
Intitally, we have one character 'A'.
In step 1, we use Copy All operation.
In step 2, we use Paste operation to get 'AA'.
In step 3, we use Paste operation to get 'AAA'.
 

Note:

The n will be in the range [1, 1000].
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
using namespace std;

/*
Allow me to explain what is being done here.
As per the keyboard operations:
to get AA from A we need 2 additional steps (copy-all and then paste)
to get AAA from A we need 3 additional steps (copy-all, then paste, then again paste)

For generating AAAA we need 2 additional steps from AA.
however, to get AAAAAAAA, the most optimal way would be from AAAA, with 2 additional steps (copy-all then paste)
Essentially, we find the next smaller length sequence (than the one under consideration) 
which can be copied and then pasted over multiple times to generate the desired sequence. 
The moment we find a length that divides our required sequence length perfectly, 
then we don't need to check for any smaller length sequences.
*/
class Solution2 { // refine of solution1
public:
    int minSteps(int n) {
        vector<int> dp(n + 1, INT_MAX);
        dp[1] = 0;
        for (int i = 2; i <= n; ++i) {
            for (int j = i - 1; j > 0; --j) {
                if (i % j == 0) {
                    dp[i] = min(dp[i], dp[j] + i / j);
                    break;
                }
            }
        }
        return dp[n];
    }
};

class Solution {
public:
    int minSteps(int n) { //100%
        if (n == 1) {
            return 0;   
        }
        for (int i = 2; i <= sqrt(n); i++) {
            if (n % i == 0) {
                return i + minSteps(n / i);
            }
        }
        return n;
    }
};

class Solution1 { // faster than 26.80%
public:
    int minSteps(int n) {
        vector<int> dp(n + 1, INT_MAX);
        dp[1] = 0;
        for (int i = 2; i <= n; ++i) {
            for (int j = 1; j < i; ++j) {
                if (i % j == 0) {
                    dp[i] = min(dp[i], dp[j] + i / j);
                }
            }
        }
        return dp[n];
    }
};
