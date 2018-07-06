/*
 We have a string S of lowercase letters, and an integer array shifts.
 
 Call the shift of a letter, the next letter in the alphabet, (wrapping around so that 'z' becomes 'a').
 
 For example, shift('a') = 'b', shift('t') = 'u', and shift('z') = 'a'.
 
 Now for each shifts[i] = x, we want to shift the first i+1 letters of S, x times.
 
 Return the final string after all such shifts to S are applied.
 
 Example 1:
 
 Input: S = "abc", shifts = [3,5,9]
 Output: "rpl"
 Explanation:
 We start with "abc".
 After shifting the first 1 letters of S by 3, we have "dbc".
 After shifting the first 2 letters of S by 5, we have "igc".
 After shifting the first 3 letters of S by 9, we have "rpl", the answer.
 Note:
 
 1 <= S.length = shifts.length <= 20000
 0 <= shifts[i] <= 10 ^ 9
 */

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <map>
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
    string shiftingLetters(string S, vector<int>& shifts) {
        long sum = 0;
        for (int i = S.size() - 1; i >= 0; i--) {
            sum += shifts[i];
            long move = (S[i] - 'a') + sum;
            S[i] = (move % 26) + 'a';
        }
        return S;
    }
};
