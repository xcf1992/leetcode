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
    bool firstOneWin(int num, unordered_map<int, bool>& dp) {
        if (dp.find(num) != dp.end()) {
            return dp[num];
        }
        
        int num1 = 1;
        int num2 = 2;
        int temp = num - num1;
        while (temp > 0) {
            if (!firstOneWin(temp, dp)) {
                dp[num] = true;
                return true;
            }
            
            int next = num1 + num2;
            num1 = num2;
            num2 = next;
            temp = num - num1;
        }
        dp[num] = false;
        return false;
    }
public:
    string countNumberGame(int num1, int num2) {
        unordered_map<int, bool> dp;
        dp[1] = true;
        dp[2] = true;
        if (firstOneWin(num1, dp) == firstOneWin(num2, dp)) {
            return "Xiaobin Win";
        }
        return "Xiaoai Win";
    }
};


int main() {
    Solution s;
    cout << s.countNumberGame(1, 5);
    return 0;
}
