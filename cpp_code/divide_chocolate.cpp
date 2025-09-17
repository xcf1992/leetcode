/*
1231. Divide Chocolate
https://leetcode.com/problems/divide-chocolate/

You have one chocolate bar that consists of some chunks.
Each chunk has its own sweetness given by the array sweetness.

You want to share the chocolate with your K friends
so you start cutting the chocolate bar into K+1 pieces using K cuts,
each piece consists of some consecutive chunks.

Being generous, you will eat the piece with the minimum total sweetness and give the other pieces to your friends.
Find the maximum total sweetness of the piece you can get by cutting the chocolate bar optimally.

Example 1:
Input: sweetness = [1,2,3,4,5,6,7,8,9], K = 5
Output: 6
Explanation: You can divide the chocolate to [1,2,3], [4,5], [6], [7], [8], [9]

Example 2:
Input: sweetness = [5,6,7,8,9,1,2,3,4], K = 8
Output: 1
Explanation: There is only one way to cut the bar into 9 pieces.

Example 3:
Input: sweetness = [1,2,2,1,2,2,1,2,2], K = 2
Output: 5
Explanation: You can divide the chocolate to [1,2,2], [1,2,2], [1,2,2]

Constraints:
0 <= K < sweetness.length <= 10^4
1 <= sweetness[i] <= 10^5
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
using namespace std;
/*
Explanation
We want to maximize the minimum sweetness.
Binary search the result between 1 and 10^9.

Time O(Nlog(10^9))
Space O(1)

There's another reason: in this question,
we want to find the maximum total sweetness.
We have to find the rightmost value,
so we use int mid = (left + right + 1)/2
and if(condition passed) left = mid;else hi = mid - 1.

For question like 1101, we want to find the leftmost value.
So we have to use something like int mid = (left + right) / 2
and if (condition passed) right = mid; else left = mid + 1;.
*/
class Solution {
public:
    int maximizeSweetness(vector<int>& sweetness, int K) {
        int left = 1;
        int right = 1e9 / (K + 1);
        while (left < right) {
            int mid = (1 + left + right) / 2;
            int cur = 0;
            int cuts = 0;
            for (int a : sweetness) {
                cur += a;
                if (cur >= mid) {
                    cur = 0;
                    cuts += 1;
                }
                if (cuts > K) {
                    break;
                }
            }

            if (cuts > K) {
                left = mid;
            }
            else {
                right = mid - 1;
            }
        }
        return left;
    }
};
