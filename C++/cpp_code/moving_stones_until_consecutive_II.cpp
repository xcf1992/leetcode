/*
1040. Moving Stones Until Consecutive II

On an infinite number line, the position of the i-th stone is given by stones[i].
Call a stone an endpoint stone if it has the smallest or largest position.

Each turn, you pick up an endpoint stone and move it to an unoccupied position so that it is no longer an endpoint stone.

In particular, if the stones are at say, stones = [1,2,5],
you cannot move the endpoint stone at position 5,
since moving it to any position (such as 0, or 3) will still keep that stone as an endpoint stone.

The game ends when you cannot make any more moves, ie. the stones are in consecutive positions.

When the game ends, what is the minimum and maximum number of moves that you could have made?
Return the answer as an length 2 array: answer = [minimum_moves, maximum_moves]

Example 1:
Input: [7,4,9]
Output: [1,2]
Explanation:
We can move 4 -> 8 for one move to finish the game.
Or, we can move 9 -> 5, 4 -> 6 for two moves to finish the game.

Example 2:
Input: [6,5,4,3,10]
Output: [2,3]
We can move 3 -> 8 then 10 -> 7 to finish the game.
Or, we can move 3 -> 7, 4 -> 8, 5 -> 9 to finish the game.
Notice we cannot move 10 -> 2 to finish the game, because that would be an illegal move.

Example 3:
Input: [100,101,104,102,103]
Output: [0,0]

Note:
3 <= stones.length <= 10^4
1 <= stones[i] <= 10^9
stones[i] have distinct values.
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
1. For the max move,
we should either move s[0] to s[1] + 1 or move s[n-1] to s[n-2] - 1
after that we should move the stone until all of them are in a window of size n,
so the moves will be max(s[n - 1] - s[1] + 1 - (n - 1), s[n - 2] - s[0] + 1 - (n - 1))
                        -------------------   ------
------------------------> the size of gap       # of stones already in the gap

求最大值：

每次可以移动最左端或者最右端，因此最大值一定是要么第一次移动的是最左端，要么第一次移动的是最右端；

如果第一次移动最右端，那么第一步一定是移到最右边开始第二个的前面，即stones[n-2]，n为stones的长度，并且最左的位置是stones[0]，
因此移动距离就是stones[n-2]-stones[0]-1-(n-3)，也就是当前区间内部的位置，减去内部已经有石头的数量
(有3个不在区间内部，分别是区间左右端2个和最后1个stones[n-1])，剩下的空位置就是能移动石头的位置。

例如：[1,3,5,7,12,65]，1到12之间还剩下7个空位置，也就是先移动右端，能最多移动7次。

同样的，如果第一次移动最左端，那么第一步一定是移动到最左边开始第二个的后面，即stones[1]，它的最右端即是stones[n-1]，
因此移动距离就是stones[n-1]-stones[1]-1-(n-3)；

例如：[1,3,5,7,12,65]，3到65之间还剩下58个空位置，也就是先移动左端，能最多移动58次。

上面两个值取最大值就是当前能移动的最大步数。

求最小值：

window slide，不断构造一个区间，这个区间[i,j]满足，区间的长度不会大于石头的数量，
即这个区间是可以被区间外部的石头塞满的(可以塞不下，但不能有空隙)。

接着检查如果这个区间是连续的并且外部非连续的只有1个，那么这是一种特殊情况，返回2。

例如[1,2,3,4,10]，区间[1,2,3,4]是连续的，但外部非连续的只有1个，需要将1放到6的位置，再将10放到5的位置。

如果不是以上的特殊情况，那么不需要检查区间内部是否连续了，也就是将除了[i,j]区间以外的数字放入[i,j]区间，放不下的要让它们连续，只需要n-(j-i+1)步。

例如：

区间内部不连续：

[1,4,7,9,20,30]，当前i为0，j为1，那么将[7,9,20,30]与[1,4]连续只需要4步
将30放入6的位置，[1,4,6,7,9,20]；
将20放入5的位置，[1,4,5,6,7,9]；
将9放入3的位置，[1,3,4,5,6,7]；
将7放入2的位置，[1,2,3,4,5,6]，结束。

区间内部连续：
[1,2,3,56,89]，i为0，j为2，只需要2步
将89放入5的位置，[1,2,3,5,56]；
将56放入4的位置，[1,2,3,4,5]，结束。
*/

/*
in case of n stones,
we need to find a consecutive n positions and move the stones in.

This idea led the solution with sliding windows.

Slide a window of size N, and find how many stones are already in this window.
We want moves other stones into this window.
For each missing stone, we need at least one move.

Generally, the number of missing stones and the moves we need are the same.
Only one corner case in this problem, we need to move the endpoint to no endpoint.

For case 1,2,4,5,10,
1 move needed from 10 to 3.

For case 1,2,3,4,10,
2 move needed from 1 to 6, then from 10 to 5.
*/
class Solution {
public:
    vector<int> numMovesStonesII(vector<int>& stones) {
        sort(stones.begin(), stones.end());

        int n = stones.size();
        int minMove = n;
        int i = 0;
        for (int j = 0; j < n; ++j) {
            while (stones[j] - stones[i] + 1 > n) { // this is not valid as the window size is larger than n
                i += 1;
            }

            // j - i + 1 is the number of stones already in this interval
            if (j - i + 1 == n - 1 and stones[j] - stones[i] + 1 == n - 1) {
                minMove = min(minMove, 2);
            }
            else {
                minMove = min(minMove, n - (j - i + 1));
            }
        }
        return {minMove, max(stones[n - 1] - stones[1] + 2 - n, stones[n - 2] - stones[0] + 2 - n)};
    }
};
