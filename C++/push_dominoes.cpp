/*
 There are N dominoes in a line, and we place each domino vertically upright.
 
 In the beginning, we simultaneously push some of the dominoes either to the left or to the right.
 
 
 
 After each second, each domino that is falling to the left pushes the adjacent domino on the left.
 
 Similarly, the dominoes falling to the right push their adjacent dominoes standing on the right.
 
 When a vertical domino has dominoes falling on it from both sides, it stays still due to the balance of the forces.
 
 For the purposes of this question, we will consider that a falling domino expends no additional force to a falling or already fallen domino.
 
 Given a string "S" representing the initial state. S[i] = 'L', if the i-th domino has been pushed to the left; S[i] = 'R', if the i-th domino has been pushed to the right; S[i] = '.', if the i-th domino has not been pushed.
 
 Return a string representing the final state.
 
 Example 1:
 
 Input: ".L.R...LR..L.."
 Output: "LL.RR.LLRRLL.."
 Example 2:
 
 Input: "RR.L"
 Output: "RR.L"
 Explanation: The first domino expends no additional force on the second domino.
 Note:
 
 0 <= N <= 10^5
 String dominoes contains only 'L', 'R' and '.'
 */

#include <iostream>
#include <sstream>
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
    string pushDominoes(string dominoes) {
        int count = dominoes.size();
        if (count <= 1) {
            return dominoes;
        }
        
        vector<int> distance(count, INT_MAX);
        for (int i = 0; i < dominoes.size(); i++) {
            if (dominoes[i] == 'R') {
                distance[i] = 0;
            }
            else if (dominoes[i - 1] == 'R' && dominoes[i] == '.') {
                dominoes[i] = 'R';
                distance[i] = distance[i - 1] + 1;
            }
        }
        
        int dis = INT_MAX;
        for (int i = count - 1; i >= 0; i--) {
            if (dominoes[i] == 'L') {
                dis = 0;
            }
            else if (dominoes[i + 1] == 'L') {
                dis += 1;
                if (dominoes[i] == '.') {
                    dominoes[i] = 'L';
                }
                else if (dominoes[i] == 'R') {
                    if (dis == distance[i]) {
                        dominoes[i] = '.';
                    }
                    if (dis < distance[i]) {
                        dominoes[i] = 'L';
                    }
                }
            }
        }
        return dominoes;
    }
};
