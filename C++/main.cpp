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
#include <set>
#include <numeric>
using namespace std;

class Solution {
private:
    // DONT FORGET TO INITIALIZE m AND n
    int m = 0;
    int n = 0;
    vector<int> root;
    vector<int> diff = {0, 1, 0, -1, 0};

    int find(int island) {
        if (island != root[island]) {
            root[island] = find(root[island]);
        }
        return island;
    }

    void check(int row, int col, int newIsland, int &count) {
        int island = row * n + col;
        if (row < 0 or col < 0 or row >= m or col >= n or root[island] == -1) {
            return;
        }

        int newRoot = find(newIsland);
        int curRoot = find(island);
        if (curRoot != newRoot) {
            root[curRoot] = newRoot;
            count -= 1;
        }
    }
public:
    vector<int> numIslands2(int m, int n, vector<vector<int>>& positions) {
        this -> m = m;
        this -> n = n;
        root = vector<int>(m * n, -1);

        int count = 0;
        vector<int> result;
        for (vector<int>& pos : positions) {
            int row = pos[0];
            int col = pos[1];
            int island = row * n + col;
            if (root[island] != -1) {
                result.push_back(count);
                continue; // this one has become island before already
            }

            count += 1;
            root[island] = island;
            for (int i = 1; i < diff.size(); ++i) {
                check(row + diff[i], col + diff[i - 1], island, count);
            }
            result.push_back(count);
        }
        return result;
    }
};

int main() {
    Solution s;
    vector<int> temp({1,3,2,4});
    vector<int> temp1({1,3,3,3,2});
    vector<vector<int>> matrix({
        {0,1},
        {1,2},
        {2,1},
        {1,0},
        {0,2},
        {0,0},
        {1,1}
    });
    vector<vector<int>> matrix2({
        {1,0},
        {0,0}
    });
    vector<string> words({"cat","cats","and","sand","dog"});
    s.numIslands2(3, 3, matrix);
}
