/*
1696. Jump Game VI
https://leetcode.com/problems/jump-game-vi/

You are given a 0-indexed integer array nums and an integer k.

You are initially standing at index 0.
In one move,
you can jump at most k steps forward without going outside the boundaries of the array.
That is, you can jump from index i to any index in the range [i + 1, min(n - 1, i + k)] inclusive.

You want to reach the last index of the array (index n - 1).
Your score is the sum of all nums[j] for each index j you visited in the array.
Return the maximum score you can get.

Example 1:
Input: nums = [1,-1,-2,4,-7,3], k = 2
Output: 7
Explanation: You can choose your jumps forming the subsequence [1,-1,4,3] (underlined above). The sum is 7.

Example 2:
Input: nums = [10,-5,-2,4,0,3], k = 3
Output: 17
Explanation: You can choose your jumps forming the subsequence [10,4,3] (underlined above). The sum is 17.

Example 3:
Input: nums = [1,-5,-20,4,-1,3,-6,-3], k = 2
Output: 0

Constraints:
 1 <= nums.length, k <= 105
-104 <= nums[i] <= 104
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
#include <climits>
#include <set>
#include <numeric>
using namespace std;
/*
Let's try to solve this from the end for better visualization.
At every index i we want to pick the maximum result from i+1 to i+k and add nums[i] to it
A maxium from i+1 to i+k can be found in O(1) time using a monoqueue when we start from the end.

Now all we need to do is use this monoqueue
to get the maximum result for the next k indices and store it somewhere,
we can use the input array itself as an auxillary array.
Let's store only the indices in the monoqueue
so that we can limit the monoqueue to have results only for the next k indices at max.

Best question to solve to understand the workings of a monoqueue:
239. Sliding Window Maximum
*/
class Solution {
public:
    int maxResult(vector<int>& nums, int k) {
        long curr = 0;
        deque<int> dq;  // Monoqueue

        // Start answering the best possible results for index `i` from the back
        for (int i = nums.size() - 1; i >= 0; i--) {
            curr = nums[i] + (dq.empty() ? 0 : nums[dq.front()]);
            // Get current best, the maximum result will be the first element in the monoqueue.

            // We remove all the smaller results greedily as they wont get used anyways (This helps the monoqueue to
            // remain sorted)
            while (!dq.empty() && curr > nums[dq.back()]) {
                dq.pop_back();
            }
            dq.push_back(i);  // Insert current index into the monoqueue

            // Erase all the indices in deque that are greater than or equal to i+k.
            if (dq.front() >= i + k) {
                dq.pop_front();
            }
            nums[i] = curr;  // Use input array as auxillary array to store the best results.
        }
        return curr;  // `curr` would have the best or the maxium result to reach end from index 0.
    }
};