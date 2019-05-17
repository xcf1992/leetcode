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
