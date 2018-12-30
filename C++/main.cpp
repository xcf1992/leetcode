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
    bool firstOneWin(int num, unordered_map<int, bool>& dp, unordered_set<int>& fibonacci) {
        if (dp.find(num) != dp.end()) {
            return dp[num];
        }
        if (fibonacci.find(num) != fibonacci.end()) {
            dp[num] = true;
            return true;
        }
        
        int num1 = 1;
        int num2 = 2;
        int temp = num - num1;
        while (temp > 0) {
            if (!firstOneWin(temp, dp, fibonacci)) {
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
    
    unordered_set<int> generate(int num) {
        unordered_set<int> result;
        int num1 = 1;
        int num2 = 2;
        while (num1 <= num) {
            result.insert(num1);
            int temp = num1 + num2;
            num1 = num2;
            num2 = temp;
        }
        return result;
    }
public:
    string countNumberGame(int num1, int num2) {
        int num = max(num1, num2);
        unordered_set<int> fibonacci = generate(num);
        unordered_map<int, bool> dp;
        if (firstOneWin(num1, dp, fibonacci) == firstOneWin(num2, dp, fibonacci)) {
            return "Xiaobin Win";
        }
        return "Xiaoai Win";
    }
};


int main() {
    Solution s;
    cout << s.countNumberGame(1, 4);
    return 0;
}
