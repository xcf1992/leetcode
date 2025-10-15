/*
1320. Minimum Distance to Type a Word Using Two Fingers
https://leetcode.com/problems/minimum-distance-to-type-a-word-using-two-fingers/

A B C D E F
G H I J K L
M N O P Q R
S T U V W X
Y Z
You have a keyboard layout as shown above in the XY plane,
where each English uppercase letter is located at some coordinate,
for example, the letter A is located at coordinate (0,0),
the letter B is located at coordinate (0,1),
the letter P is located at coordinate (2,3)
and the letter Z is located at coordinate (4,1).

Given the string word,
return the minimum total distance to type such string using only two fingers.
The distance between coordinates (x1,y1) and (x2,y2) is |x1 - x2| + |y1 - y2|.

Note that the initial positions of your two fingers are considered free
so don't count towards your total distance,
also your two fingers do not have to start at the first letter or the first two letters.

Example 1:
Input: word = "CAKE"
Output: 3
Explanation:
Using two fingers, one optimal way to type "CAKE" is:
Finger 1 on letter 'C' -> cost = 0
Finger 1 on letter 'A' -> cost = Distance from letter 'C' to letter 'A' = 2
Finger 2 on letter 'K' -> cost = 0
Finger 2 on letter 'E' -> cost = Distance from letter 'K' to letter 'E' = 1
Total distance = 3

Example 2:
Input: word = "HAPPY"
Output: 6
Explanation:
Using two fingers, one optimal way to type "HAPPY" is:
Finger 1 on letter 'H' -> cost = 0
Finger 1 on letter 'A' -> cost = Distance from letter 'H' to letter 'A' = 2
Finger 2 on letter 'P' -> cost = 0
Finger 2 on letter 'P' -> cost = Distance from letter 'P' to letter 'P' = 0
Finger 1 on letter 'Y' -> cost = Distance from letter 'A' to letter 'Y' = 4
Total distance = 6

Example 3:
Input: word = "NEW"
Output: 3

Example 4:
Input: word = "YEAR"
Output: 7

Constraints:
2 <= word.length <= 300
Each word[i] is an English uppercase letter.
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
#include "extra_data_types.hpp"
using namespace std;
/*
Initial the position of two fingers as (0,0).
Iterate the input sttring and track the position of two fingers after tap the last character.
dp[a,b] means with one finger at a and the other at postion b,
the minimum distance we need is dp[a, b].
d(a, b) return the distance moving from a to b. Also if a = 0 we return 0.
*/

/*
Top-Down DP
We have two choices - type the next character using either left or right index finger.
So, we run DFS to find the minimum cost.
Without memoisation, the runtime complexity is O(2 ^ n).

The memoisation dimensions here are quite intuitive -
both fingers' locations and position in the input string.
We have 27 locations for each finger, including the initial 'hovering' state.
*/
class Solution {
private:
    int getDistance(int from, int to) {
        if (from == 26) {
            return 0;
        }
        return abs(from / 6 - to / 6) + abs(from % 6 - to % 6);
    }

    int dfs(string& word, int pos, int left, int right, vector<vector<vector<int>>>& dp) {
        if (pos >= word.size()) {
            return 0;
        }

        if (dp[left][right][pos] == -1) {
            int to = word[pos] - 'A';
            dp[left][right][pos] = min(getDistance(left, to) + dfs(word, pos + 1, to, right, dp),
                getDistance(right, to) + dfs(word, pos + 1, left, to, dp));
        }
        return dp[left][right][pos];
    }
public:
    int minimumDistance(string word) {
        int n = word.size();
        vector<vector<vector<int>>> dp(27, vector<vector<int>>(27, vector<int>(n, -1)));
        return dfs(word, 0, 26, 26, dp);
    }
};
