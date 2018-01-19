//
//  duplicate_emails.cpp
//  C++
//
//  Created by Chenfu Xie on 1/18/18.
//  Copyright © 2018 Chenfu Xie. All rights reserved.
//

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
using namespace std;

class Solution {
private:
    void dfs(vector<vector<int>>& result, vector<int>& cur, vector<int>& nums, int index) {
        if (cur.size() > 1) {
            result.push_back(cur);
        }
        
        unordered_set<int> unique;
        for (int i = index; i < nums.size(); i++) {
            if ((cur.empty() || nums[i] >= cur.back()) && unique.find(nums[i]) == unique.end()) {
                cur.push_back(nums[i]);
                dfs(result, cur, nums, i + 1);
                cur.pop_back();
                unique.insert(nums[i]);
            }
        }
    }
public:
    vector<vector<int>> findSubsequences(vector<int>& nums) {
        vector<vector<int>> result;
        vector<int> cur;
        dfs(result, cur, nums, 0);
        return result;
    }
};
