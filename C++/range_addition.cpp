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
    vector<int> getModifiedArray(int length, vector<vector<int>>& updates) {
        vector<int> result(length, 0);
        for (int i = 0; i < updates.size(); i++) {
            result[updates[i][0]] += updates[i][2];
            if (updates[i][1] + 1 < length) {
                result[updates[i][1] + 1] -= updates[i][2];
            }
        }

        for (int i = 1; i < length; i++) {
            result[i] += result[i - 1];
        }

        return result;
    }
};

int main() {
    Solution s;
    return 0;
}