/*
https://leetcode.com/problems/find-building-where-alice-and-bob-can-meet/description/
2940. Find Building Where Alice and Bob Can Meet

You are given a 0-indexed array heights of positive integers, where heights[i] represents the height of the ith
building.

If a person is in building i, they can move to any other building j if and only if i < j and heights[i] < heights[j].

You are also given another array queries where queries[i] = [ai, bi]. On the ith query, Alice is in building ai while
Bob is in building bi.

Return an array ans where ans[i] is the index of the leftmost building where Alice and Bob can meet on the ith query. If
Alice and Bob cannot move to a common building on query i, set ans[i] to -1.



Example 1:

Input: heights = [6,4,8,5,2,7], queries = [[0,1],[0,3],[2,4],[3,4],[2,2]]
Output: [2,5,-1,5,2]
Explanation: In the first query, Alice and Bob can move to building 2 since heights[0] < heights[2] and heights[1] <
heights[2]. In the second query, Alice and Bob can move to building 5 since heights[0] < heights[5] and heights[3] <
heights[5]. In the third query, Alice cannot meet Bob since Alice cannot move to any other building. In the fourth
query, Alice and Bob can move to building 5 since heights[3] < heights[5] and heights[4] < heights[5]. In the fifth
query, Alice and Bob are already in the same building. For ans[i] != -1, It can be shown that ans[i] is the leftmost
building where Alice and Bob can meet. For ans[i] == -1, It can be shown that there is no building where Alice and Bob
can meet. Example 2:

Input: heights = [5,3,8,2,6,1,4,6], queries = [[0,7],[3,5],[5,2],[3,0],[1,6]]
Output: [7,6,-1,4,6]
Explanation: In the first query, Alice can directly move to Bob's building since heights[0] < heights[7].
In the second query, Alice and Bob can move to building 6 since heights[3] < heights[6] and heights[5] < heights[6].
In the third query, Alice cannot meet Bob since Bob cannot move to any other building.
In the fourth query, Alice and Bob can move to building 4 since heights[3] < heights[4] and heights[0] < heights[4].
In the fifth query, Alice can directly move to Bob's building since heights[1] < heights[6].
For ans[i] != -1, It can be shown that ans[i] is the leftmost building where Alice and Bob can meet.
For ans[i] == -1, It can be shown that there is no building where Alice and Bob can meet.



Constraints:

1 <= heights.length <= 5 * 104
1 <= heights[i] <= 109
1 <= queries.length <= 5 * 104
queries[i] = [ai, bi]
0 <= ai, bi <= heights.length - 1
*/
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <cmath>
#include <queue>
#include <set>
#include <stack>
#include <stdio.h>
using namespace std;
/*
Step 1
For each query [i,j],
if i < j and A[i] < A[j], then Alice and Bob meet at j.
if i > j and A[i] > A[j], then Alice and Bob meet at i.
if i == j, then Alice and Bob already meet at i.

Step 2
For the remaining queries,
we arrange them by position,
a query [i,j] can be answered after index max(i,j),

We will(not now) put a query in a minimum priority queue,
sorted by key max(A[i], A[j]),
so we can answer the query with minimum height first.

Step 3
Then we iterate heights A[i] from left to right,
and check if we can answer any not answered queries.
After we answer all queries we can answer with A[i],
we will push new queries that we can answer from now,
new queries are arranged from step 2.

Step 4
Finally return the answer res.
 */
// it is actually binding each query to a building with the query index and max_height of that query
class Solution {
public:
    vector<int> leftmostBuildingQueries(vector<int>& heights, vector<vector<int>>& queries) {
        int bild_cnt = heights.size();
        int query_cnt = queries.size();
        vector<vector<vector<int>>> building_with_query(bild_cnt);
        vector<int> rst(query_cnt, -1);
        // Step 1
        for (int query_idx = 0; query_idx < query_cnt; query_idx++) {
            int i = queries[query_idx][0];
            int j = queries[query_idx][1];
            if (i < j && heights[i] < heights[j]) {
                rst[query_idx] = j;
            } else if (i > j && heights[i] > heights[j]) {
                rst[query_idx] = i;
            } else if (i == j) {
                rst[query_idx] = i;
            } else {  // Step 2
                int max_height = max(heights[i], heights[j]);
                building_with_query[max(i, j)].push_back({max_height, query_idx});
            }
        }

        // Step 3
        // min heap with the least element at top
        priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> pq;
        for (int i = 0; i < bild_cnt; i++) {
            while (!pq.empty() && pq.top()[0] < heights[i]) {
                rst[pq.top()[1]] = i;
                pq.pop();
            }

            for (auto& q : building_with_query[i]) {
                pq.push(q);
            }
        }
        return rst;
    }
};
