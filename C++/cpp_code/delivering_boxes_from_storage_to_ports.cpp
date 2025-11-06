/*
1687. Delivering Boxes from Storage to Ports
https://leetcode.com/problems/delivering-boxes-from-storage-to-ports/

You have the task of delivering some boxes from storage to their ports using only one ship.
However, this ship has a limit on the number of boxes and the total weight that it can carry.

You are given an array boxes, where boxes[i] = [ports​​i​, weighti],
and three integers portsCount, maxBoxes, and maxWeight.
ports​​i is the port where you need to deliver the ith box and weightsi is the weight of the ith box.
portsCount is the number of ports.
maxBoxes and maxWeight are the respective box and weight limits of the ship.
The boxes need to be delivered in the order they are given.
The ship will follow these steps:

The ship will take some number of boxes from the boxes queue,
not violating the maxBoxes and maxWeight constraints.
For each loaded box in order,
the ship will make a trip to the port the box needs to be delivered to and deliver it.
If the ship is already at the correct port, no trip is needed, and the box can immediately be delivered.
The ship then makes a return trip to storage to take more boxes from the queue.
The ship must end at storage after all the boxes have been delivered.

Return the minimum number of trips the ship needs to make to deliver all boxes to their respective ports.

Example 1:
Input: boxes = [[1,1],[2,1],[1,1]], portsCount = 2, maxBoxes = 3, maxWeight = 3
Output: 4
Explanation: The optimal strategy is as follows:
- The ship takes all the boxes in the queue, goes to port 1, then port 2, then port 1 again, then returns to storage. 4
trips. So the total number of trips is 4. Note that the first and third boxes cannot be delivered together because the
boxes need to be delivered in order (i.e. the second box needs to be delivered at port 2 before the third box). Example
2: Input: boxes = [[1,2],[3,3],[3,1],[3,1],[2,4]], portsCount = 3, maxBoxes = 3, maxWeight = 6 Output: 6 Explanation:
The optimal strategy is as follows:
- The ship takes the first box, goes to port 1, then returns to storage. 2 trips.
- The ship takes the second, third and fourth boxes, goes to port 3, then returns to storage. 2 trips.
- The ship takes the fifth box, goes to port 3, then returns to storage. 2 trips.
So the total number of trips is 2 + 2 + 2 = 6.
Example 3:
Input: boxes = [[1,4],[1,2],[2,1],[2,1],[3,2],[3,4]], portsCount = 3, maxBoxes = 6, maxWeight = 7
Output: 6
Explanation: The optimal strategy is as follows:
- The ship takes the first and second boxes, goes to port 1, then returns to storage. 2 trips.
- The ship takes the third and fourth boxes, goes to port 2, then returns to storage. 2 trips.
- The ship takes the fifth and sixth boxes, goes to port 3, then returns to storage. 2 trips.
So the total number of trips is 2 + 2 + 2 = 6.
Example 4:
Input: boxes = [[2,4],[2,5],[3,1],[3,2],[3,7],[3,1],[4,4],[1,3],[5,2]], portsCount = 5, maxBoxes = 5, maxWeight = 7
Output: 14
Explanation: The optimal strategy is as follows:
- The ship takes the first box, goes to port 2, then storage. 2 trips.
- The ship takes the second box, goes to port 2, then storage. 2 trips.
- The ship takes the third and fourth boxes, goes to port 3, then storage. 2 trips.
- The ship takes the fifth box, goes to port 3, then storage. 2 trips.
- The ship takes the sixth and seventh boxes, goes to port 3, then port 4, then storage. 3 trips.
- The ship takes the eighth and ninth boxes, goes to port 1, then port 5, then storage. 3 trips.
So the total number of trips is 2 + 2 + 2 + 2 + 3 + 3 = 14.

Constraints:
1 <= boxes.length <= 105
1 <= portsCount, maxBoxes, maxWeight <= 105
1 <= ports​​i <= portsCount
1 <= weightsi <= maxWeight
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
Usually, we will greedily take as many boxes as possible.
But in one case,
the last several small boxes in this trip,
are going to the same port as the first box in the next trips.
We may probably let it go in the next trip,
we waste a little weight, but we can save a trip.

Explanation
The overall solution is a sliding window problem.
So you need to make sure you can understand basic sliding window solution.

We start to delievery boxes from each A[i],
and we load boxes from A[i] to A[j] as many as possible.
Also we record the biggest lastj that has the same port target,
that isA[lastj][0] = A[j][0].

dp[i] means the number trips we need to finish the first i boxes.
Note that we can calulated dp[i] for each i,
but here we apply a greediest solution and a second greediest solution,
we don't calculate and we don't need all dp[i] in this process.

Complexity
Time O(N)
Space O(N)
*/
class Solution {
public:
    int boxDelivering(vector<vector<int>>& A, int portsCount, int B, int W) {
        int n = A.size(), need = 0, j = 0, lastj = 0;
        vector<int> dp(n + 1, 200000);
        dp[0] = 0;
        for (int i = 0; i < n; ++i) {
            while (j < n && B > 0 && W >= A[j][1]) {
                B -= 1;
                W -= A[j][1];
                if (j == 0 || A[j][0] != A[j - 1][0]) {
                    lastj = j;
                    need++;
                }
                j++;
            }
            dp[j] = min(dp[j], dp[i] + need + 1);
            dp[lastj] = min(dp[lastj], dp[i] + need);
            B += 1;
            W += A[i][1];
            if (i == n - 1 || A[i][0] != A[i + 1][0]) {
                need--;
            }
        }
        return dp[n];
    }
};