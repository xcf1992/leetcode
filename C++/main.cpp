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
    int find(int num, vector<int>& parent) {
        if (parent[num] != num) {
            parent[num] = find(parent[num], parent);
        }
        return parent[num];
    }
public:
    string smallestStringWithSwaps(string s, vector<vector<int>> pairs) {
        int n = s.size();
        vector<int> parent(n);
        vector<string> component(n, "");
        for (int i = 0; i < n; ++i) {
            parent[i] = i;
            component[i].push_back(s[i]);
        }

        for (vector<int>& pair : pairs) {
            int pu = find(pair[0], parent);
            int pv = find(pair[1], parent);
            if (pu != pv) {
                parent[pu] = pv;
                for (int c : component[pu]) {
                    component[pv] += component[pu];
                }
            }
        }

        for (int i = 0; i < n; ++i) if (parent[i] == i) {
            sort(component[i].rbegin(), component[i].rend());
        }

        for (int i = 0; i < n; ++i) {
            int pi = find(i, parent);
            s[i] = component[pi].back();
            component[pi].pop_back();
        }
        return s;
    }
};

int main() {
    Solution s;
    s.smallestStringWithSwaps("dcab", {{0,3}, {1,2}});

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
}
