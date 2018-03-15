/*
 An image is represented by a binary matrix with 0 as a white pixel and 1 as a black pixel. The black pixels are connected, i.e., there is only one black region. Pixels are connected horizontally and vertically. Given the location (x, y) of one of the black pixels, return the area of the smallest (axis-aligned) rectangle that encloses all black pixels.
 
 For example, given the following image:
 
 [
 "0010",
 "0110",
 "0100"
 ]
 and x = 0, y = 2,
 Return 6.
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
    
    void dfs(vector<vector<bool>>& visited, vector<vector<char>>& image, int x, int y) {
        int m = image.size();
        int n = image[0].size();
        if (x < 0 || y < 0 || x >= m || y >= n || visited[x][y] || image[x][y] == '0') {
            return;
        }
        
        minX = min(x, minX);
        minY = min(y, minY);
        maxX = max(x, maxX);
        maxY = max(y, maxY);
        visited[x][y] = true;
        dfs(visited, image, x - 1, y);
        dfs(visited, image, x + 1, y);
        dfs(visited, image, x, y - 1);
        dfs(visited, image, x, y + 1);
        return;
    }
public:
    int minArea(vector<vector<char>>& image, int x, int y) {
        int m = image.size();
        if (m == 0) {
            return 0;
        }
        int n = image[0].size();
        vector<vector<bool>> visited(m, vector<bool>(n, false));
        minX = maxX = x;
        minY = maxY = y;
        return (maxX - minX) * (maxY - minY);
    }
};
