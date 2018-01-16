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
    int minSwapsCouples(vector<int>& row) {
        int result = 0;
        int n = row.size();
        vector<int> pos(n , 0);
        
        for (int i = 0; i < n; i++) {
            pos[row[i]] = i;
        }
        for (int i = 0; i < n; i += 2) {
            int odd = row[i] % 2 == 0 ? 1 : -1;
            if (row[i] + odd != row[i + 1]) {
                int couple = pos[row[i] + odd];
                swap(pos[row[i] + odd], pos[row[i + 1]]);
                swap(row[i + 1], row[couple]);
                result += 1;
            }
        }
        
        return result;
    }
};
