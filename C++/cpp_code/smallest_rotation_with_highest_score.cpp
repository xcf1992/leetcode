/*
798. Smallest Rotation with Highest Score

Given an array A,
we may rotate it by a non-negative integer K
so that the array becomes A[K], A[K+1], A{K+2], ... A[A.length - 1], A[0], A[1], ..., A[K-1].
Afterward, any entries that are less than or equal to their index are worth 1 point.

For example, if we have [2, 4, 1, 3, 0], and we rotate by K = 2, it becomes [1, 3, 0, 2, 4].
This is worth 3 points because 1 > 0 [no points], 3 > 1 [no points], 0 <= 2 [one point], 2 <= 3 [one point], 4 <= 4 [one point].

Over all possible rotations,
return the rotation index K that corresponds to the highest score we could receive.
If there are multiple answers,
return the smallest such index K.

Example 1:
Input: [2, 3, 1, 4, 0]
Output: 3
Explanation:
Scores for each K are listed below:
K = 0,  A = [2,3,1,4,0],    score 2
K = 1,  A = [3,1,4,0,2],    score 3
K = 2,  A = [1,4,0,2,3],    score 3
K = 3,  A = [4,0,2,3,1],    score 4
K = 4,  A = [0,2,3,1,4],    score 3
So we should choose K = 3, which has the highest score.

Example 2:
Input: [1, 3, 0, 2, 4]
Output: 0
Explanation:  A will always have 3 points no matter how it shifts.
So we will choose the smallest K, which is 0.

Note:
A will have length at most 20000.
A[i] will be in the range [0, A.length].
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
Lose point
(i - A[i] + N) % N is the value of K making A[i]'s index just equal to A[i].
For example, If A[6] = 1, then K = (6 - A[6]) % 6 = 5 making A[6] to index 1 of new array.
So when K=5, we get this point for A[6]
Then if K is bigger when K = (i - A[i] + 1) % N, we start to lose this point, making our score -= 1
All I have done is record the value of K for all A[i] where we will lose points.

Explanation of codes

Search the index where score decrease and record this changement to a list change.
A simple for loop to calculate the score for every K value.
score[K] = score[K-1] + change[K]
In my codes I accumulated changes so I get the changed score for every K value compared to K=0
Find the index of best score.

The second for loop actually calculate total changes in k step moving left via k - 1, so you could think of
totalChange[k] = totalChange[k - 1] + change[k] + 1, as an equivalent as change[k] += change[k - 1] + 1.

The above applies well when 0 < A[i] < A.length, but what if A[i] = 0 or A[i] = A.length()?
Their turning point k = (i - 0(or N) + 1 + N) % N = i + 1 is not real, because they never lose point!
(0 always counts one point, and N never).
However, assume that 0(or N) is at position i in original array, and it needs i steps to move to position 0.
So when it arrives at the turning point i + 1, it is actually moving from 0 to A.length - 1,
which means we simultaneously subtract 1(in change[k]) and add 1 for totalChange[k].

Hope this could help.

Key point
Don't calculate the score for K=0, we don't need it at all.
(I see almost all other solutions did)
The key point is to find out how score changes when K++

For one step move left, we can figure out how points change with respect to the last position.
For each element, it must satisfy one of the three cases when moving from position i to position (i - 1 + N) % N:

No point get and no point lose, this happens when A[i] > i;
One point get, this happens when it moves from 0 to N - 1;
One point lost, this happens when A[i] == i and moves to i - 1.
change[k] actually records all the lost points after k steps moving left,
by calculating how many elements would lose point at k.
The relationship of turning point k and initial position of element i is: k = (i - A[i] + 1 + N) % N.
So by looping i, we can calculate the vector of change[k].

The second for loop actually calculate total changes in k step moving left via k - 1, so you could think of
totalChange[k] = totalChange[k - 1] + change[k] + 1, as an equivalent as change[k] += change[k - 1] + 1.

The above applies well when 0 < A[i] < A.length, but what if A[i] = 0 or A[i] = A.length()?
Their turning point k = (i - 0(or N) + 1 + N) % N = i + 1 is not real,
because they never lose point! (0 always counts one point, and N never).
However, assume that 0(or N) is at position i in original array, and it needs i steps to move to position 0.
So when it arrives at the turning point i + 1, it is actually moving from 0 to A.length - 1,
which means we simultaneously subtract 1(in change[k]) and add 1 for totalChange[k].

Hope this could help.
*/
class Solution {
public:
    int bestRotation(vector<int> &A) {
        int n = A.size();
        vector<int> change(n, 0);
        for (int i = 0; i < n; i++) {
            change[(n - A[i] + i + 1) % n] -= 1;
        }

        int score = change[0];
        int result = 0;
        for (int i = 1; i < n; i++) {
            // you can aways get one point for moving an element from index 0 to index N-1
            // so we always plus one for each increase i in second loop
            change[i] += change[i - 1] + 1;
            if (change[i] > score) {
                score = change[i];
                result = i;
            }
        }
        return result;
    }
};