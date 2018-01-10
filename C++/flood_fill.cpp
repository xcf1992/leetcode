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
