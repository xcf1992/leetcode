//
//  checking_the_safe.cpp
//  C++
//
//  Created by Chenfu Xie on 1/20/18.
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
    bool dfs(string& result, int n, int k, int total, unordered_set<string>& visited) {
        if (visited.size() == total) {
            return true;
        }
        
        string prefix = result.substr(result.size() - n + 1, n - 1);
        prefix.push_back('0');
        for (int i = 0; i < k; i++) {
            prefix.back() = '0' + i;
            if (visited.find(prefix) == visited.end()) {
                visited.insert(prefix);
                result.push_back(prefix.back());
                if (dfs(result , n, k, total, visited)) {
                    return true;
                }
                visited.erase(prefix);
                result.pop_back();
            }
        }
        return false;
    }
public:
    string crackSafe(int n, int k) {
        string result(n, '0');
        int total = pow(k, n);
        unordered_set<string> visited;
        dfs(result , n, k, total, visited);
        return result;
    }
};
