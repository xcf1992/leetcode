/*
1686. Stone Game VI
https://leetcode.com/problems/stone-game-vi/

Alice and Bob take turns playing a game, with Alice starting first.

There are n stones in a pile. On each player's turn,
they can remove a stone from the pile and receive points based on the stone's value.
Alice and Bob may value the stones differently.

You are given two integer arrays of length n,
aliceValues and bobValues.
Each aliceValues[i] and bobValues[i] represents how Alice and Bob,
respectively, value the ith stone.

The winner is the person with the most points after all the stones are chosen.
If both players have the same amount of points, the game results in a draw.
Both players will play optimally. Both players know the other's values.

Determine the result of the game, and:
If Alice wins, return 1.
If Bob wins, return -1.
If the game results in a draw, return 0.

Example 1:
Input: aliceValues = [1,3], bobValues = [2,1]
Output: 1
Explanation:
If Alice takes stone 1 (0-indexed) first, Alice will receive 3 points.
Bob can only choose stone 0, and will only receive 2 points.
Alice wins.

Example 2:
Input: aliceValues = [1,2], bobValues = [3,1]
Output: 0
Explanation:
If Alice takes stone 0, and Bob takes stone 1, they will both have 1 point.
Draw.

Example 3:
Input: aliceValues = [2,4,3], bobValues = [1,6,7]
Output: -1
Explanation:
Regardless of how Alice plays, Bob will be able to have more points than Alice.
For example, if Alice takes stone 1, Bob can take stone 2, and Alice takes stone 0, Alice will have 6 points to Bob's 7.
Bob wins.

Constraints:
n == aliceValues.length == bobValues.length
1 <= n <= 105
1 <= aliceValues[i], bobValues[i] <= 100
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
#include <numeric>
using namespace std;
/*
Sort stones by their sum value for Alice and Bob.
If a stone is super valued for Alice, Alice wants to take it.
If a stone is super valued for Bob, Alice also wants to take it.
Because she doesn't want Bob to take it.

Explanation
Here is more convinced explanation.
Assume a stone valued [a,b] for Alice and Bod.
Alice takes it, worth a for Alice,
Bob takes it, worth b for Bob,
we can also consider that it worth -b for Alice.
The difference will be a+b.
That's the reason why we need to sort based on a+b.
And Alice and Bob will take one most valued stone each turn.

Complexity
Time O(nlogn)
Space O(n)
*/
class Solution {
public:
    int stoneGameVI(vector<int> &A, vector<int> &B) {
        vector<vector<int> > C;
        int n = A.size();
        for (int i = 0; i < n; ++i) {
            C.push_back({-A[i] - B[i], A[i], B[i]});
        }

        sort(begin(C), end(C));

        int res[2] = {0, 0};
        for (int i = 0; i < n; ++i) {
            res[i % 2] += C[i][1 + i % 2];
        }
        return res[0] == res[1] ? 0 : res[0] > res[1] ? 1 : -1;
    }
};