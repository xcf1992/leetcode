/*
296. Best Meeting Point
https://leetcode.com/problems/best-meeting-point/description/?envType=company&envId=doordash&favoriteSlug=doordash-all

Given an m x n binary grid grid where each 1 marks the home of one friend, return the minimal total travel distance.

The total travel distance is the sum of the distances between the houses of the friends and the meeting point.

The distance is calculated using Manhattan Distance, where distance(p1, p2) = |p2.x - p1.x| + |p2.y - p1.y|.

Example:
Input:
1 - 0 - 0 - 0 - 1
|   |   |   |   |
0 - 0 - 0 - 0 - 0
|   |   |   |   |
0 - 0 - 1 - 0 - 0
Output: 6
Explanation: Given three people living at (0,0), (0,4), and (2,2):
             The point (0,2) is an ideal meeting point, as the total travel distance
             of 2+2+2=6 is minimal. So return 6.
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
#include <climits>
using namespace std;
/*
https://math.stackexchange.com/questions/113270/the-median-minimizes-the-sum-of-absolute-deviations-the-l-1-norm
Finding the best meeting point in a 2D grid seems difficult.
Let us take a step back and solve the 1D case which is much simpler.
Notice that the Manhattan distance is the sum of two independent variables.
Therefore, once we solve the 1D case, we can solve the 2D case as two independent 1D problems.

Let us look at some 1D examples below:

Case #1: 1-0-0-0-1

Case #2: 0-1-0-1-0
We know the best meeting point must locate somewhere between the left-most and right-most point.
For the above two cases, we would select the center point at x = 2 as the best meeting point.
How about choosing the mean of all points as the meeting point?

Consider this case:

Case #3: 1-0-0-0-0-0-0-1-1
Using the mean gives us avg(x) = (0 + 7 + 8) / 3 = 5 as the meeting point.
The total distance is 10.

But the best meeting point should be at x = 7 and the total distance is 8.

You may argue that the mean is close to the optimal point.
But imagine a larger case with many 1's congregating on the right side and just a single 1 on the left-most side.
Using the mean as the meeting point would be far from optimal.

Besides mean, what is a better way to represent the distribution of points?
Would median be a better representation? Indeed. In fact, the median must be the optimal meeting point.

Case #4: 1-1-0-0-1
To see why this is so,
let us look at case #4 above and choose the median x = 1 as our initial meeting point.
Assume that the total distance traveled is d.
Note that we have equal number of points distributed to its left and to its right.
Now let us move one step to its right where x = 2 and notice how the distance changes accordingly.

Since there are two points to the left of x = 2, we add 2 * (+1) to d.
And d is offset by –1 since there is one point to the right.
This means the distance had overall increased by 1.

Therefore, it is clear that:

As long as there is equal number of points to the left and right of the meeting point, the total distance is minimized.

Case #5: 1-1-0-0-1-1
One may think that the optimal meeting point must fall on one of the 1's.
This is true for cases with odd number of 1's,
but not necessarily true when there are even number of 1's,
just like case #5 does.
You can choose any of the x = 1 to x = 4 points and the total distance is minimized. Why?

The implementation is direct.
First we collect both the row and column coordinates,
sort them and select their middle elements.
Then we calculate the total distance as the sum of two independent 1D problems.
*/
class Solution {
private:
    int calculate(vector<int>& position) {
        int result = 0;
        int middle = position[position.size() / 2];
        for (int i = 0; i < position.size(); i++) {
            result += abs(position[i] - middle);
        }
        return result;
    }

public:
    int minTotalDistance(vector<vector<int>>& grid) {
        vector<int> row;
        vector<int> col;
        for (int i = 0; i < grid.size(); i++) {
            for (int j = 0; j < grid[0].size(); j++) {
                if (grid[i][j] == 1) {
                    row.push_back(i);
                    col.push_back(j);
                }
            }
        }
        sort(col.begin(), col.end());
        return calculate(row) + calculate(col);
    }
};