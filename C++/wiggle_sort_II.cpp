/*
324. Wiggle Sort II
https://leetcode.com/problems/wiggle-sort-ii/

Given an unsorted array nums,
reorder it such that nums[0] < nums[1] > nums[2] < nums[3]....

Example 1:
Input: nums = [1, 5, 1, 1, 6, 4]
Output: One possible answer is [1, 4, 1, 5, 1, 6].

Example 2:
Input: nums = [1, 3, 2, 2, 3, 1]
Output: One possible answer is [2, 3, 1, 3, 1, 2].

Note:
You may assume all input has valid answer.

Follow Up:
Can you do it in O(n) time and/or in-place with O(1) extra space?
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
/*
Explanation
First I find a median using nth_element.
That only guarantees O(n) average time complexity
and I don't know about space complexity.
I might write this myself using O(n) time and O(1) space,
but that's not what I want to show here.

This post is about what comes after that.
We can use three-way partitioning to arrange the numbers
so that those larger than the median come first,
then those equal to the median come next,
and then those smaller than the median come last.

Ordinarily, you'd then use one more phase to bring the numbers to their final positions
to reach the overall wiggle-property.
But I don't know a nice O(1) space way for this.
Instead, I embed this right into the partitioning algorithm.
That algorithm simply works with indexes 0 to n-1 as usual,
but sneaky as I am, I rewire those indexes where I want the numbers to actually end up.
The partitioning-algorithm doesn't even know that I'm doing that,
it just works like normal (it just uses A(x) instead of nums[x]).

Let's say nums is [10,11,...,19].
Then after nth_element and ordinary partitioning,
we might have this (15 is my median):

index:     0  1  2  3   4   5  6  7  8  9
number:   18 17 19 16  15  11 14 10 13 12
I rewire it so that the first spot has index 5, the second spot has index 0, etc, so that I might get this instead:

index:     5  0  6  1  7  2  8  3  9  4
number:   11 18 14 17 10 19 13 16 12 15
And 11 18 14 17 10 19 13 16 12 15 is perfectly wiggly.
And the whole partitioning-to-wiggly-arrangement (everything after finding the median) only takes O(n) time and O(1) space.

If the above description is unclear, maybe this explicit listing helps:

Accessing A(0) actually accesses nums[1].
Accessing A(1) actually accesses nums[3].
Accessing A(2) actually accesses nums[5].
Accessing A(3) actually accesses nums[7].
Accessing A(4) actually accesses nums[9].
Accessing A(5) actually accesses nums[0].
Accessing A(6) actually accesses nums[2].
Accessing A(7) actually accesses nums[4].
Accessing A(8) actually accesses nums[6].
Accessing A(9) actually accesses nums[8].
*/
/*
This is to explain why mapped index formula is (1 + 2*index) % (n | 1)

Notice that by placing the median in it's place in the array we divided the array in 3 chunks:
all numbers less than median are in one side,
all numbers larger than median are on the other side,
median is in the dead center of the array.

We want to place any a group of numbers (larger than median) in odd slots,
and another group of numbers (smaller than median) in even slots.
So all numbers on left of the median < n / 2 should be in odd slots,
all numbers on right of the median > n / 2 should go into even slots
(remember that median is its correct place at n / 2)

PS: I'm ignoring the discussion of odd/even array length for simplicity.

So let's think about the first group in the odd slots,
all numbers is the left side of the array should go into these odd slots.
What's the formula for it? Naturally it would be:
(1 + 2 x index) % n

All these indexes are less than n / 2 so multiplying by 2 and add 1
(to make them go to odd place)
and then mod by n will always guarantee that they are less than n.
Original Index => Mapped Index
0 => (1 + 2 x 0) % 6 = 1 % 6 = 1
1 => (1 + 2 x 1) % 6 = 3 % 6 = 3
2 => (1 + 2 x 2) % 6 = 5 % 6 = 5

These are what's less than median, if we continue this with indexes 3, 4, 5 we will cycle again:
3 => (1 + 2 x 3) % 6 = 7 % 6 = 1
4 => (1 + 2 x 4) % 6 = 9 % 6 = 3
5 => (1 + 2 x 5) % 6 = 11 % 6 = 5

and we don't want that,
so for indexes larger than n/2 we want them to be even,
(n|1) does that exactly.
What n|1 does it that it gets the next odd number to n if it was even
if n = 6 for example 110 | 1 = 111 = 7
if n = 7 for example 111 | 1 = 111 = 7
and this is what we want, instead of cycling the odd numbers again we want them to be even,
and odd % odd number is even so updating the formula to :
(1 + 2*index) % (n | 1)

Then we have:
3 => (1 + 2 x 3) % 7 = 7 % 7 = 0
4 => (1 + 2 x 4) % 7 = 9 % 7 = 2
5 => (1 + 2 x 5) % 7 = 11 % 7 = 4
*/
class Solution {
private:
    int getPos(int i, int n) {
        return (1 + 2 * i) % (n | 1);
    }
public:
    void wiggleSort(vector<int>& nums) {
        int n = nums.size();
        auto midPtr = nums.begin() + n / 2;
        nth_element(nums.begin(), midPtr, nums.end());

        int midNum = *midPtr;
        int left = 0;
        int right = n - 1;
        int cur = 0;
        while (cur <= right) {
            if (nums[getPos(cur, n)] > midNum) { // the part before virtual index left will always be <= midNum, so we can move cur forward
                swap(nums[getPos(left, n)], nums[getPos(cur, n)]);
                left += 1;
                cur += 1;
            }
            else if (nums[getPos(cur, n)] < midNum) { // we do no konw the value at virtual index right, we need to check again after swap
                swap(nums[getPos(cur, n)], nums[getPos(right, n)]);
                right -= 1;
            }
            else {
                cur += 1;
            }
        }
    }
};

// wrong for [4,5,5,6]
class Solution1 {
public:
    void wiggleSort(vector<int>& nums) {
        int n = nums.size();
        vector<int> temp = nums;
        sort(temp.begin(), temp.end());
        int left = 0;
        int right = (n + 1) >> 1;
        for (int i = 0; i < n; i++) {
            nums[i] = i % 2 == 0 ? temp[left++] : temp[right++];
        }
    }
};
