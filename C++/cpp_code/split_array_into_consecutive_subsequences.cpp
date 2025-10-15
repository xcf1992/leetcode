/*
659. Split Array into Consecutive Subsequences
https://leetcode.com/problems/split-array-into-consecutive-subsequences/

You are given an integer array sorted in ascending order (may contain duplicates),
you need to split them into several subsequences,
where each subsequences consist of at least 3 consecutive integers.
Return whether you can make such a split.

Example 1:
Input: [1,2,3,3,4,5]
Output: True
Explanation:
You can split them into two consecutive subsequences :
1, 2, 3
3, 4, 5

Example 2:
Input: [1,2,3,3,4,4,5,5]
Output: True
Explanation:
You can split them into two consecutive subsequences :
1, 2, 3, 4, 5
3, 4, 5

Example 3:
Input: [1,2,3,4,4,5]
Output: False

Note:
The length of the input is in range of [1, 10000]
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
Call a chain a sequence of 3 or more consecutive numbers.

Considering numbers x from left to right,
if x can be added to a current chain, it's at least as good to add x to that chain first,
rather than to start a new chain.

Why? If we started with numbers x and greater from the beginning,
the shorter chains starting from x could be concatenated with the chains ending before x,
possibly helping us if there was a "chain" from x that was only length 1 or 2.

Algorithm

Say we have a count of each number, and let tails[x] be the number of chains ending right before x.

Now let's process each number.
If there's a chain ending before x, then add it to that chain.
Otherwise, if we can start a new chain, do so.

It's worth noting that our solution can be amended to take only O(1) additional space,
since we could do our counts similar to Approach #1, and we only need to know the last 3 counts at a time.
*/
class Solution {
public:
    bool isPossible(vector<int>& nums) {
        unordered_map<int, int> count;
        for (int num : nums) {
            count[num] += 1;
        }

        unordered_map<int, int> sub; // sub[i] counts the number of consecutive subsequences that ends at number i
        for (int num : nums) {
            if (count[num] == 0) {
                continue;
            }

            count[num] -= 1;
            if (sub[num - 1] > 0) {
                sub[num - 1] -= 1;
                sub[num] += 1;
            }
            else if (count[num + 1] > 0 and count[num + 2] > 0) {
                count[num + 1] -= 1;
                count[num + 2] -= 1;
                sub[num + 2] += 1;
            }
            else {
                return false;
            }
        }
        return true;
    }
};
