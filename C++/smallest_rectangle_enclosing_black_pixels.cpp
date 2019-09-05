/*
302. Smallest Rectangle Enclosing Black Pixels
An image is represented by a binary matrix with 0 as a white pixel and 1 as a black pixel.
The black pixels are connected, i.e.,
there is only one black region.
Pixels are connected horizontally and vertically.
Given the location (x, y) of one of the black pixels,
return the area of the smallest (axis-aligned) rectangle that encloses all black pixels.

Example:

Input:
[
  "0010",
  "0110",
  "0100"
]
and x = 0, y = 2

Output: 6
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
#include <set>
using namespace std;

class Solution {
private:
    int minX;
    int maxX;
    int minY;
    int maxY;
    int m = 0;
    int n = 0;

    void dfs(vector<vector<char>>& image, int x, int y) {
        if (x < 0 or y < 0 or x >= m or y >= n or image[x][y] == '0') {
            return;
        }

        minX = min(x, minX);
        minY = min(y, minY);
        maxX = max(x, maxX);
        maxY = max(y, maxY);
        image[x][y] = '0';
        dfs(image, x - 1, y);
        dfs(image, x + 1, y);
        dfs(image, x, y - 1);
        dfs(image, x, y + 1);
    }
public:
    int minArea(vector<vector<char>>& image, int x, int y) {
        m = image.size();
        if (m == 0) {
            return 0;
        }
        n = image[0].size();
        minX = maxX = x;
        minY = maxY = y;
        dfs(image, x, y);
        return (maxX - minX + 1) * (maxY - minY + 1);
    }
};
