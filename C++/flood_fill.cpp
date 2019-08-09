/*
733. Flood Fill
An image is represented by a 2-D array of integers,
each integer representing the pixel value of the image (from 0 to 65535).

Given a coordinate (sr, sc) representing the starting pixel (row and column) of the flood fill,
and a pixel value newColor, "flood fill" the image.

To perform a "flood fill", consider the starting pixel,
plus any pixels connected 4-directionally to the starting pixel of the same color as the starting pixel,
plus any pixels connected 4-directionally to those pixels (also with the same color as the starting pixel),
and so on.
Replace the color of all of the aforementioned pixels with the newColor.

At the end, return the modified image.

Example 1:
Input:
image = [[1,1,1],[1,1,0],[1,0,1]]
sr = 1, sc = 1, newColor = 2
Output: [[2,2,2],[2,2,0],[2,0,1]]
Explanation:
From the center of the image (with position (sr, sc) = (1, 1)), all pixels connected
by a path of the same color as the starting pixel are colored with the new color.
Note the bottom corner is not colored 2, because it is not 4-directionally connected
to the starting pixel.
Note:

The length of image and image[0] will be in the range [1, 50].
The given starting pixel will satisfy 0 <= sr < image.length and 0 <= sc < image[0].length.
The value of each color in image[i][j] and newColor will be an integer in [0, 65535].
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
    vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int newColor) {
        int m = image.size();
        if (m == 0) {
            return {};
        }
        int n = image[0].size();

        int color = image[sr][sc];
        if (color == newColor) {
            return image;
        }
        image[sr][sc] = newColor;

        queue<pair<int, int>> bfs;
        bfs.push({sr, sc});

        vector<int> rDiff({1, -1, 0, 0});
        vector<int> cDiff({0, 0, 1, -1});
        while (!bfs.empty()) {
            int row = bfs.front().first;
            int col = bfs.front().second;
            bfs.pop();

            for (int i = 0; i < 4; i++) {
                int nRow = row + rDiff[i];
                int nCol = col + cDiff[i];
                if (nRow >= 0 and nCol >= 0 and nRow < m and nCol < n and image[nRow][nCol] == color) {
                    image[nRow][nCol] = newColor;
                    bfs.push({nRow, nCol});
                }
            }
        }
        return image;
    }
};

class Solution1 {
private:
    void fill(vector<vector<int>>& image, int sr, int sc, int oldColor) {
        int m = image.size();
        int n = image[0].size();
        if (sr < 0 || sr >= m) {
            return;
        }
        if (sc < 0 || sc >= n) {
            return;
        }
        if (image[sr][sc] != oldColor) {
            return;
        }

        image[sr][sc] = -1;

        fill(image, sr - 1, sc, oldColor);
        fill(image, sr, sc - 1, oldColor);
        fill(image, sr, sc + 1, oldColor);
        fill(image, sr + 1, sc, oldColor);
        return;
    }
public:
    vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int newColor) {
        fill(image, sr, sc, image[sr][sc]);
        for (int i = 0; i < image.size(); i++) {
            for (int j = 0; j < image[0].size(); j++) {
                if (image[i][j] == -1) {
                    image[i][j] = newColor;
                }
            }
        }
        return image;
    }
};
