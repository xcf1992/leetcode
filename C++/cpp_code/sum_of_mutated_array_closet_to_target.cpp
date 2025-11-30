/*
1300. Sum of Mutated Array Closest to Target
https://leetcode.com/problems/sum-of-mutated-array-closest-to-target/

Given an integer array arr and a target value target,
return the integer value such that when we change all the integers larger than value in the given array to be equal to
value, the sum of the array gets as close as possible (in absolute difference) to target.

In case of a tie, return the minimum such integer.
Notice that the answer is not neccesarilly a number from arr.

Example 1:
Input: arr = [4,9,3], target = 10
Output: 3
Explanation: When using 3 arr converts to [3, 3, 3] which sums 9 and that's the optimal answer.

Example 2:
Input: arr = [2,3,5], target = 10
Output: 5

Example 3:
Input: arr = [60864,25176,27249,21296,20204], target = 56803
Output: 11361

Constraints:
1 <= arr.length <= 10^4
1 <= arr[i], target <= 10^5
*/
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <set>
#include <algorithm>
#include <cmath>
#include <queue>
#include <stack>
#include <climits>
#include <map>
#include <numeric>
#include "extra_data_types.hpp"
using namespace std;
/*
The value we are looking for is somewhere between 1 and maxValue (m).
Now use Binary search to speed up the process.

go up if the sum is too small
go down if the sum is too big
When we are done with binary search, l and r are equal, but it might happen that we have not exactly reached the target.
Check if l-1 (should get us below the target) leads to the sum closer to the target.
*/
class Solution {
public:
    int findBestValue(vector<int>& arr, int target) {
        int left = 1;
        int right = 0;
        int sum = 0;
        for (int num : arr) {
            sum += num;
            right = max(right, num);
        }

        if (sum <= target) {
            return right;
        }

        while (left < right) {
            int mid = left + (right - left) / 2;
            sum = 0;
            for (int num : arr) {
                sum += num > mid ? mid : num;
            }

            if (sum >= target) {
                right = mid;
            } else {
                left = mid + 1;
            }
        }

        int sum1 = 0;
        int sum2 = 0;
        for (int num : arr) {
            sum1 += num > left ? left : num;
            sum2 += num > (left - 1) ? (left - 1) : num;
        }
        return abs(sum1 - target) < abs(sum2 - target) ? left : left - 1;
    }
};

/*
Sorting solution
I got comments that sorting solution can be more inuitive.
It's maybe shorter but binary search is easier to apply as a pattern (at least for me).

Well, sorting also leads to O(NLogN) speed so it's the same speed and a qustion of taste.
However, in practice It's slightly slower.

Intuition:
We will need to replace the highest values with some value v
v must be >= the highest value of the array.
In other words: v >= max(arr)

We should pop the highest value from arr while the current result is above the target:
while(target < sum + max(arr) * numOfRemoved)

Sorting is done to speed up the search for the higest values
Then we simply calculate v to replace each removed element and get as close to the target as possible

In the end of "pop high values" process we will split the sorted array in 2 parts:
          Splitted the sorted values to left and right parts:
          a,b,c,d   |   X,Y,Z
          -------       =====
          keep          replace each elem
          as is         with v
  sum:    =sum-X-Y-Z    =v*numOfElems
          left part + right part = target

Values in the left part will stay as is. Their sum is the total sum - sum of the removed.
Values in the right part will be replaced with v and we keep their number in removed.

left part + right part = target
left part + v*removed  = target
v = (target - left part)/removed
When we do the division, v is rounded down.
I check also v+1 to cover the undesired rounding
though I'm pretty sure that a sophisticated formula can do the same shorter (I prefer simpler things).

-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
Binary search O(NlogMax(A)).
In order to ruduce the difficulty, it constrains A[i] < 10 ^ 5.

In this solution,
we sort the input and compared A[i] with target one by one.

Sort the array A in decreasing order.
We try to make all values in A to be the min(A) (the last element)
If target >= min(A) * n, we doesn't hit our target yet.
We should continue to try a value bigger.
So we pop the min(A) value.
Consider that it won't be affected anymore,
we can remove it from target by target -= A.pop()
We continue doing step 2-4, until the next number is too big for target.
We split the the target evenly, depending on the number of element left in A
At this point, @bobalice help explain the round part:
if A is empty means its impossible to reach target so we just return maximum element.
If A is not empty, intuitively the answer should be the nearest integer to target / len(A).

Since we need to return the minimum such integer if there is a tie,
if target / len(A) has 0.5 we should round down,

Complexity
Time O(NlogN)
Space O(1)
*/