/*
https://leetcode.com/problems/zero-array-transformation-iii/description/
3362. Zero Array Transformation III

You are given an integer array nums of length n and a 2D array queries where queries[i] = [li, ri].

Each queries[i] represents the following action on nums:

Decrement the value at each index in the range [li, ri] in nums by at most 1.
The amount by which the value is decremented can be chosen independently for each index.
A Zero Array is an array with all its elements equal to 0.

Return the maximum number of elements that can be removed from queries, such that nums can still be converted to a zero array using the remaining queries. If it is not possible to convert nums to a zero array, return -1.



Example 1:

Input: nums = [2,0,2], queries = [[0,2],[0,2],[1,1]]

Output: 1

Explanation:

After removing queries[2], nums can still be converted to a zero array.

Using queries[0], decrement nums[0] and nums[2] by 1 and nums[1] by 0.
Using queries[1], decrement nums[0] and nums[2] by 1 and nums[1] by 0.
Example 2:

Input: nums = [1,1,1,1], queries = [[1,3],[0,2],[1,3],[1,2]]

Output: 2

Explanation:

We can remove queries[2] and queries[3].

Example 3:

Input: nums = [1,2,3,4], queries = [[0,3]]

Output: -1

Explanation:

nums cannot be converted to a zero array even after using all the queries.



Constraints:

1 <= nums.length <= 105
0 <= nums[i] <= 105
1 <= queries.length <= 105
queries[i].length == 2
0 <= li <= ri < nums.length
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

class Solution {
public:
    int maxRemoval(vector<int> &nums, vector<vector<int> > &queries) {
        sort(queries.begin(), queries.end(),
             [](const vector<int> &a, const vector<int> &b) {
                 return a[0] < b[0];
             });

        // default is a max-heap with larger val at the top
        priority_queue<int> max_heap;
        vector<int> prefix(nums.size() + 1, 0);
        int sum = 0;
        int j = 0;
        for (int i = 0; i < nums.size(); i++) {
            sum += prefix[i];
            while (j < queries.size() && queries[j][0] <= i) {
                max_heap.push(queries[j][1]);
                j += 1;
            }

            while (sum < nums[i] && !max_heap.empty() && max_heap.top() >= i) {
                sum += 1;
                prefix[max_heap.top() + 1] -= 1;
                max_heap.pop();
            }

            if (sum < nums[i]) {
                return -1;
            }
        }
        return max_heap.size();
    }
};

/*
First, we consider the element at index 0 in nums.
If nums[0]>0, we must find at least nums[0] elements in queries with left endpoints of 0 to retain
so that nums[0] can be reduced to 0. Now, which elements of nums[0] should we choose?
Greedily, we should select those with the largest right endpoints.
After this selection, we move on to nums[1].
The elements selected in the previous step may not include index 1, and we need to remove them.
This can be accomplished using the difference array deltaArray.

At this point, the cumulative number of operations may not be enough to reduce nums[1] to 0,
and we need to select elements from queries, similar to the previous step.
We can select the elements with the largest right endpoints from the portion of unselected elements
whose left endpoints are ≤1 until the number of operations satisfies the condition to reduce nums[1] to 0.
This calculation can be efficiently handled using a priority queue (or heap).

As we traverse nums,
we continuously insert the right endpoints of the queries corresponding to the left endpoints into the heap.
When the number of operations is insufficient,
we keep extracting the largest right endpoint from the heap until the required number of operations is met.
After completing the traversal, the size of the heap represents the number of queries that can be deleted.
 */
