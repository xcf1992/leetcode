/*
1340. Jump Game V
https://leetcode.com/problems/jump-game-v/

Given an array of integers arr and an integer d.
In one step you can jump from index i to index:

i + x where: i + x < arr.length and 0 < x <= d.
i - x where: i - x >= 0 and 0 < x <= d.
In addition,
you can only jump from index i to index j
if arr[i] > arr[j] and arr[i] > arr[k] for all indices k between i and j
(More formally min(i, j) < k < max(i, j)).

You can choose any index of the array and start jumping.
Return the maximum number of indices you can visit.

Notice that you can not jump outside of the array at any time.

Example 1:
Input: arr = [6,4,14,6,8,13,9,7,10,6,12], d = 2
Output: 4
Explanation: You can start at index 10. You can jump 10 --> 8 --> 6 --> 7 as shown.
Note that if you start at index 6 you can only jump to index 7. You cannot jump to index 5 because 13 > 9. You cannot
jump to index 4 because index 5 is between index 4 and 6 and 13 > 9. Similarly You cannot jump from index 3 to index 2
or index 1.

Example 2:
Input: arr = [3,3,3,3,3], d = 3
Output: 1
Explanation: You can start at any index. You always cannot jump to any index.

Example 3:
Input: arr = [7,6,5,4,3,2,1], d = 1
Output: 7
Explanation: Start at index 0. You can visit all the indicies.

Example 4:
Input: arr = [7,1,7,1,7,1], d = 2
Output: 2

Example 5:
Input: arr = [66], d = 1
Output: 1

Constraints:
1 <= arr.length <= 1000
1 <= arr[i] <= 10^5
1 <= d <= arr.length
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
Observation:
Once we get the maximum jumps possible from a certain index
it will be same no matter how we end up at that index since we can only go to a smaller valued index.
Thus we can use caching to store the results of each index as we calulate them to solve other indices.

Solution:
Use a simple recursion to check to the right and left of the current index and cache those results in memo table.
Do this for all indices as starting indices.
Also notice that we can stop once we encounter an index
whose value is greater than or equal to the current index in the recursion function,
since we cannot jump to any index after that.
*/
class Solution {
private:
    int dfs(vector<int>& memo, vector<int>& arr, int d, int index) {
        if (memo[index] != -1) {
            return memo[index];
        }

        memo[index] = 0;
        for (int i = index + 1; i < arr.size() and i <= index + d and arr[i] < arr[index]; ++i) {
            memo[index] = max(memo[index], 1 + dfs(memo, arr, d, i));
        }
        for (int i = index - 1; i >= max(0, index - d) and arr[i] < arr[index]; --i) {
            memo[index] = max(memo[index], 1 + dfs(memo, arr, d, i));
        }
        return memo[index];
    }

public:
    int maxJumps(vector<int>& arr, int d) {
        int n = arr.size();
        vector<int> memo(n, -1);
        int result = INT_MIN;
        for (int i = 0; i < n; ++i) {
            result = max(result, 1 + dfs(memo, d, arr, i));
        }
        return result;
    }
};