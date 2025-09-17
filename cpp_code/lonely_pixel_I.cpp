/*
531. Lonely Pixel I
Given a picture consisting of black and white pixels,
find the number of black lonely pixels.

The picture is represented by a 2D char array consisting of 'B' and 'W',
which means black and white pixels respectively.

A black lonely pixel is character 'B' that located at a specific position
where the same row and same column don't have any other black pixels.

Example:
Input:
[['W', 'W', 'B'],
 ['W', 'B', 'W'],
 ['B', 'W', 'W']]

Output: 3
Explanation: All the three 'B's are black lonely pixels.
Note:
The range of width and height of the input 2D array is [1,500].
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

class Solution {
public:
    int findLonelyPixel(vector<vector<char>>& picture) {
        int m = picture.size();
        int n = picture[0].size();

        vector<int> rowCnt(m, 0);
        vector<int> colCnt(n, 0);
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (picture[i][j] == 'B') {
                    ++rowCnt[i];
                    ++colCnt[j];
                }
            }
        }

        int res = 0;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (picture[i][j] == 'B') {
                    if (rowCnt[i] == 1 and colCnt[j] == 1) {
                        ++res;
                    }
                }
            }
        }
        return res;
    }
};
