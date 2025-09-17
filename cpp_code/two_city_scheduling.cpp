/*
 1029. Two City Scheduling
 There are 2N people a company is planning to interview.
 The cost of flying the i-th person to city A is costs[i][0],
 and the cost of flying the i-th person to city B is costs[i][1].

 Return the minimum cost to fly every person to a city such that exactly N people arrive in each city.

 Example 1:

 Input: [[10,20],[30,200],[400,50],[30,20]]
 Output: 110
 Explanation:
 The first person goes to city A for a cost of 10.
 The second person goes to city A for a cost of 30.
 The third person goes to city B for a cost of 50.
 The fourth person goes to city B for a cost of 20.

 The total minimum cost is 10 + 30 + 50 + 20 = 110 to have half the people interviewing in each city.


 Note:

 1 <= costs.length <= 100
 It is guaranteed that costs.length is even.
 1 <= costs[i][0], costs[i][1] <= 1000
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

class Solution {
public:
    int twoCitySchedCost(vector<vector<int>>& costs) {
        sort(costs.begin(), costs.end(), [](vector<int>& a, vector<int>& b){
            return abs(a[0] - a[1]) > abs(b[0] - b[1]);
        });

        int n = costs.size() / 2;
        int A = 0;
        int B = 0;
        int result = 0;
        for (vector<int>& cost : costs) {
            if (cost[0] > cost[1]) {
                if (B < n) {
                    result += cost[1];
                    B += 1;
                }
                else {
                    A += 1;
                    result += cost[0];
                }
            }
            else {
                if (A < n) {
                    result += cost[0];
                    A += 1;
                }
                else {
                    result += cost[1];
                    B += 1;
                }
            }
        }
        return result;
    }
};
