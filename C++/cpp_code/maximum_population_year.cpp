/*
https://leetcode.com/problems/maximum-population-year/description/
1854. Maximum Population Year

You are given a 2D integer array logs where each logs[i] = [birthi, deathi] indicates the birth and death years of the ith person.

The population of some year x is the number of people alive during that year. The ith person is counted in year x's population if x is in the inclusive range [birthi, deathi - 1]. Note that the person is not counted in the year that they die.

Return the earliest year with the maximum population.



Example 1:

Input: logs = [[1993,1999],[2000,2010]]
Output: 1993
Explanation: The maximum population is 1, and 1993 is the earliest year with this population.
Example 2:

Input: logs = [[1950,1961],[1960,1971],[1970,1981]]
Output: 1960
Explanation:
The maximum population is 2, and it had happened in years 1960 and 1970.
The earlier year between them is 1960.


Constraints:

1 <= logs.length <= 100
1950 <= birthi < deathi <= 2050
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
#include <set>
#include <numeric>
using namespace std;

class Solution {
public:
    int maximumPopulation(vector<vector<int>>& logs) {
        vector<pair<int,int>> population;
        for (const vector<int>& log : logs) {
            population.push_back({log[0], 1});
            population.push_back({log[1], -1});
        }

        sort(population.begin(), population.end(), [](pair<int,int> a, pair<int,int> b) {
            return a.first < b.first || (a.first == b.first && a.second < b.second);
        });

        int rst = 0;
        int cur_population = 0;
        int max_population = -1;
        for (const pair<int,int>& p : population) {
            cur_population += p.second;
            if (cur_population > max_population) {
                max_population = cur_population;
                rst = p.first;
            }
        }
        return rst;
    }
};
