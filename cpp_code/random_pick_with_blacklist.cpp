/*
710. Random Pick with Blacklist

Given a blacklist B containing unique integers from [0, N),
write a function to return a uniform random integer from [0, N) which is NOT in B.

Optimize it such that it minimizes the call to system’s Math.random().

Note:
1 <= N <= 1000000000
0 <= B.length < min(100000, N)
[0, N) does NOT include N. See interval notation.

Example 1:
Input:
["Solution","pick","pick","pick"]
[[1,[]],[],[],[]]
Output: [null,0,0,0]

Example 2:
Input:
["Solution","pick","pick","pick"]
[[2,[]],[],[],[]]
Output: [null,1,1,1]

Example 3:
Input:
["Solution","pick","pick","pick"]
[[3,[1]],[],[],[]]
Output: [null,0,0,2]

Example 4:
Input:
["Solution","pick","pick","pick"]
[[4,[2]],[],[],[]]
Output: [null,1,3,1]
Explanation of Input Syntax:

The input is two lists:
the subroutines called and their arguments.
Solution's constructor has two arguments, N and the blacklist B.
pick has no arguments. Arguments are always wrapped with a list, even if there aren't any.
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
private:
    vector<pair<int, int>> whiteRange;
public:
    Solution(int N, vector<int> blacklist) {
        sort(blacklist.begin(), blacklist.end());
        int white = 0;
        for (int bnum : blacklist) {
            if (bnum - white == 1) {
                whiteRange.push_back({white, white});
            }
            else if (bnum - white > 1) {
                whiteRange.push_back({white, bnum - 1});
            }
            white = bnum + 1;
        }
        if (white < N) {
            whiteRange.push_back({white, N - 1});
        }
    }

    int pick() {
        int r = rand() % whiteRange.size();
        int start = whiteRange[r].first;
        int end = whiteRange[r].second;
        int range = end - start + 1;
        return (rand() % range) + start;
    }
};
/*
* Your Solution object will be instantiated and called as such:
* Solution obj = new Solution(N, blacklist);
* int param_1 = obj.pick();
*/