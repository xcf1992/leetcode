/*
47. Permutations II

Given a collection of numbers that might contain duplicates, return all possible unique permutations.

Example:

Input: [1,1,2]
Output:
[
  [1,1,2],
  [1,2,1],
  [2,1,1]
]
*/
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <algorithm>
using namespace std;

class Solution {
private:
    void generate(vector<vector<int>>& result, vector<int> permutation, map<int, int>& count, int length) {
        if (permutation.size() == length) {
            result.push_back(permutation);
            return;
        }

        for (auto it = count.begin(); it != count.end(); it++) if (it -> second > 0) {
            permutation.push_back(it -> first);
            it -> second -= 1;
            generate(result, permutation, count, length);
            it -> second += 1;
            permutation.pop_back();
        }
    }
public:
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        map<int, int> count;
        for (int num : nums) {
            count[num] += 1;
        }

        vector<vector<int>> result;
        vector<int> permutation;
        generate(result, permutation, count, nums.size());
        return result;
    }
};

class Solution1 {
private:
    void generate(vector<int> &num, vector<int> &visit, vector<int> &solution, vector<vector<int>> &result) {
        if (solution.size() == num.size()) {
            result.push_back(solution);
            return;
        }

        for (int i = 0; i < num.size(); i++) {
            if (visit[i] == 0) {
                if (i > 0 and num[i - 1] == num[i] and visit[i - 1] == 0) {
                    continue;
                }

                visit[i] = 1;
                solution.push_back(num[i]);
                generate(num, visit, solution, result);
                solution.pop_back();
                visit[i] = 0;
            }
        }
    }
public:
    vector<vector<int> > permuteUnique(vector<int> &num) {
        vector<int> solution;
        vector<vector<int>> result;
        vector<int> visit(num.size(), 0);

        sort(num.begin(), num.end());
        generate(num, visit, solution, result);
        return result;
    }
};


class Solution2 {
private:
    void generate(vector<int> num, int start, vector<vector<int>> &result) {
        if (start == num.size()) {
            result.push_back(num);
            return;
        }

        for (int i = start; i < num.size(); i++) {
            if (i != start and num[i] == num[start]) {
                continue;
            }

            swap(num[i], num[start]);
            generate(num, start + 1, result);
        }
    }
public:
    vector<vector<int> > permuteUnique(vector<int> &num) {
        vector<vector<int>> result;
        sort(num.begin(), num.end());
        generate(num, 0, result);
        return result;
    }
};
