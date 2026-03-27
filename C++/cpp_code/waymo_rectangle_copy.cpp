/*
给你一个二维数组（2D array），实现一个矩形区域拷贝操作——把数组中某个矩形区域的内容复制到另一个位置，要求额外内存只能用
O(1)，也就是不能开一个临时矩阵来暂存。 比如在一个 8×8 的网格上，把左上角 3×3 的区域复制到右下角某个位置： 源区域 (r1=0,
c1=0, 3x3)     目标位置 (r2=5, c2=5)

A B C . . . . .               . . . . . . . .
D E F . . . . .               . . . . . . . .
G H I . . . . .       →       . . . . . . . .
. . . . . . . .               . . . . . . . .
. . . . . . . .               . . . . . . . .
. . . . . . . .               . . . . . A B C
. . . . . . . .               . . . . . D E F
. . . . . . . .               . . . . . G H I
难点在于： 当源区域和目标区域有重叠时，直接逐行拷贝会导致源数据被覆盖，后续读到的是已经被写入的新值而不是原始值。
O(1) 内存的关键是选择正确的遍历方向，类似于 memmove 的思路：

如果目标在源的下方或右方，从右下角往左上角倒序拷贝
如果目标在源的上方或左方，从左上角往右下角正序拷贝

这样正在读取的源数据永远还没被覆盖，不需要额外缓冲区。
*/
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <cmath>
#include <queue>
#include <set>
#include <climits>
#include <map>
#include <cassert>
using namespace std;

class Solution {
public:
    void rect_copy(vector<vector<int>>& grid, int sr, int sc, int dr, int dc, int h, int w) {
        int row_start, row_end, row_step;
        int col_start, col_end, col_step;
        if (dr <= sr) {
            row_start = 0;
            row_end = h;
            row_step = 1;
        } else {
            row_start = h - 1;
            row_end = -1;
            row_step = -1;
        }

        if (dc <= sc) {
            col_start = 0;
            col_end = w;
            col_step = 1;
        } else {
            col_start = w - 1;
            col_end = -1;
            col_step = -1;
        }

        for (int r = row_start; r != row_end; r += row_step) {
            for (int c = col_start; c != col_end; c += col_step) {
                grid[dr + r][dc + c] = grid[sr + r][sc + c];
            }
        }
    }
};
