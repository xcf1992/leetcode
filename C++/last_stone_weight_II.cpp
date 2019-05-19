/*
 1049. Last Stone Weight II

 We have a collection of rocks, each rock has a positive integer weight.
 
 Each turn, we choose any two rocks and smash them together.  Suppose the stones have weights x and y with x <= y.  The result of this smash is:
 
 If x == y, both stones are totally destroyed;
 If x != y, the stone of weight x is totally destroyed, and the stone of weight y has new weight y-x.
 At the end, there is at most 1 stone left.  Return the smallest possible weight of this stone (the weight is 0 if there are no stones left.)
 
 
 
 Example 1:
 
 Input: [2,7,4,1,8,1]
 Output: 1
 Explanation:
 We can combine 2 and 4 to get 2 so the array converts to [2,7,1,8,1] then,
 we can combine 7 and 8 to get 1 so the array converts to [2,1,1,1] then,
 we can combine 2 and 1 to get 1 so the array converts to [1,1,1] then,
 we can combine 1 and 1 to get 0 so the array converts to [1] then that's the optimal value.
 
 
 Note:
 
 1 <= stones.length <= 30
 1 <= stones[i] <= 100

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
#include <set>
#include <numeric>
using namespace std;

/*
 1. Think of the final answer as a sum of weights with + or - sign symbols infront of each weight. Actually, all sums with 1 of each sign symbol are possible.
 2. Use dynamic programming: for every possible sum with N stones, those sums +x or -x is possible with N+1 stones, where x is the value of the newest stone. (This overcounts sums that are all positive or all negative, but those don't matter.)
 https://leetcode.com/problems/last-stone-weight-ii/discuss/295401/C%2B%2B-DP-inspired-by-the-hints-double-100-with-explanation
 */
class Solution {
public:
    int lastStoneWeightII(vector<int>& stones) {
        unordered_set<int> stoneLeft;
        for (int& stone : stones) {
            if (stoneLeft.empty()) {
                stoneLeft.insert(stone);
                stoneLeft.insert(-stone);
            }
            else {
                unordered_set<int> temp;
                for (int left : stoneLeft) {
                    temp.insert(left + stone);
                    temp.insert(left - stone);
                }
                stoneLeft = temp;
            }
        }
        
        int result = INT_MAX;
        for (int left : stoneLeft) {
            if (left >= 0) {
                result = min(left, result);
            }
        }
        return result;
    }
};
