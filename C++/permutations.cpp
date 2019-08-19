/*
46. Permutations

Given a collection of distinct integers, return all possible permutations.

Example:

Input: [1,2,3]
Output:
[
  [1,2,3],
  [1,3,2],
  [2,1,3],
  [2,3,1],
  [3,1,2],
  [3,2,1]
]
*/
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

class Solution {
private:
    void generate(vector<vector<int>>& result, vector<int>& num, int level) {
        if (level == num.size()) {
            result.push_back(num);
            return;
        }

        for (int i = level; i < num.size(); i++) {
            swap(num[i], num[level]);
            generate(result, num, level + 1);
            swap(num[i], num[level]);
        }
    }
public:
    vector<vector<int> > permute(vector<int>& num) {
        vector<vector<int>> result;
        generate(result, num, 0);
        return result;
    }
};
