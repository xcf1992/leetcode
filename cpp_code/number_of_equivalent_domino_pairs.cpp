/*
1128. Number of Equivalent Domino Pairs
Given a list of dominoes,
dominoes[i] = [a, b] is equivalent to dominoes[j] = [c, d]
if and only if either (a==c and b==d), or (a==d and b==c)
- that is, one domino can be rotated to be equal to another domino.

Return the number of pairs (i, j) for which 0 <= i < j < dominoes.length, and dominoes[i] is equivalent to dominoes[j].

Example 1:

Input: dominoes = [[1,2],[2,1],[3,4],[5,6]]
Output: 1


Constraints:

1 <= dominoes.length <= 40000
1 <= dominoes[i][j] <= 9
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
#include "extra_data_types.hpp"
using namespace std;

class Solution {
private:
    string genKey(vector<int>& dominoe) {
        if (dominoe[0] > dominoe[1]) {
            return to_string(dominoe[0]) + "-" + to_string(dominoe[1]);
        }
        return to_string(dominoe[1]) + "-" + to_string(dominoe[0]);
    }
public:
    int numEquivDominoPairs(vector<vector<int>>& dominoes) {
        unordered_map<string, int> count;
        for (vector<int>& dominoe : dominoes) {
            count[genKey(dominoe)] += 1;
        }

        int result = 0;
        for (auto& it : count) {
            int k = it.second;
            if (k > 1) {
                result += k * (k - 1) / 2;
            }
        }
        return result;
    }
};

class Solution1 { // TLE
public:
    int numEquivDominoPairs(vector<vector<int>>& dominoes) {
        int n = dominoes.size();
        int result = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                if ((dominoes[i][0] == dominoes[j][0] and dominoes[i][1] == dominoes[j][1]) or (dominoes[i][1] == dominoes[j][0] and dominoes[i][0] == dominoes[j][1])) {
                    result += 1;
                }
            }
        }
        return result;
    }
};
