/*
 517. Super Washing Machines
 You have n super washing machines on a line. Initially, each washing machine has some sum or is empty.

 For each move, you could choose any m (1 ≤ m ≤ n) washing machines,
 and pass one dress of each washing machine to one of its adjacent washing machines at the same time .

 Given an integer array representing the number of sum in each washing machine from left to right on the line,
 you should find the minimum number of moves to make all the washing machines have the same number of sum.
 If it is not possible to do it, return -1.

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
 It's impossible to make all the three washing machines have the same number of sum.
 Note:
 The range of n is [1, 10000].
 The range of sum number in a super washing machine is [0, 1e5].
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
#include <set>
#include <numeric>
using namespace std;
/*
toLeft: the number of cloths moved to left from this machine
toRight: the number of cloths moved to right from this machine
toLeft and toRight may be negative but it's okay.

====

Hope the 2 examples below are helpful:
Let's say toLeft = 3 and toRight = -4,
which means that this machine must give 3 cloths to its left
(this must be done in at least 3 turns)
and receive 4 cloths from its right (we don't care since another machine will deal with it).
Therefore, res = max(res, 3, -4, -1) = max(res, 3).

Then let's say toLeft = 3 and toRight = 4,
which means that this machine must give 3 cloths to its left,
and also give 4 cloths to its right.
This can be done in at least 3+4 turns.
Therefore, res = max(res, 3, 4, 7) = max(res, 7).
*/
class Solution {
public:
    int findMinMoves(vector<int>& machines) {
        int n = machines.size();
        int sum = accumulate(machines.begin(), machines.end(), 0);
        if (sum % n != 0) {
            return -1;
        }

        int avg = sum / n;
        int toLeft = 0;
        int result = 0;
        for (int i = 0; i < n; ++i) {
            int toRight = machines[i] - avg - toLeft;
            result = max(result, max(toLeft + toRight, max(toLeft, toRight)));
            toLeft = - toRight;
        }
        return result;
    }
};

/*
First we check the sum of dresses in all machines. if that number cannot be divided by count of machines, there is no solution.

Otherwise, we can always transfer a dress from one machine to another,
one at a time until every machines reach the same number,
so there must be a solution.
In this way, the total actions is sum of operations on every machine.

Since we can operate several machines at the same time,
the minium number of moves is the maximum number of necessary operations on every machine.

For a single machine, necessary operations is to transfer dresses from one side to another until sum of both sides
and itself reaches the average number.
We can calculate (required dresses) - (contained dresses) of each side as L and R:

L > 0 && R > 0:
both sides lacks dresses,
and we can only export one dress from current machines at a time,
so result is abs(L) + abs(R)

L < 0 && R < 0:
both sides contains too many dresses,
and we can import dresses from both sides at the same time,
so result is max(abs(L), abs(R))

L < 0 && R > 0 or L > 0 && R < 0:
the side with a larger absolute value will import/export its extra dresses from/to current machine or other side,
so result is max(abs(L), abs(R))

For example, [1, 0, 5], average is 2
for 1, L = 0 * 2 - 0 = 0, R = 2 * 2 - 5= -1, result = 1
for 0, L = 1 * 2 - 1= 1, R = 1 * 2 - 5 = -3, result = 3
for 5, L = 2 * 2 - 1= 3, R = 0 * 2 - 0= 0, result = 3
so minium moves is 3
*/
class Solution1 { // this one is easier to understand
public:
    int findMinMoves(vector<int>& machines) {
        int n = machines.size();
        int sum = accumulate(machines.begin(), machines.end(), 0);
        if (sum % n != 0) {
            return -1;
        }

        int avg = sum / n;
        int left = 0;
        int right = sum;
        int result = 0;
        for (int i = 0; i < n; i++) {
            right -= machines[i];
            int rightNeed = avg * (n - i - 1) - right;
            int leftNeed = avg * i - left;

            if (leftNeed > 0 and rightNeed > 0) {
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
