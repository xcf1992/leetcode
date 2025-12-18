/*
https://leetcode.com/problems/time-needed-to-rearrange-a-binary-string/description/
2380. Time Needed to Rearrange a Binary String

You are given a binary string s. In one second, all occurrences of "01" are simultaneously replaced with "10". This
process repeats until no occurrences of "01" exist.

Return the number of seconds needed to complete this process.



Example 1:

Input: s = "0110101"
Output: 4
Explanation:
After one second, s becomes "1011010".
After another second, s becomes "1101100".
After the third second, s becomes "1110100".
After the fourth second, s becomes "1111000".
No occurrence of "01" exists any longer, and the process needed 4 seconds to complete,
so we return 4.
Example 2:

Input: s = "11100"
Output: 0
Explanation:
No occurrence of "01" exists in s, and the processes needed 0 seconds to complete,
so we return 0.


Constraints:

1 <= s.length <= 1000
s[i] is either '0' or '1'.


Follow up:

Can you solve this problem in O(n) time complexity?
*/
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <map>
#include <unordered_set>
#include <algorithm>
#include <cmath>
#include <queue>
#include <stack>
#include <climits>
#include <set>

using namespace std;
/*
DP is O(n) but could be tricky to figure out; Brute-Force is good enough for the contest since n <= 1,000.

DP
We count "zeros" so far. If we have a string 00001, we need 4 seconds (as we have 4 zeros) to make it 10000.

We also track seconds we need to rearrange first i letters.

If i + 1 letter is 1, we need at least seconds + 1 seconds, but not less than zero seconds.

Here is calculation for the "100111110001000001" test case:

For i == 11 (yellow), the result is 7 as we need 6 seconds for i - 1.
For i == 17 (green), the result is 10 as we have 10 zeros, even though we need 7 seconds for i - 1.

To see why max(seconds + 1, zeros) is used. We can think of it as the time it take for the current 1 to reach its
destination. There are two outcomes for this 1. It ether:

never catches up to a prev 1 before the prev 1 finish moving, then this current 1 spend all the time swapping with a 0
before it. This takes zeros amount of time where zeros is the number of 0 before it. It does catch up to a prev 1 before
the prev 1 finish moving and form a 11 at some point. The time it take to catch up is part of the prev time and do not
add anything to its total time. Once a 11 is formed. the second 1 can only follow the first 1's move, but with 1 second
delay. When the first 1 move, the second 1 can move at the next second. When the first 1 wait, the second 1 have to wait
at the next second. Think about waiting in the line of a supermarket, you can move only after the person in front of you
move, but with 1 time slot delay. This 1 second delay means the second 1 will add 1 second at the end for it to reach
its place. That's seconds+1. These are the only two outcomes, we take the max of them.
 */
class Solution {
public:
    int secondsToRemoveOccurrences(string s) {
        int zeros = 0;
        int seconds = 0;
        for (int i = 0; i < s.size(); ++i) {
            zeros += s[i] == '0';
            if (s[i] == '1' && zeros > 0)
                seconds = max(seconds + 1, zeros);
        }
        return seconds;
    }
};