/*
 You have n super washing machines on a line. Initially, each washing machine has some dresses or is empty.
 
 For each move, you could choose any m (1 ≤ m ≤ n) washing machines, and pass one dress of each washing machine to one of its adjacent washing machines at the same time .
 
 Given an integer array representing the number of dresses in each washing machine from left to right on the line, you should find the minimum number of moves to make all the washing machines have the same number of dresses. If it is not possible to do it, return -1.
 
 Example1
 
 Input: [1,0,5]
 
 Output: 3
 
 Explanation:
 1st move:    1     0 <-- 5    =>    1     1     4
 2nd move:    1 <-- 1 <-- 4    =>    2     1     3
 3rd move:    2     1 <-- 3    =>    2     2     2
 Example2
 
 Input: [0,3,0]
 
 Output: 2
 
 Explanation:
 1st move:    0 <-- 3     0    =>    1     2     0
 2nd move:    1     2 --> 0    =>    1     1     1
 Example3
 
 Input: [0,2,0]
 
 Output: -1
 
 Explanation:
 It's impossible to make all the three washing machines have the same number of dresses.
 Note:
 The range of n is [1, 10000].
 The range of dresses number in a super washing machine is [0, 1e5].
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
#include <set>
using namespace std;

class Solution {
public:
    int findMinMoves(vector<int>& machines) {
        int machineNum = machines.size();
        int dresses = 0;
        for (int dress : machines) {
            dresses += dress;
        }
        
        if (dresses % machineNum != 0) {
            return -1;
        }
        
        int avg = dresses / machineNum;
        int result = 0;
        int left = 0;
        int right = dresses;
        for (int i = 0; i < machineNum; i++) {
            right -= machines[i];
            int rightNeed = avg * (machineNum - i - 1) - right;
            int leftNeed = avg * i - left;
            
            if (leftNeed > 0 && rightNeed > 0) {
                result = max(result, leftNeed + rightNeed);
            }
            else {
                result = max(result, max(abs(leftNeed), abs(rightNeed)));
            }
            left += machines[i];
        }
        return result;
    }
};
