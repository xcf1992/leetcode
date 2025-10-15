/*
1198. Find Smallest Common Element in All Rows
https://leetcode.com/problems/find-smallest-common-element-in-all-rows/

Given a matrix mat where every row is sorted in increasing order,
return the smallest common element in all rows.

If there is no common element, return -1.

Example 1:
Input: mat = [[1,2,3,4,5],[2,4,5,8,10],[3,5,7,9,11],[1,3,5,7,9]]
Output: 5

Constraints:
1 <= mat.length, mat[i].length <= 500
1 <= mat[i][j] <= 10^4
mat[i] is sorted in increasing order.
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
#include <map>
using namespace std;

class Solution {
public:
    int smallestCommonElement(vector<vector<int>>& mat) {
        int m = mat.size();
        int n = mat[0].size();
        map<int, int> count;
        for (int j = 0; j < n; ++j) {
            for (int i = 0; i < m; ++i) {
                count[mat[i][j]] += 1;
                if (count[mat[i][j]] == m) {
                    return mat[i][j];
                }
            }
        }
        return -1;
    }
};

class Solution1 {
public:
    int smallestCommonElement(vector<vector<int>>& mat) {
        int m = mat.size();
        int n = mat[0].size();
        map<int, int> count;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                count[mat[i][j]] += 1;
            }
        }

        for (auto& it : count) {
            if (it.second == m) {
                return it.first;
            }
        }
        return -1;
    }
};
