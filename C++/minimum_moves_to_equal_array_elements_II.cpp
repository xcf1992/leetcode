/*
462. Minimum Moves to Equal Array Elements II
Given a non-empty integer array, find the minimum number of moves required to make all array elements equal, where a move is incrementing a selected element by 1 or decrementing a selected element by 1.

You may assume the array's length is at most 10,000.

Example:

Input:
[1,2,3]

Output:
2

Explanation:
Only two moves are needed (remember each move increments or decrements one element):

[1,2,3]  =>  [2,2,3]  =>  [2,2,2]
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
using namespace std;

/*
In the previous approach, 
we went for finding the median after sorting and then calculated the number of moves required. 
But, if we observe properly, we'll find that if the array is sorted, 
we can do the same task without actually finding the median or the number kk to which we need to settle at the end. 
To proceed with this, let's look at the maximum(maxmax) and the minimum numbers(minmin) in the array, 
which currently lie at its extreme positions. We know, at the end, both these numbers should be equalized to kk. 
For the number maxmax, the number of moves required to do this is given by max - kmax−k. Similarly, 
for the number minmin, the number of moves is given by k - mink−min. 
Thus, the total number of moves for both maxmax and minmin is given by max - k + (k - min) = max - min, 
which is independent of the number kk. Thus, we can continue now, 
with the next maximum and the next minimum number in the array, until the complete array is exhausted.
*/
class Solution {
public:
    int minMoves2(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        int start = 0;
        int end = nums.size() - 1;
        int result = 0;
        while (end > start) {
            result += (nums[end--] - nums[start++]);
        }
        return result;
    }
};
