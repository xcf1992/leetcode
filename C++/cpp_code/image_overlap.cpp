/*
835. Image Overlap
Two images A and B are given, represented as binary,
square matrices of the same size.
(A binary matrix has only 0s and 1s as values.)

We translate one image however we choose
(sliding it left, right, up, or down any number of units),
and place it on top of the other image.
After, the overlap of this translation is the number of positions that have a 1 in both images.

(Note also that a translation does not include any kind of rotation.)

What is the largest possible overlap?

Example 1:

Input: A = [[1,1,0],
[0,1,0],
[0,1,0]]
B = [[0,0,0],
[0,1,1],
[0,0,1]]
Output: 3
Explanation: We slide A to right by 1 unit and down by 1 unit.
Notes:

1 <= A.length = A[0].length = B.length = B[0].length <= 30
0 <= A[i][j], B[i][j] <= 1
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
using namespace std;
/*
Intuition:
If we do brute force, we have 2N horizontal possible sliding, 2N vertical sliding and N^2 to count overlap area.
We get O(N^4) solution and it may get accepted.
But we waste out time on case of sparse matrix.

Explanation:
Assume index in A and B is [0, N * N -1].

Loop on A, if value == 1, save a coordinates i / N * 100 + i % N to LA.
Loop on B, if value == 1, save a coordinates i / N * 100 + i % N to LB.
Loop on combination (i, j) of LA and LB, increase count[i - j] by 1.
If we slide to make A[i] orverlap B[j], we can get 1 point.
Loop on count and return max values.
I use a 1 key hashmap. Assume ab for row and cd for col, I make it abcd as coordinate.
For sure, hashmap with 2 keys will be better for understanding.

Time Complexity:
As reminded by @specialzsp,
O(N^2) for preparing, and O(AB) for loop.
O(AB + N^2)

Update 2018-05-15 about i / N * 100 + i % N
I find many people discuss it, so I update this explanantion.

1.why 100?
100 is big enough and very clear.
For example, If I slide 13 rows and 19 cols, it will be 1319.

why not 30?
30 is not big enough.
For example: 409 = 13 * 30 + 19 = 14 * 30 - 11.
409 can be taken as sliding "14 rows and -11 cols" or "13 rows and 19 cols" at the same time.

How big is enough?
Bigger than 2N-1. Bigger than 2N-1. Bigger than 2N-1.

Can we replace i / N * 100 + i % N by i?
No, it's wrong for simple test case [[0,1],[1,1]], [[1,1],[1,0]]
*/
class Solution {
public:
    int largestOverlap(vector<vector<int>>& A, vector<vector<int>>& B) {
        int num = A.size();
        vector<int> a;
        vector<int> b;
        for (int i = 0; i < num; i++) {
            for (int j = 0; j < num; j++) {
                if (A[i][j] == 1) {
                    a.push_back(i * 100 + j);
                }

                if (B[i][j] == 1) {
                    b.push_back(i * 100 + j);
                }
            }
        }

        unordered_map<int, int> count;
        for (int ait : a) {
            for (int bit : b) {
                count[ait - bit] += 1;
            }
        }

        int result = 0;
        for (auto& c : count) {
            result = max(result, c.second);
        }
        return result;
    }
};