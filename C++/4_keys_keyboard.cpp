/*
651. 4 Keys Keyboard
Imagine you have a special keyboard with the following keys:

Key 1: (A): Print one 'A' on screen.

Key 2: (Ctrl-A): Select the whole screen.

Key 3: (Ctrl-C): Copy selection to buffer.

Key 4: (Ctrl-V): Print buffer on screen appending it after what has already been printed.

Now, you can only press the keyboard for N times (with the above four keys),
find out the maximum numbers of 'A' you can print on screen.

Example 1:
Input: N = 3
Output: 3
Explanation:
We can at most get 3 A's on screen by pressing following key sequence:
A, A, A
Example 2:
Input: N = 7
Output: 9
Explanation:
We can at most get 9 A's on screen by pressing following key sequence:
A, A, A, Ctrl A, Ctrl C, Ctrl V, Ctrl V

Note:
1 <= N <= 50
Answers will be in the range of 32-bit signed integer.
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

class Solution {
public:
    int maxA(int N) {
        vector<int> count(N + 1, 0);
        for (int i = 1; i <= N; i++) {
            count[i] = i;
            for (int j = 1; j <= i - 3; j++) {
                /*
                * we have i - j times of key press for copying and pasting,
                * which can make original count[j] string to become length (i - j - 2) times longger
                * so the total final length will be i - j - 1 times
                */
                count[i] = max(count[i], count[j] * (i - j - 1));
            }
        }
        return count.back();
    }
};

/*
 The inner loop of the bottom-up DP can be truncated to at most four terms,
 that is, for dp[i], we only need to choose the largest one from
 dp[i - 3] * 2, dp[i - 4] * 3, dp[i - 5] * 4, dp[i - 6] * 5,
 while all the rest terms like dp[i - 7] * 6, dp[i - 8] * 7, ... can be ignored.
 The reason is as follows: when computing dp[i - 3],
 we’ve already chosen its value to be the maximum of terms like dp[i - 6] * 2, dp[i - 7] * 3, dp[i - 8] * 4, ...,
 which implies dp[i - 3] >= dp[i - k] * (k - 4) for k >= 6.
 This further leads to dp[i - 3] * 2 >= dp[i - k] * (2k - 8) >= dp[i - k] * (k - 1) if k >= 7.
 So we always have dp[i - 3] * 2 >= dp[i - 7] * 6, dp[i - 3] * 2 >= dp[i - 8] * 7, ....
 Therefore terms like dp[i - 7] * 6, dp[i - 8] * 7, ...
 won’t contribute when evaluating dp[i].

 The truncation will make the DP solution run effectively in O(n) time.
 Also the space complexity can be reduced to O(1) since now we only need to maintain a constant number of variables
 (seven, I would say, dp[i], dp[i-1], dp[i-2], dp[i-3], dp[i-4], dp[i-5], dp[i-6]).
 The following is the modified code:
 */
class Solution1 {
public:
    int maxA(int N) {
        if (N < 7) {
            return N;
        }
        vector<int> count(6, 0);
        for (int i = 0; i < 6; i++) {
            count[i] = i;
        }
        for (int i = 6; i <= N; i++) {
            int temp = 0;
            for (int j = 0; j <= 3; j++) {
                temp = max(temp, count[j] * (5 - j));
            }
            for (int j = 0; j < 5; j++) {
                count[j] = count[j + 1];
            }
            count.back() = temp;
        }
        return count.back();
    }
};
