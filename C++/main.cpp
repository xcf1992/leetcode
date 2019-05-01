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
#include <numeric>
using namespace std;

class Solution {
private:
    int count(vector<int>& balance, int start) {
        if (start == balance.size()) {
            return 0;
        }

        int result = INT_MAX;
        for (int i = start + 1; i < balance.size(); ++i) {
            if (balance[start] * balance[i] < 0) {
                balance[i] = balance[i] + balance[start];
                result = min(result, 1 + count(balance, start + 1));
                balance[i] = balance[i] - balance[start];
            }
        }
        return result;
    }
public:
    int minTransfers(vector<vector<int>> transactions) {
        map<int, int> balance;
        for (vector<int>& transaction : transactions) {
            balance[transaction[0]] -= transaction[2];
            balance[transaction[1]] += transaction[2];
        }

        vector<int> nonZeroBalance;
        for (auto it = balance.begin(); it != balance.end(); ++it) {
            if (it -> second != 0) {
                nonZeroBalance.push_back(it -> second);
            }
        }

        return count(nonZeroBalance, 0);
    }
};


int main() {
    Solution s;
    int i = s.minTransfers({{1,5,8},{8,9,8},{2,3,9},{4,3,1}});
    return 0;
}
