/*
https://leetcode.com/problems/maximum-total-damage-with-spell-casting/description/
3186. Maximum Total Damage With Spell Casting

A magician has various spells.

You are given an array power, where each element represents the damage of a spell. Multiple spells can have the same
damage value.

It is a known fact that if a magician decides to cast a spell with a damage of power[i], they cannot cast any spell with
a damage of power[i] - 2, power[i] - 1, power[i] + 1, or power[i] + 2.

Each spell can be cast only once.

Return the maximum possible total damage that a magician can cast.



Example 1:

Input: power = [1,1,3,4]

Output: 6

Explanation:

The maximum possible damage of 6 is produced by casting spells 0, 1, 3 with damage 1, 1, 4.

Example 2:

Input: power = [7,1,6,6]

Output: 13

Explanation:

The maximum possible damage of 13 is produced by casting spells 1, 2, 3 with damage 1, 6, 6.



Constraints:

1 <= power.length <= 105
1 <= power[i] <= 109
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
    long long maximumTotalDamage(vector<int>& power) {
        unordered_map<int, long long> freq;
        for (int& p : power) {
            freq[p] += 1;
        }

        vector<int> keys;
        for (auto it = freq.begin(); it != freq.end(); ++it) {
            keys.push_back(it->first);
        }
        sort(keys.begin(), keys.end());

        int n = keys.size();
        vector<long long> dp(n, 0);
        dp[0] = keys[0] * freq[keys[0]];
        for (int i = 1; i < n; i++) {
            long long max_damage = keys[i] * freq[keys[i]];
            int prev = lower_bound(keys.begin(), keys.begin() + i, keys[i] - 2) - keys.begin() - 1;
            if (prev >= 0) {
                max_damage += dp[prev];
            }
            dp[i] = max(dp[i - 1], max_damage);
        }
        return dp[n - 1];
    }
};
