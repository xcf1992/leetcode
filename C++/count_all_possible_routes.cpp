/*
1575. Count All Possible Routes
https://leetcode.com/problems/count-all-possible-routes/

You are given an array of distinct positive integers locations
where locations[i] represents the position of city i. You are also given integers start,
finish and fuel representing the starting city, ending city,
and the initial amount of fuel you have, respectively.

At each step, if you are at city i, you can pick any city j such that j != i
and 0 <= j < locations.length and move to city j.
Moving from city i to city j reduces the amount of fuel you have by |locations[i] - locations[j]|.
Please notice that |x| denotes the absolute value of x.

Notice that fuel cannot become negative at any point in time,
and that you are allowed to visit any city more than once (including start and finish).

Return the count of all possible routes from start to finish.
Since the answer may be too large, return it modulo 10^9 + 7.

Example 1:
Input: locations = [2,3,6,8,4], start = 1, finish = 3, fuel = 5
Output: 4
Explanation: The following are all possible routes, each uses 5 units of fuel:
1 -> 3
1 -> 2 -> 3
1 -> 4 -> 3
1 -> 4 -> 2 -> 3

Example 2:
Input: locations = [4,3,1], start = 1, finish = 0, fuel = 6
Output: 5
Explanation: The following are all possible routes:
1 -> 0, used fuel = 1
1 -> 2 -> 0, used fuel = 5
1 -> 2 -> 1 -> 0, used fuel = 5
1 -> 0 -> 1 -> 0, used fuel = 3
1 -> 0 -> 1 -> 0 -> 1 -> 0, used fuel = 5

Example 3:
Input: locations = [5,2,1], start = 0, finish = 2, fuel = 3
Output: 0
Explanation: It's impossible to get from 0 to 2 using only 3 units of fuel since the shortest route needs 4 units of fuel.

Example 4:
Input: locations = [2,1,5], start = 0, finish = 0, fuel = 3
Output: 2
Explanation: There are two possible routes, 0 and 0 -> 1 -> 0.

Example 5:
Input: locations = [1,2,3], start = 0, finish = 2, fuel = 40
Output: 615088286
Explanation: The total number of possible routes is 2615088300. Taking this number modulo 10^9 + 7 gives us 615088286.

Constraints:
2 <= locations.length <= 100
1 <= locations[i] <= 10^9
All integers in locations are distinct.
0 <= start, finish < locations.length
1 <= fuel <= 200
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
using namespace std;
/*
Start from the start index, and visit all cities except start.

Continue this process recursively.

If you reach end index, do:
    Now, we have atleast 1 way of reaching end so add this 1 possible way to the answer.

    Continue recursion, since there might be more ways to get back from end to end using other cities.

If fuel < 0, there is no further way left.

If you look at this recursion, we can see that there are overlapping subproblems. If you reach a city c with fuel f multiple times from different paths, don't recompute, just use memoised result.
*/
class Solution {
private:
    // dp[curCity][fuel] = number of ways to reach finish, when we are at city `curCity` with fuel `fuel`
    long solve(vector<int>& locations, int curCity, int e, vector<vector<long>>& dp, int fuel) {
        // 4. There is no further way left.
        if (fuel < 0) {
            return 0;
        }

        if (dp[curCity][fuel] != -1) {
            return dp[curCity][fuel];
        }
        // 3. Now, if we have atleast 1 way of reaching `end`, add 1 to the answer.
        // But don't stop right here, keep going, there might be more ways :)
        long ans = (curCity == e) ? 1 : 0;
        for (int nextCity = 0; nextCity < locations.size(); ++nextCity) {
            // 1. Visit all cities except `curCity`.
            if (nextCity != curCity) {
                // 2. Continue this process recursively.
                ans = (ans + solve(locations, nextCity, e, dp, fuel - abs(locations[curCity] - locations[nextCity]))) % 1000000007;
            }
        }
        return dp[curCity][fuel] = ans;
    }
public:
    int countRoutes(vector<int>& locations, int start, int finish, int fuel) {
        int n = locations.size();
        vector<vector<long>> dp(n, vector<long>(fuel + 1, -1));
        return solve(locations, start, finish, dp, fuel);
    }
};
