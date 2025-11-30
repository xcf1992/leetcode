/*
https://leetcode.com/problems/maximum-difference-between-even-and-odd-frequency-ii/description/
3445. Maximum Difference Between Even and Odd Frequency II

You are given a string s and an integer k. Your task is to find the maximum difference between the frequency of two
characters, freq[a] - freq[b], in a substring subs of s, such that:

subs has a size of at least k.
Character a has an odd frequency in subs.
Character b has a non-zero even frequency in subs.
Return the maximum difference.

Note that subs can contain more than 2 distinct characters.



Example 1:

Input: s = "12233", k = 4

Output: -1

Explanation:

For the substring "12233", the frequency of '1' is 1 and the frequency of '3' is 2. The difference is 1 - 2 = -1.

Example 2:

Input: s = "1122211", k = 3

Output: 1

Explanation:

For the substring "11222", the frequency of '2' is 3 and the frequency of '1' is 2. The difference is 3 - 2 = 1.

Example 3:

Input: s = "110", k = 3

Output: -1



Constraints:

3 <= s.length <= 3 * 104
s consists only of digits '0' to '4'.
The input is generated that at least one substring has a character with an even frequency and a character with an odd
frequency. 1 <= k <= s.length
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
#include <set>
#include <numeric>
using namespace std;

// https://leetcode.com/problems/maximum-difference-between-even-and-odd-frequency-ii/solutions/6831146/easy-to-understand-explanation-for-edito-0bca/
/*
Easy to understand explanation for editorial solution

kaitouchinh
Top Interview 150
21433
Jun 10, 2025
Sliding Window
Prefix Sum
Bitmask
Java
The core idea is to reframe the problem from finding a substring to finding two points in the string (a start and an
end) that satisfy certain conditions. By iterating through all possible characters for a and b, the problem simplifies
to: for a fixed a and b, find the maximum difference.

The solution uses a combination of prefix sums, bitmasking for states, and a sliding window/two-pointer approach to
solve the problem efficiently for each pair of characters (a, b).

Brute-Force Character Selection
The problem is to find the max difference for some pair of characters a and b. Since the set of possible characters is
very small ('0' to '4'), we can simply test every possible combination. We use a nested loop to iterate through all 20
pairs where a is not equal to b. The final answer will be the maximum value found across all these pairs.

Using Prefix Sums to Find Substring Frequencies
The frequency of a character in a substring s[i...j] can be calculated using prefix sums. Let count(char, j) be the
number of times char appears in the prefix s[0...j].

freq[a] in s[i...j] = count(a, j) - count(a, i-1)
freq[b] in s[i...j] = count(b, j) - count(b, i-1)
The value we want to maximize is freq[a] - freq[b]. Let's rewrite this:

(count(a, j) - count(a, i-1)) - (count(b, j) - count(b, i-1))
Rearranging this gives us a crucial insight:

(count(a, j) - count(b, j)) - (count(a, i-1) - count(b, i-1))
This means for a given substring ending at j, to maximize the total difference, we need to find a starting point i-1
that minimizes the term count(a, i-1) - count(b, i-1) while still satisfying the problem's parity conditions.

Using Bitmasks to Handle Parity (Odd/Even) Conditions
The problem has strict rules about the parity of frequencies: freq[a] must be odd, and freq[b] must be even.

The parity of a difference depends on the parity of the numbers being subtracted:

odd - even = odd
even - odd = odd
odd - odd = even
even - even = even
So, for freq[a] to be odd, the parities of count(a, j) and count(a, i-1) must be different. For freq[b] to be even, the
parities of count(b, j) and count(b, i-1) must be the same.

We can represent the parity of the two prefix counts (count(a), count(b)) as a 2-bit state:

Bit 1: count(a) % 2 (1 for odd, 0 for even)
Bit 0: count(b) % 2 (1 for odd, 0 for even)
This gives us 4 possible states for any prefix:

00 (Decimal 0): count(a) is even, count(b) is even.
01 (Decimal 1): count(a) is even, count(b) is odd.
10 (Decimal 2): count(a) is odd, count(b) is even.
11 (Decimal 3): count(a) is odd, count(b) is odd.
Our target substring must have the state 10 (freq[a] odd, freq[b] even).

The state of a substring is the XOR of the states of its endpoint prefixes. Why? Let's say the 2 endpoints are i and j
and so the prefix states are state_i and state_j. Let's consider bit 0 which is count(b):

bit 0 state_i     bit 0 state_j     XOR      b's parity in s[i, j]
     0                 0             0        even - even = even = 0
     0                 1             1        odd - even = odd = 1
     1                 0             1        even - odd = odd = 1
     1                 1             0        odd - odd = even = 0
You can see the XOR will give the correct parity of b in s[i, j] when we XOR bit 0 of the 2 states.
Similarly, it will also give the correct parity of a in s[i, j] when we XOR bit 1 of the 2 states. Therefore the state
of the whole substring is the XOR of the states of the 2 endpoint prefixes.

If state_j is the state for prefix s[0, j] and state_{i-1} is for prefix s[0, i-1], then:

target_state = state_j ⊕ state_{i-1}
10 = state_j ⊕ state_{i-1}
Therefore, state_{i-1} = state_j ⊕ 10.
This tells us: for a prefix ending at j with state state_j, we must find a previous prefix ending at i-1 that had the
state state_j ⊕ 10.

The best Array and the Two-Pointer Logic
This is where all the pieces come together. We iterate through the string with a right pointer, representing the end of
our potential substring.

right: The main iterator, moving from 0 to n-1. It defines the prefix s[0...right].
left: A second pointer that trails behind. It defines the prefix s[0...left] that we consider as a potential starting
point (specifically, left+1 is the start of the substring). best[4]: An array to store the minimum value of prev_a -
prev_b seen so far for each of the 4 possible parity states. best[status] holds this minimum value for all prefixes
s[0...left] that have the state status. The process for each right:

Advance right: Move right one step, and update the prefix counts cnt_a and cnt_b for the prefix s[0...right].
Update best array: Before calculating an answer, we potentially advance the left pointer. The while loop updates the
best array. It processes prefixes ending at left only when they are valid candidates to start a substring (i.e., right -
left >= k). For each such left, we calculate its state (left_status) and update best[left_status] with the minimum
prev_a - prev_b seen. Calculate Answer: Get the state for the current prefix s[0...right], let's call it right_status.
Find the required state for the starting prefix: required_status = right_status ⊕ 0b10.
Look up best[required_status]. This gives us the minimum prev_a - prev_b for a valid starting prefix that satisfies the
parity rules. The potential answer for this right is (cnt_a - cnt_b) - best[required_status]. We update our global
maximum ans with this value.
 */
class Solution {
public:
    int maxDifference(string s, int k) {
        int n = s.size();
        vector pre(5, vector(n, 0)), closest_right(5, vector(n, n));
        for(int x = 0; x < 5; x++) {
            for(int i = 0; i < n; i++) {
                int num = s[i]-'0';
                pre[x][i] = (num == x);
                if(i > 0) pre[x][i] += pre[x][i - 1];
            }
            for(int i = n - 1; i >= 0; i--) {
                int num = s[i]-'0';
                if(i < n-1) closest_right[x][i] = closest_right[x][i + 1];
                if(num == x) closest_right[x][i] = i;
            }
        }
        int ans = INT_MIN;
        auto go = [&](int odd, int even) -> int {
            vector suf(2, vector(2, vector(n, INT_MIN)));

            for(int end_idx = 0; end_idx < n; end_idx++) {
                int odd_parity = pre[odd][end_idx] % 2;
                int even_parity = pre[even][end_idx] % 2;
                if(pre[odd][end_idx] > 0 && pre[even][end_idx] > 0) {
                    suf[odd_parity][even_parity][end_idx] = pre[odd][end_idx] - pre[even][end_idx];
                }
            }
            for(int odd_parity = 0; odd_parity < 2; odd_parity++) {
                for(int even_parity = 0; even_parity < 2; even_parity++) {
                    for(int end_idx = n - 2; end_idx >= 0; end_idx--) {
                        suf[odd_parity][even_parity][end_idx] = max(
                            suf[odd_parity][even_parity][end_idx],
                            suf[odd_parity][even_parity][end_idx + 1]);
                    }
                }
            }
            for(int start_idx = 0; start_idx < n; start_idx++) {
                int min_end_idx = start_idx + k - 1;
                if(min_end_idx >= n) break;

                int odd_below_i = (start_idx == 0 ? 0 : pre[odd][start_idx - 1]);
                int even_below_i = (start_idx == 0 ? 0 : pre[even][start_idx - 1]);

                int good_odd_parity = (odd_below_i + 1) % 2;
                int good_even_parity = (even_below_i) % 2;

                int query = max({start_idx + k - 1, closest_right[odd][start_idx], closest_right[even][start_idx]});
                if(query >= n) continue;

                int val = suf[good_odd_parity][good_even_parity][query];
                if(val == INT_MIN) continue;

                ans = max(ans, val - odd_below_i + even_below_i);
            }
            return ans;
        };
        for(int a = 0; a <= 4; a++) {
            for(int b = 0; b <= 4; b++) {
                if(a != b) {
                    go(a, b);
                }
            }
        }
        return ans;
    }
};
