/*
1125. Smallest Sufficient Team

In a project, you have a list of required skills req_skills, and a list of people.
The i-th person people[i] contains a list of skills that person has.

Consider a sufficient team:
a set of people such that for every required skill in req_skills,
there is at least one person in the team who has that skill.
We can represent these teams by the index of each person:
for example, team = [0, 1, 3] represents the people with skills people[0], people[1], and people[3].

Return any sufficient team of the smallest possible size,
represented by the index of each person.

You may return the answer in any order.
It is guaranteed an answer exists.

Example 1:
Input: req_skills = ["java","nodejs","reactjs"], people = [["java"],["nodejs"],["nodejs","reactjs"]]
Output: [0,2]

Example 2:
Input: req_skills = ["algorithms","math","java","reactjs","csharp","aws"], people =
[["algorithms","math","java"],["algorithms","math","reactjs"],["java","csharp","aws"],["reactjs","csharp"],["csharp","math"],["aws","java"]]
Output: [1,2]

Constraints:
1 <= req_skills.length <= 16
1 <= people.length <= 60
1 <= people[i].length, req_skills[i].length, people[i][j].length <= 16
Elements of req_skills and people[i] are (respectively) distinct.
req_skills[i][j], people[i][j][k] are lowercase English letters.
It is guaranteed a sufficient team exists.
*/
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <cmath>
#include <queue>
#include <stack>
#include <map>
#include <climits>
using namespace std;

class Solution {
    // another way to write solution1 simillar idea 691. Stickers to Spell Word
private:
    int getSkillSet(vector<string>& people, unordered_map<string, int>& skillIndex) {
        int result = 0;
        for (string& skill : people) {
            result |= 1 << skillIndex[skill];
        }
        return result;
    }

public:
    vector<int> smallestSufficientTeam(vector<string>& req_skills, vector<vector<string>>& people) {
        int n = req_skills.size();
        unordered_map<string, int> skillIndex;
        for (int i = 0; i < n; ++i) {
            skillIndex[req_skills[i]] = i;
        }

        vector<vector<int>> dp(1 << n);
        dp[0] = {};
        for (int state = 0; state < (1 << n); ++state)
            if (state == 0 or !dp[state].empty()) {
                for (int p = 0; p < people.size(); ++p)
                    if (!people[p].empty()) {
                        int skill = getSkillSet(people[p], skillIndex);
                        int nextState = state | skill;
                        if (dp[nextState].empty() or dp[nextState].size() > 1 + dp[state].size()) {
                            dp[nextState] = dp[state];
                            dp[nextState].push_back(p);
                        }
                    }
            }
        return dp[(1 << n) - 1];
    }
};

class Solution1 {
private:
    int getSkillSet(vector<string>& people, unordered_map<string, int>& skillIndex) {
        int result = 0;
        for (string& skill : people) {
            result |= 1 << skillIndex[skill];
        }
        return result;
    }

public:
    vector<int> smallestSufficientTeam(vector<string>& req_skills, vector<vector<string>>& people) {
        int n = req_skills.size();
        unordered_map<string, int> skillIndex;
        for (int i = 0; i < n; ++i) {
            skillIndex[req_skills[i]] = i;
        }
        /*
         * map<int,vector<int>> res; cannot be replaced by unordered_map
         * if rehashing occurs due to the insertion, all iterators are invalidated.
         * Hope it helps someone who makes the same mistake.
         */
        map<int, vector<int>> dp;
        dp[0] = {};
        for (int i = 0; i < people.size(); ++i) {
            int newSkill = getSkillSet(people[i], skillIndex);
            for (auto it = dp.begin(); it != dp.end(); it++) {
                int curSkill = it->first;
                int combineSkill = curSkill | newSkill;
                if (dp.find(combineSkill) == dp.end() or dp[combineSkill].size() > dp[curSkill].size() + 1) {
                    dp[combineSkill] = dp[curSkill];
                    dp[combineSkill].push_back(i);
                }
            }
        }
        return dp[(1 << n) - 1];
    }
};