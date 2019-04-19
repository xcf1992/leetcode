/*
 656. Coin Path

 Given an array A (index starts at 1) consisting of N integers: A1, A2, ..., AN and an integer B. The integer B denotes that from any place (suppose the index is i) in the array A, you can jump to any one of the place in the array A indexed i+1, i+2, …, i+B if this place can be jumped to. Also, if you step on the index i, you have to pay Ai coins. If Ai is -1, it means you can’t jump to the place indexed i in the array.

 Now, you start from the place indexed 1 in the array A, and your aim is to reach the place indexed N using the minimum coins. You need to return the path of indexes (starting from 1 to N) in the array you should take to get to the place indexed N using minimum coins.

 If there are multiple paths with the same cost, return the lexicographically smallest such path.

 If it's not possible to reach the place indexed N then you need to return an empty array.

 Example 1:

 Input: [1,2,4,-1,2], 2
 Output: [1,3,5]


 Example 2:

 Input: [1,2,4,-1,2], 1
 Output: []


 Note:

 Path Pa1, Pa2, ..., Pan is lexicographically smaller than Pb1, Pb2, ..., Pbm, if and only if at the first i where Pai and Pbi differ, Pai < Pbi; when no such i exists, then n < m.
 A1 >= 0. A2, ..., AN (if exist) will in the range of [-1, 100].
 Length of A is in the range of [1, 1000].
 B is in the range of [1, 100].
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

class Solution {
public:
    vector<int> cheapestJump(vector<int>& A, int B) {
        int n = A.size();
        vector<int> cost(n, INT_MAX);
        vector<int> previous(n, -1);
        vector<int> length(n, 0);
        cost[0] = 0;
        for (int i = 0; i < n; ++i) {
            if (A[i] == -1) {
                continue;
            }

            for (int j = max(0, i - B); j < i; ++j) {
                if (A[j] == -1 or cost[j] == INT_MAX) {
                    continue;
                }

                int curCost = cost[j] + A[i];
                if (curCost < cost[i] or (curCost == cost[i] and length[j] + 1 > length[i])) {
                    cost[i] = curCost;
                    previous[i] = j;
                    length[i] = length[j] + 1;
                }
            }
        }

        vector<int> result;
        for (int i = n - 1; i >= 0; i = previous[i]) {
            result.push_back(i + 1);
        }
        reverse(result.begin(), result.end());
        if (result[0] != 1) {
            return {};
        }
        return result;
    }
};
