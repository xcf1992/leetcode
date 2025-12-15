/*
https://leetcode.com/problems/divide-players-into-teams-of-equal-skill/description/
2491. Divide Players Into Teams of Equal Skill

You are given a positive integer array skill of even length n where skill[i] denotes the skill of the ith player. Divide
the players into n / 2 teams of size 2 such that the total skill of each team is equal.

The chemistry of a team is equal to the product of the skills of the players on that team.

Return the sum of the chemistry of all the teams, or return -1 if there is no way to divide the players into teams such
that the total skill of each team is equal.



Example 1:

Input: skill = [3,2,5,1,3,4]
Output: 22
Explanation:
Divide the players into the following teams: (1, 5), (2, 4), (3, 3), where each team has a total skill of 6.
The sum of the chemistry of all the teams is: 1 * 5 + 2 * 4 + 3 * 3 = 5 + 8 + 9 = 22.
Example 2:

Input: skill = [3,4]
Output: 12
Explanation:
The two players form a team with a total skill of 7.
The chemistry of the team is 3 * 4 = 12.
Example 3:

Input: skill = [1,1,2,3]
Output: -1
Explanation:
There is no way to divide the players into teams such that the total skill of each team is equal.


Constraints:

2 <= skill.length <= 105
skill.length is even.
1 <= skill[i] <= 1000
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
#include <set>
using namespace std;

class Solution {
public:
    long long dividePlayers(vector<int>& skill) {
        int sum = 0;
        unordered_map<int, int> skill_map;
        for (int s : skill) {
            sum += s;
            skill_map[s] += 1;
        }

        int n = skill.size();
        int group_cnt = n / 2;
        if (sum % group_cnt != 0) {
            return -1;
        }

        long long rst = 0;
        int target = sum / group_cnt;
        for (auto& [cur_skill, cur_freq] : skill_map) {
            int target_skill = target - cur_skill;
            if (skill_map.find(target_skill) == skill_map.end() || skill_map[target_skill] != cur_freq) {
                return -1;
            }
            rst += 1LL * cur_freq * cur_skill * target_skill;
        }
        return rst / 2;
    }
};
