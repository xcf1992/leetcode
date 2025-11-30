/*
https://leetcode.com/problems/taking-maximum-energy-from-the-mystic-dungeon/description/
3147. Taking Maximum Energy From the Mystic Dungeon

In a mystic dungeon, n magicians are standing in a line. Each magician has an attribute that gives you energy. Some
magicians can give you negative energy, which means taking energy from you.

You have been cursed in such a way that after absorbing energy from magician i, you will be instantly transported to
magician (i + k). This process will be repeated until you reach the magician where (i + k) does not exist.

In other words, you will choose a starting point and then teleport with k jumps until you reach the end of the
magicians' sequence, absorbing all the energy during the journey.

You are given an array energy and an integer k. Return the maximum possible energy you can gain.

Note that when you are reach a magician, you must take energy from them, whether it is negative or positive energy.



Example 1:

Input: energy = [5,2,-10,-5,1], k = 3

Output: 3

Explanation: We can gain a total energy of 3 by starting from magician 1 absorbing 2 + 1 = 3.

Example 2:

Input: energy = [-2,-3,-1], k = 2

Output: -1

Explanation: We can gain a total energy of -1 by starting from magician 2.



Constraints:

1 <= energy.length <= 105
-1000 <= energy[i] <= 1000
1 <= k <= energy.length - 1
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
#include <climits>
#include <set>
using namespace std;

class Solution {
public:
    int maximumEnergy(vector<int>& energy, int k) {
        int n = energy.size();
        vector<int> dp(n);
        int result = INT_MIN;
        for (int i = n - 1; i >= 0; --i) {
            dp[i] = energy[i] + ((i + k < n) ? dp[i + k] : 0);
            result = max(result, dp[i]);
        }
        return result;
    }
};

class Solution {
public:
    int maximumEnergy(vector<int>& energy, int k) {
        vector<int> dp(k, 0);
        for (int i = 0; i < energy.size(); i++) {
            dp[i % k] = max(dp[i % k] + energy[i], energy[i]);
        }

        int rst = dp[0];
        for (const int & e : dp) {
            rst = max(rst, e);
        }
        return rst;
    }
};