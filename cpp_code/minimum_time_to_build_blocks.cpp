/*
1199. Minimum Time to Build Blocks
https://leetcode.com/problems/minimum-time-to-build-blocks/

You are given a list of blocks,
where blocks[i] = t means that the i-th block needs t units of time to be built.
A block can only be built by exactly one worker.

A worker can either split into two workers (number of workers increases by one)
or build a block then go home. Both decisions cost some time.
The time cost of spliting one worker into two workers is given as an integer split.
Note that if two workers split at the same time, they split in parallel so the cost would be split.
Output the minimum time needed to build all blocks.
Initially, there is only one worker.

Example 1:
Input: blocks = [1], split = 1
Output: 1
Explanation: We use 1 worker to build 1 block in 1 time unit.

Example 2:
Input: blocks = [1,2], split = 5
Output: 7
Explanation: We split the worker into 2 workers in 5 time units then assign each of them to a block so the cost is 5 + max(1, 2) = 7.

Example 3:
Input: blocks = [1,2,3], split = 1
Output: 4
Explanation: Split 1 worker into 2, then assign the first worker to the last block and split the second worker into 2.
Then, use the two unassigned workers to build the first two blocks.
The cost is 1 + max(3, 1 + max(1, 2)) = 4.

Constraints:
1 <= blocks.length <= 1000
1 <= blocks[i] <= 10^5
1 <= split <= 100
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
#include <numeric>
using namespace std;
/*
huffman, https://leetcode.com/problems/minimum-time-to-build-blocks/discuss/387035/Python%3A-O(n-log-n)-using-Huffman's-Algorithm-(priority-queue)-with-explanation.

We can model this entire question as a binary tree that we need to construct with a minimum max depth cost.
Each of the blocks is a leaf node, with a cost of its face value.
And then each inner node will be of cost split.
nodes that are sitting at the same level represent work that is done in parallel.
We know there will be len(blocks) - 1 of these inner nodes,
so the question now is how can we construct the tree such that it has the minimum depth.

For example, a possible (not optimal) tree for the data set
[1, 2, 4, 7, 10] with split cost 3 is:
(Sorry for ascii art, 2 AM is too late at night to do this properly :) )

 ........3
 ...../....\
 .....3.....\
 ../.....\....\
  3.......3....\
 /..\..../..\...\
1...2...4...7...10

This tree has a maximum depth of 16 (3 -> 3 -> 3 -> 7).

So, how can we optimise the construction of this tree? Huffman's algorithm!

I'm going to assume you're familiar with Huffman's algorithm. If not, google it or read this.
Note that it's traditionally used for building compression codes, but there is no reason we can't also use it here.
https://www.geeksforgeeks.org/huffman-coding-greedy-algo-3/

Instead of actually building the whole tree,
we can just keep track of the nodes the huffman algorithm still needs to consider,
as the maximum depth below them.
So put all the leaf node (blocks) onto a priority queue,
and then repeatedly take the 2 smallest off and add split onto the biggest of the 2
(this is Huffman's algorithm, it's greedy) and put the result back onto the priority queue.

Once there is only one left, this is the depth of the root node, and we return it.

It is O(n-log-n) because we are making 2n - 1 insertions into a heap and n removals,
and both heap insertion and removal have a cost of O(log-n).
We drop the constants, giving a final cost of O(n-log-n).

-=-=-=-=-=-=
Observe in reversed way, look each num in blocks as leaf, and merge these leaves with cost "split" until get one root.
Use priority queue to decide the order of merge.
*/
class Solution {
public:
    int minBuildTime(vector<int>& blocks, int split) {
        priority_queue<int, vector<int>, greater<int>> pq;
        for (int b: blocks) {
            pq.push(b);
        }

        while (pq.size() > 1) {
            int a = pq.top();
            pq.pop();
            int b = pq.top();
            pq.pop();
            pq.push(b + split);
        }
        return pq.top();
    }
};

class Solution1 { // 444ms, 14%
private:
    int dfs(int workers, int bCount, vector<int>& blocks, int split, vector<vector<int>>& dp) {
        if (bCount <= 0) {
            return 0;
        }

        if (workers <= 0) {
            return INT_MAX;
        }

        if (workers >= bCount) {
            return blocks[bCount - 1];
        }

        if (dp[bCount][workers] != INT_MAX) {
            return dp[bCount][workers];
        }

        int option1 = max(blocks[bCount - 1], dfs(workers - 1, bCount - 1, blocks, split, dp));
        int option2 = split + dfs(workers * 2, bCount, blocks, split, dp);
        dp[bCount][workers] = min(option1, option2);
        return dp[bCount][workers];
    }
public:
    int minBuildTime(vector<int>& blocks, int split) {
        int n = blocks.size();
        vector<vector<int>> dp(n, vector<int>(n, INT_MAX));
        sort(blocks.begin(), blocks.end());
        return dfs(1, n, blocks, split, dp);
    }
};
