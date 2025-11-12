/*
https://leetcode.com/problems/maximize-subarrays-after-removing-one-conflicting-pair/description/?envType=problem-list-v2&envId=prefix-sum
3480. Maximize Subarrays After Removing One Conflicting Pair

You are given an integer n which represents an array nums containing the numbers from 1 to n in order. Additionally, you
are given a 2D array conflictingPairs, where conflictingPairs[i] = [a, b] indicates that a and b form a conflicting
pair.

Remove exactly one element from conflictingPairs. Afterward, count the number of non-empty subarrays of nums which do
not contain both a and b for any remaining conflicting pair [a, b].

Return the maximum number of subarrays possible after removing exactly one conflicting pair.



Example 1:

Input: n = 4, conflictingPairs = [[2,3],[1,4]]

Output: 9

Explanation:

Remove [2, 3] from conflictingPairs. Now, conflictingPairs = [[1, 4]].
There are 9 subarrays in nums where [1, 4] do not appear together. They are [1], [2], [3], [4], [1, 2], [2, 3], [3, 4],
[1, 2, 3] and [2, 3, 4]. The maximum number of subarrays we can achieve after removing one element from conflictingPairs
is 9. Example 2:

Input: n = 5, conflictingPairs = [[1,2],[2,5],[3,5]]

Output: 12

Explanation:

Remove [1, 2] from conflictingPairs. Now, conflictingPairs = [[2, 5], [3, 5]].
There are 12 subarrays in nums where [2, 5] and [3, 5] do not appear together.
The maximum number of subarrays we can achieve after removing one element from conflictingPairs is 12.


Constraints:

2 <= n <= 105
1 <= conflictingPairs.length <= 2 * n
conflictingPairs[i].length == 2
1 <= conflictingPairs[i][j] <= n
conflictingPairs[i][0] != conflictingPairs[i][1]
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
An Intuitive Single-Pass Solution [Python/C++/Java]
This problem seems complex, but it has an elegant and highly efficient solution that uses a single pass. The core idea
is to reframe the problem: instead of removing a pair and re-calculating everything, we can calculate the base score
(with no pairs removed) and the maximum potential bonus from removing a pair at the same time.

This explanation will break down the intuition step-by-step, focusing on the two key concepts: the "Forbidden Start" and
the "Bonus Gain".

Part 1: The Core Idea - The "Forbidden Start"
First, let's solve a simpler problem: How do we count all valid subarrays if we don't remove any conflicts?

The most efficient way is to iterate from r = 1 to n, where r is the endpoint of a subarray. At each r, we'll count how
many valid subarrays end at that exact position. The grand total will be the sum of these counts.

A conflict like (1, 3) creates a rule: "Any subarray that ends at position 3 or later is forbidden from starting at
position 1 or earlier."

As we iterate, we collect these rules. The "Forbidden Start" for any endpoint r is the strictest rule we've encountered
so far. It's the largest u from any active conflict (u, v) where v <= r.

The number of valid subarrays ending at r is found with a simple formula:
Count at step r = r - Forbidden Start

Tracing the Base Count Calculation
Let's trace this with n = 5, conflicts = [[1, 3], [2, 4], [1, 4]]. Our goal is to find the base score.

r = 1:

Active Conflicts: None.
Forbidden Start: 0.
Count for this step: 1 - 0 = 1. ([1])
Total Score so far: 1
r = 2:

Active Conflicts: None.
Forbidden Start: 0.
Count for this step: 2 - 0 = 2. ([2], [1, 2])
Total Score so far: 1 + 2 = 3
r = 3:

Active Conflicts: (1, 3). The rule is "don't start at or before 1".
Forbidden Start: 1.
Count for this step: 3 - 1 = 2. ([2, 3], [3])
Total Score so far: 3 + 2 = 5
r = 4:

Active Conflicts: (1, 3), (1, 4), (2, 4). The rules are "don't start <= 1" and "don't start <= 2".
Forbidden Start: The strictest rule is the largest u, so it's 2.
Count for this step: 4 - 2 = 2. ([3, 4], [4])
Total Score so far: 5 + 2 = 7
r = 5:

Active Conflicts: Same as r=4.
Forbidden Start: The strictest rule is still from (2, 4), so it remains 2.
Count for this step: 5 - 2 = 3. ([3,4,5], [4,5], [5])
Total Score so far: 7 + 3 = 10
After the pass, the total base score is 10. This is what the ans variable in the code calculates.

Part 2: The Leap - Finding the Best "Bonus"
Now for the main trick. We can find the best possible bonus at the same time. At each step, we ask:

"If the rule that gave me my current 'Forbidden Start' was removed, what would my new 'Forbidden Start' be?"

To answer this, we must track the top two strictest rules.

top1: The "Forbidden Start" we just used. It's the largest u from all active conflicts.
top2: The second-largest u. This is our backup—the rule that would take over if the top1 conflict was gone.
The gain we get at any single step r is the difference in the number of subarrays:

Original count: r - top1
Bonus count: r - top2
Gain at step r: (r - top2) - (r - top1) = top1 - top2
The bonus array acts as a scoreboard. When we calculate a gain, we add it to the tally for the conflict that caused it.

Tracing the Full Logic (Base + Bonus)
Let's trace again, this time tracking top1, top2, and the bonus array.

r = 3:

Active Conflicts: (1, 3).
top1 = 1, top2 = 0.
Base Count: ans += 3 - 1 = 2. (ans is now 5).
Gain: top1 - top2 = 1 - 0 = 1.
Update Scoreboard: This gain is for removing the conflict starting at u=1. So, bonus[1] += 1.
r = 4:

Active Conflicts give u values of {1, 1, 2}.
top1 = 2, top2 = 1.
Base Count: ans += 4 - 2 = 2. (ans is now 7).
Gain: top1 - top2 = 2 - 1 = 1.
Update Scoreboard: This gain is for removing the conflict starting at u=2. So, bonus[2] += 1.
r = 5:

Active Conflicts are the same.
top1 = 2, top2 = 1.
Base Count: ans += 5 - 2 = 3. (ans is now 10).
Gain: top1 - top2 = 2 - 1 = 1.
Update Scoreboard: This gain is also for the conflict starting at u=2. So, bonus[2] += 1.
Final Result
The final Base Score (ans) is 10.
The final Bonus Scoreboard (bonus) shows bonus[1]=1 and bonus[2]=2.
The Maximum Bonus we can get is max(bonus) = 2.
The final answer is Base Score + Max Bonus = 10 + 2 = 12.
 */
#include <vector>
#include <algorithm>

class Solution {
public:
    long long maxSubarrays(int n, std::vector<std::vector<int>>& conflictingPairs) {
        std::vector<std::vector<int>> right(n + 1);
        for (const auto& pair : conflictingPairs) {
            right[std::max(pair[0], pair[1])].push_back(std::min(pair[0], pair[1]));
        }

        long long rst = 0;
        std::vector<long long> left = {0, 0};  // {largest forbidden start, second largest forbidden start}
        std::vector<long long> bonus(n + 1, 0);

        for (int r = 1; r <= n; ++r) {
            for (int l_val : right[r]) {
                // Manually update top two values
                if (l_val > left[0]) {
                    left = {static_cast<long long>(l_val), left[0]};
                } else if (l_val > left[1]) {
                    left = {left[0], static_cast<long long>(l_val)};
                }
            }

            rst += r - left[0];

            if (left[0] > 0) {
                bonus[left[0]] += left[0] - left[1];
            }
        }

        long long max_bonus = 0;
        for (long long b : bonus) {
            max_bonus = std::max(max_bonus, b);
        }

        return rst + max_bonus;
    }
};
