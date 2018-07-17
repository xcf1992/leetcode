/*
 Given an unsorted array nums, reorder it such that nums[0] < nums[1] > nums[2] < nums[3]....
 
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

/*
 Explanation
 First I find a median using nth_element. That only guarantees O(n) average time complexity and I don't know about space complexity. I might write this myself using O(n) time and O(1) space, but that's not what I want to show here.
 
 This post is about what comes after that. We can use three-way partitioning to arrange the numbers so that those larger than the median come first, then those equal to the median come next, and then those smaller than the median come last.
 
 Ordinarily, you'd then use one more phase to bring the numbers to their final positions to reach the overall wiggle-property. But I don't know a nice O(1) space way for this. Instead, I embed this right into the partitioning algorithm. That algorithm simply works with indexes 0 to n-1 as usual, but sneaky as I am, I rewire those indexes where I want the numbers to actually end up. The partitioning-algorithm doesn't even know that I'm doing that, it just works like normal (it just uses A(x) instead of nums[x]).
 
 Let's say nums is [10,11,...,19]. Then after nth_element and ordinary partitioning, we might have this (15 is my median):
 
 index:     0  1  2  3   4   5  6  7  8  9
 number:   18 17 19 16  15  11 14 10 13 12
 I rewire it so that the first spot has index 5, the second spot has index 0, etc, so that I might get this instead:
 
 index:     5  0  6  1  7  2  8  3  9  4
 number:   11 18 14 17 10 19 13 16 12 15
 And 11 18 14 17 10 19 13 16 12 15 is perfectly wiggly. And the whole partitioning-to-wiggly-arrangement (everything after finding the median) only takes O(n) time and O(1) space.
 
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
class Solution {
public:
    void wiggleSort(vector<int>& nums) {
        int n = nums.size();
        auto midPtr = nums.begin() + n / 2;
        nth_element(nums.begin(), midPtr, nums.end());
        int midNum = *midPtr;
        
        #define A(i) nums[(1+2*(i)) % (n|1)]
        
        int i = 0;
        int j = 0;
        int k = n - 1;
        while (j <= k) {
            if (A(j) > midNum) {
                swap(A(i++), A(j++));
            }
            else if (A(j) < midNum) {
                swap(A(j), A(k--));
            }
            else {
                j++;
            }
        }
    }
};
