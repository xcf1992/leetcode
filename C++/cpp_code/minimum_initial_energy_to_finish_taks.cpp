/*
1665. Minimum Initial Energy to Finish Tasks
https://leetcode.com/problems/minimum-initial-energy-to-finish-tasks/

You are given an array tasks where tasks[i] = [actuali, minimumi]:
actuali is the actual amount of energy you spend to finish the ith task.
minimumi is the minimum amount of energy you require to begin the ith task.
For example, if the task is [10, 12] and your current energy is 11,
you cannot start this task. However, if your current energy is 13,
you can complete this task, and your energy will be 3 after finishing it.

You can finish the tasks in any order you like.
Return the minimum initial amount of energy you will need to finish all the tasks.

Example 1:
Input: tasks = [[1,2],[2,4],[4,8]]
Output: 8
Explanation:
Starting with 8 energy, we finish the tasks in the following order:
    - 3rd task. Now energy = 8 - 4 = 4.
    - 2nd task. Now energy = 4 - 2 = 2.
    - 1st task. Now energy = 2 - 1 = 1.
Notice that even though we have leftover energy, starting with 7 energy does not work because we cannot do the 3rd task.

Example 2:
Input: tasks = [[1,3],[2,4],[10,11],[10,12],[8,9]]
Output: 32
Explanation:
Starting with 32 energy, we finish the tasks in the following order:
    - 1st task. Now energy = 32 - 1 = 31.
    - 2nd task. Now energy = 31 - 2 = 29.
    - 3rd task. Now energy = 29 - 10 = 19.
    - 4th task. Now energy = 19 - 10 = 9.
    - 5th task. Now energy = 9 - 8 = 1.

Example 3:
Input: tasks = [[1,7],[2,8],[3,9],[4,10],[5,11],[6,12]]
Output: 27
Explanation:
Starting with 27 energy, we finish the tasks in the following order:
    - 5th task. Now energy = 27 - 5 = 22.
    - 2nd task. Now energy = 22 - 2 = 20.
    - 3rd task. Now energy = 20 - 3 = 17.
    - 1st task. Now energy = 17 - 1 = 16.
    - 4th task. Now energy = 16 - 4 = 12.
    - 6th task. Now energy = 12 - 6 = 6.

Constraints:
1 <= tasks.length <= 105
1 <= actual​i <= minimumi <= 104
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
#include <cfloat>
#include <stdio.h>
#include <map>
#include <set>
#include <list>
#include <numeric>
#include <random>
#include <vector>
#include "extra_data_types.hpp"
using namespace std;
/*
Intuition
Need to sort by minimum - actual


Explanation
We have n investor,
each investor can invest actual energy,
and he think your company have minimum value.

If you already have at least minimum - actual energy,
the investory will invest you actual energy.

Assuming you get all investment,
how many energy you have at least in the end?

We sort by the energy required minimum - actual.
res is our current energy.
Each round we will get energy a and reach max(res + a, m).
Return directly res in the end.


Continue the story
The following explanation is from @kaiwensun, vote for him.

minimum - actual is the "bar" of an investor.
if your company doesn't already have at least minimum - actual energy/value
when the investor is assessing your company,
you don't meet the investor's bar.
They don't want to invest to you.

But don't worry, you can pay some extra energy/money
from your own pocket to reach minimum - actual and meet the bar,
then the investor will invest actual energy.

Eventually, every investor will invest actual to you.
You want to pay as little out-of-pocket energy/money as possible.

So you want your company's energy/value to be as high as possible
before visiting an investor to let it asses your company.

In other words, you want to first visit those investors whose bar is lower.

So we sort by investors by their "bar",
i.e. by their minimum - actual.


Complexity
Time O(sort)
Space O(sort)
*/
class Solution {
public:
    int minimumEffort(vector<vector<int> > &A) {
        int res = 0;
        for (auto &a: A)
            a[0] = a[1] - a[0];
        sort(A.begin(), A.end());
        for (auto &a: A)
            res = max(res + a[1] - a[0], a[1]);
        return res;
    }
};