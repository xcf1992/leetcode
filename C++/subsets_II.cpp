/*
90. Subsets II

Given a collection of integers that might contain duplicates, nums, return all possible subsets (the power set).

Note: The solution set must not contain duplicate subsets.

Example:

Input: [1,2,2]
Output:
[
  [2],
  [1],
  [1,2,2],
  [2,2],
  [1,2],
  []
]
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
    vector<vector<int> > subsetsWithDup(vector<int> &S) {
        vector<int> subset;
        vector<vector<int>> result;
        if (S.empty()) {
            result.push_back(subset);
            return result;
        }

        sort(S.begin(), S.end());
        result.push_back(subset);
        subset.push_back(S[0]);
        result.push_back(subset);
        subset.clear();
        int preValue = S[0];
        int preLength = 1;

        for (int i = 1; i < S.size(); i++) {
            if (S[i] != preValue) {
                preValue = S[i];
                preLength = 0;
            }

            int curLength = result.size();
            for (int j = preLength; j < curLength; j++) {
                subset = result[j];
                subset.push_back(S[i]);
                result.push_back(subset);
            }
            preLength = curLength;
        }

        return result;
    }
};
