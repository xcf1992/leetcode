/*
1176. Diet Plan Performance
A dieter consumes calories[i] calories on the i-th day.
For every consecutive sequence of k days, they look at T,
the total calories consumed during that sequence of k days:

    If T < lower, they performed poorly on their diet and lose 1 point;
    If T > upper, they performed well on their diet and gain 1 point;
    Otherwise, they performed normally and there is no change in points.

Return the total number of points the dieter has after all calories.length days.

Note that: The total points could be negative.

Example 1:

Input: calories = [1,2,3,4,5], k = 1, lower = 3, upper = 3
Output: 0
Explaination: calories[0], calories[1] < lower and calories[3], calories[4] > upper, total points = 0.
Example 2:

Input: calories = [3,2], k = 2, lower = 0, upper = 1
Output: 1
Explaination: calories[0] + calories[1] > upper, total points = 1.
Example 3:

Input: calories = [6,5,0,0], k = 2, lower = 1, upper = 5
Output: 0
Explaination: calories[0] + calories[1] > upper, calories[2] + calories[3] < lower, total points = 0.


Constraints:

1 <= k <= calories.length <= 10^5
0 <= calories[i] <= 20000
0 <= lower <= upper
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
using namespace std;

class Solution {
private:
    void update(int& result, int sum, int lower, int upper) {
        if (sum < lower) {
            result -= 1;
        }
        if (sum > upper) {
            result += 1;
        }
    }

public:
    int dietPlanPerformance(vector<int>& calories, int k, int lower, int upper) {
        int n = calories.size();
        if (k > n) {
            return 0;
        }

        int sum = 0;
        for (int i = 0; i < k; ++i) {
            sum += calories[i];
        }

        int result = 0;
        update(result, sum, lower, upper);
        for (int i = k; i < n; ++i) {
            sum -= calories[i - k];
            sum += calories[i];
            update(result, sum, lower, upper);
        }
        return result;
    }
};