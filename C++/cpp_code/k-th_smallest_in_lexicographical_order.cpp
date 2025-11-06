/*
440. K-th Smallest in Lexicographical Order
https://leetcode.com/problems/k-th-smallest-in-lexicographical-order/

Given integers n and k,
find the lexicographically k-th smallest integer in the range from 1 to n.

Note:
1 ≤ k ≤ n ≤ 109.

Example:
Input:
n: 13
k: 2
Output:
10

Explanation:
The lexicographical order is [1, 10, 11, 12, 13, 2, 3, 4, 5, 6, 7, 8, 9], so the second smallest number is 10.
Seen this question in a real interview before?
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
https://leetcode.com/problems/k-th-smallest-in-lexicographical-order/discuss/92242/ConciseEasy-to-understand-Java-5ms-solution-with-Explaination

Initially, image you are at node 1 (variable: curr),
the goal is move (k - 1) steps to the target node x. (substract steps from k after moving)
when k is down to 0, curr will be finally at node x, there you get the result.

we don't really need to do a exact k steps preorder traverse of the denary tree,
the idea is to calculate the steps between curr and curr + 1 (neighbor nodes in same level),
in order to skip some unnecessary moves.

Main function
Firstly, calculate how many steps curr need to move to curr + 1.

if the steps <= k, we know we can move to curr + 1, and narrow down k to k - steps.

else if the steps > k,
that means the curr + 1 is actually behind the target node x in the preorder path,
we can't jump to curr + 1.
What we have to do is to move forward only 1 step (curr * 10 is always next preorder node)
and repeat the iteration.

calSteps function

how to calculate the steps between curr and curr + 1?
Here we come up a idea to calculate by level.
Let n1 = curr,
n2 = curr + 1.
n2 is always the next right node beside n1's right most node (who shares the same ancestor "curr")
(refer to the pic, 2 is right next to 1, 20 is right next to 19, 200 is right next to 199).

so, if n2 <= n,
what means n1's right most node exists,
we can simply add the number of nodes from n1 to n2 to steps.

else if n2 > n,
what means n (the biggest node) is on the path between n1 to n2,
add (n + 1 - n1) to steps.

organize this flow to "steps += Math.min(n + 1, n2) - n1; n1 *= 10; n2 *= 10;"
            1                           2
        /   |   \                   /   |   \
       10   11...19                20   21...29
*/
class Solution {
private:
    /*
     * we need to calculate how many elements are there between left and right
     * so for each level if left <= n, we need to check if all nodes in current level is smaller than n or only a part
     * of them
     */
    int calSteps(long n, long left, long right) {
        int steps = 0;
        while (left <= n) {
            // sicne we need to count distance from n + 1 to ***0, so it is n + 1
            steps += min(n + 1, right) - left;
            left *= 10;
            right *= 10;
        }
        return steps;
    }

public:
    int findKthNumber(int n, int k) {
        int cur = 1;
        k -= 1;
        // k used as left steps
        while (k > 0) {
            int steps = calSteps(n, cur, cur + 1);
            if (steps <= k) {
                cur += 1;
                k -= steps;
            } else {
                cur *= 10;
                k -= 1;
            }
        }
        return cur;
    }
};

/*
Input:
957747794
424238336

Time limit exceed
*/
class Solution1 {
private:
    int find(int n, int k, long long number, int& rank) {
        if (rank == k) {
            return number;
        }

        for (int digit = 0; digit <= 9; digit++) {
            long long temp = number * 10 + digit;
            if (temp > n) {
                break;
            }
            rank += 1;
            int result = find(n, k, temp, rank);
            if (result != -1) {
                return result;
            }
        }
        return -1;
    }

public:
    int findKthNumber(int n, int k) {
        int rank = 0;
        int result = -1;
        for (int i = 1; i <= 9; i++) {
            if (i > n) {
                break;
            }
            rank += 1;
            result = find(n, k, i, rank);
            if (result != -1) {
                break;
            }
        }
        return result;
    }
};