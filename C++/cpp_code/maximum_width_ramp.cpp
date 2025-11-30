/*
962. Maximum Width Ramp
Given an array A of integers,
a ramp is a tuple (i, j) for which i < j and A[i] <= A[j].
The width of such a ramp is j - i.

Find the maximum width of a ramp in A.
If one doesn't exist, return 0.

Example 1:
Input: [6,0,8,2,1,5]
Output: 4
Explanation:
The maximum width ramp is achieved at (i, j) = (1, 5): A[1] = 0 and A[5] = 5.

Example 2:
Input: [9,8,1,0,1,9,4,0,4,1]
Output: 7
Explanation:
The maximum width ramp is achieved at (i, j) = (2, 9): A[2] = 1 and A[9] = 1.

Note:

2 <= A.length <= 50000
0 <= A[i] <= 50000
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
#include <climits>
#include <map>
#include <numeric>
using namespace std;
/*
Approach 1: Sort
Intuition and Algorithm

For all elements like A[i] = v, let's write the indices i in sorted order of their values v.
For example with A[0] = 7, A[1] = 2, A[2] = 5, A[3] = 4, we can write the order of indices i=1, i=3, i=2, i=0.

Then, whenever we write an index i,
we know there was a ramp of width i - min(indexes_previously_written) (if this quantity is positive).
We can keep track of the minimum of all indexes previously written as m.
*/
class Solution {
public:
    int maxWidthRamp(vector<int>& A) {
        int n = A.size();
        vector<pair<int, int>> indexedA;
        for (int i = 0; i < n; i++) {
            indexedA.push_back({i, A[i]});
        }

        sort(indexedA.begin(), indexedA.end(), [](pair<int, int>& a, pair<int, int>& b) {
            return a.second < b.second or (a.second == b.second and a.first < b.first);
        });

        int result = 0;
        int minIndex = n;
        for (pair<int, int>& cur : indexedA) {
            result = max(result, cur.first - minIndex);
            minIndex = min(minIndex, cur.first);
        }
        return result;
    }
};