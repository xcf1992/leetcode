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

struct myComp {
    bool operator()(pair<int, int>& a, pair<int, int>& b) {
        return a.second < b.second;
    }
};

class Solution {
public:
    int largestValsFromLabels(vector<int>& values, vector<int>& labels, int num_wanted, int use_limit) {
        priority_queue<pair<int, int>, vector<pair<int, int>>> maxHeap;
        int n = values.size();
        for (int i = 0; i < n; ++i) {
            maxHeap.push({labels[i], values[i]});
        }
        
        int result = 0;
        unordered_map<int, int> used;
        int count = 0;
        while (count < num_wanted and !maxHeap.empty()) {
            pair<int, int> cur = maxHeap.top();
            maxHeap.pop();
            if (used[cur.first] < use_limit) {
                result += cur.second;
                used[cur.first] += 1;
                count += 1;
            }
        }
        return result;
    }
};

int main() {
    Solution s;
    vector<int> temp({5,4,3,2,1});
    vector<int> temp1({1,3,3,3,2});
    vector<vector<int>> matrix({
        {0,1,0},
        {1,1,1},
        {0,1,0}
    });
    s.largestValsFromLabels(temp, temp1, 3, 2);
}
