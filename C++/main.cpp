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
#include "extra_data_types.hpp"
using namespace std;

class Solution {
private:
    void mergeCount(vector<int>& indices, int first, int last, vector<int>& result, vector<int>& nums) {
        if (first >= last) {
            return;
        }

        int mid = first + (last - first) / 2;
        mergeCount(indices, first, mid, result, nums);
        mergeCount(indices, mid, last, result, nums);

        vector<int> temp;
        int idx1 = first;
        int idx2 = mid;
        int semicount = 0; // semicount if the count of numbers have merged in second half before current number in first half
        while (idx1 < mid or idx2 < last) {
            if (idx2 == last or (idx1 < mid and nums[indices[idx1]] <= nums[indices[idx2]])) {
                temp.push_back(indices[idx1]);
                result[indices[idx1]] += semicount;
                idx1 += 1;
            }
            else {
                temp.push_back(indices[idx2]);
                semicount += 1;
                idx2 += 1;
            }
        }
        move(temp.begin(), temp.end(), indices.begin() + first);
    }
public:
    vector<int> countSmaller(vector<int>& nums) {
        int n = nums.size();
        vector<int> indices(n, 0);
        iota(indices.begin(), indices.end(), 0);
        vector<int> result(n, 0);
        mergeCount(indices, 0, n, result, nums);
        return result;
    }
};

int main() {
    Solution s;
    vector<int> temp({5,2,6,1});
    vector<int> temp1({1,3,3,3,2});
    vector<vector<int>> matrix({
        {0,1},
        {1,2},
        {2,1},
        {1,0},
        {0,2},
        {0,0},
        {1,1}
    });
    vector<vector<int>> matrix2({
        {1,2,2,3,5},
        {3,2,3,4,4},
        {2,4,5,3,1},
        {6,7,1,4,5},
        {5,1,1,2,4}
    });
    vector<string> words({"hot","dot","dog","lot","log","cog"});
    TreeNode* r1 = new TreeNode(0);
    TreeNode* r2 = new TreeNode(1);
    TreeNode* r3 = new TreeNode(3);
    r1 -> left = r2;
    s.countSmaller(temp);
}
