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
private:
    void dfs(vector<set<char>>& groups, int index, vector<string>& result, string cur) {
        if (index == groups.size()) {
            result.push_back(cur);
        }
        
        for (char c : groups[index]) {
            cur.push_back(c);
            dfs(groups, index + 1, result, cur);
            cur.pop_back();
        }
    }
public:
    vector<string> expand(string S) {
        int n = S.size();
        vector<set<char>> groups;
        for (int i = 0; i < n; ++i) {
            set<char> cur;
            if (S[i] == '{') {
                while (i < n and S[i] != '}') {
                    if (isalpha(S[i])) {
                        cur.insert(S[i]);
                    }
                    i += 1;
                }
            }
            else {
                cur.insert(S[i]);
            }
            groups.push_back(cur);
        }
        
        vector<string> result;
        dfs(groups, 0, result, "");
        return result;
    }
};

int main() {
    Solution s;
    vector<int> temp({1,4,2,5,3});
    vector<vector<int>> matrix({
        {0,1,0},
        {1,1,1},
        {0,1,0}
    });
    s.expand("{a,b}c{d,e}f");
}
