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
    int findLongestChain(vector<vector<int>>& pairs) {
        sort(pairs.begin(), pairs.end(), [](vector<int>& a, vector<int>& b) {
            return a[1] < b[1];
        });
        int result = 1;
        int end = pairs[0][1];
        for (int i = 1; i < pairs.size(); i++) {
            if (end < pairs[i][0]) {
                result += 1;
                end = pairs[i][1];
            }
        }
        return result;
    }
};