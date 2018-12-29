/*
A and B will claim a number num1 and num2
 1. Then they will start to count number, one at a time, they can decide which one they give this number to.
 2. A starts first, he can choose give this number to himself or B. But the sum of numbers each one get can not exceed the number they claim at first.
 3. If anyone can not count any number anymore, he lose. Thus if after anyone's turn, the sum of the numbers each one get equals the number they claim, then he wins.
 4. A and B can only pick number from fibonacci sequence: 1, 2, 3, 5, 8, ...
 
 Input:
 the number A and B claims as num1 and num2
 num1, num2 <= 10000
 
 Output:
 who will win, "A" stands for A, "B" stands for B
 
 Example:
 Input: 1 4
 output: "A"
 
 Input: 3 4
 output: "A"
 
 Input: 4 4
 output: "B"
 
 Input: 1 5
 output: "B"
 */

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

/*
 A typical DP program
 we can start from count one number sum, then let A and B count to the sum
 it is obvious that dp[1] = "A", dp[2] = "A", dp[3] = "A"
 Then for dp[4], there is no fibonacci number equals 4, but after subtract a fibonacci number from 4, which is
 1, 2, or 3, the left number is 3, 2, and 1. The result of dp[4 - valid_fibonacci_num] = "A"
 Then dp[4] = "B"
 
 So from this we can know for a sum,
 if sum == fibonacci_num
 then A wins
 
 else if all the numbers < sum, dp[number] == "A", number == sum - valid_fibonacci_num
 then B wins
 
 else if any of the number < sum, dp[number] == "B", number == sum - valid_fibonacci_num
 then A wins
 
 then let's consider the situation for two numbers,
 
 if num1 A wins and num2 A wins separately, then final B wins
 cause A win be the last to count num1, then B will be the first to count num2 and B wins at last.
 
 if num1 B wins and num2 B wins separately, then B wins
 cause B will be the last to count num1, and A will be the first count num2, then B last to count num2 at last.
 
 if num1 A wins and num2 wins separately or vice versa, then A wins
 cause A can count the number he wins first, and then another number, and win at last
 
 here actually we can say A and B as the first one to count a number win at last or the second one to count a number win
 at last, which is easier to understand.
 */
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
