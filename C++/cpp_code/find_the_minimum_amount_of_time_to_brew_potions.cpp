/*
https://leetcode.com/problems/find-the-minimum-amount-of-time-to-brew-potions/description/
3494. Find the Minimum Amount of Time to Brew Potions

You are given two integer arrays, skill and mana, of length n and m, respectively.

In a laboratory, n wizards must brew m potions in order. Each potion has a mana capacity mana[j] and must pass through
all the wizards sequentially to be brewed properly. The time taken by the ith wizard on the jth potion is timeij =
skill[i] * mana[j].

Since the brewing process is delicate, a potion must be passed to the next wizard immediately after the current wizard
completes their work. This means the timing must be synchronized so that each wizard begins working on a potion exactly
when it arrives. ​

Return the minimum amount of time required for the potions to be brewed properly.



Example 1:

Input: skill = [1,5,2,4], mana = [5,1,4,2]

Output: 110

Explanation:

Potion Number	Start time	Wizard 0 done by	Wizard 1 done by	Wizard 2 done by	Wizard 3 done by
0	0	5	30	40	60
1	52	53	58	60	64
2	54	58	78	86	102
3	86	88	98	102	110
As an example for why wizard 0 cannot start working on the 1st potion before time t = 52, consider the case where the
wizards started preparing the 1st potion at time t = 50. At time t = 58, wizard 2 is done with the 1st potion, but
wizard 3 will still be working on the 0th potion till time t = 60.

Example 2:

Input: skill = [1,1,1], mana = [1,1,1]

Output: 5

Explanation:

Preparation of the 0th potion begins at time t = 0, and is completed by time t = 3.
Preparation of the 1st potion begins at time t = 1, and is completed by time t = 4.
Preparation of the 2nd potion begins at time t = 2, and is completed by time t = 5.
Example 3:

Input: skill = [1,2,3,4], mana = [1,2]

Output: 21



Constraints:

n == skill.length
m == mana.length
1 <= n, m <= 5000
1 <= mana[i], skill[i] <= 5000
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
    long long minTime(vector<int>& skill, vector<int>& mana) {
        int n = skill.size();
        int m = mana.size();
        vector<long long> done(n + 1, 0);
        for (int m_idx = 0; m_idx < m; m_idx++) {
            for (int w_idx = 0; w_idx < n; w_idx++) {
                done[w_idx + 1] = max(done[w_idx + 1], done[w_idx]) + 1LL * skill[w_idx] * mana[m_idx];
            }

            for (int w_idx = n - 1; w_idx > 0; w_idx--) {
                done[w_idx] = done[w_idx + 1] - 1LL * skill[w_idx] * mana[m_idx];
            }
        }
        return done[n];
    }
};