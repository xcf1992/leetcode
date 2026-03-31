/*
Run length encoding:
{'B', 'A', 'A', 'E', 'E', 'E', 'C'} -> B1A2E3C1
implement function: char Find(int p) using encoded data, p為原始資料中的index

这道题分两部分：
第一部分是背景： Run Length Encoding（游程编码），把连续重复的字符压缩表示。原始数据 {'B', 'A', 'A', 'E', 'E', 'E', 'C'}
编码后变成 B1A2E3C1，意思是 B 出现 1 次、A 出现 2 次、E 出现 3 次、C 出现 1 次。 第二部分是问题：
给你的是编码后的数据（不是原始数组），实现 Find(int p)，返回原始数据中第 p 个位置的字符。 用原始数据对照一下： 原始索引:
0    1    2    3    4    5    6 原始数据: 'B', 'A', 'A', 'E', 'E', 'E', 'C' 所以 Find(0) = 'B'，Find(2) = 'A'，Find(5) =
'E'，Find(6) = 'C'。 关键考点是：
你不能把编码展开还原成原始数组（那就失去压缩的意义了），而是要直接在压缩数据上定位。核心思路是把每段的累积长度算出来，然后用二分搜索找到
p 落在哪一段。比如 B1A2E3C1 的累积长度是 [1, 3, 6, 7]，查 p=5 时二分找到第一个累积值 > 5 的位置，就是 6（对应
'E'），所以答案是 'E'。 这样 Find 的时间复杂度是 O(log n)，n 是编码段数，而不需要 O(原始长度) 的空间去还原。

follow up: char FindbyValue(char target, int left, int right), find the bigger char in range[left,
right]，假設input為排序過

这道题的意思是：
编码后的数据是按字符排序过的，比如 A3B2C4E1（展开后是 AAABBCCCCCE），然后给你一个 target 字符和一个区间 [left,
right]（指原始数据的索引范围），要你在这个区间里找到比 target 大的最小字符。 举个例子，编码 A3B2C4E1，展开后： 索引:  0
1 2 3 4 5 6 7 8 9 数据:  A A A B B C C C C E 调用 FindbyValue('B', 2, 7)，在区间 [2, 7] 即 A B B C C C 中找比 'B'
大的最小字符，答案是 'C'。 考点是： 因为数据排过序，编码段本身也是有序的，所以不需要展开原始数据。关键思路是利用
range_idx 累积数组，先用二分找到 target 所在的段，然后往后看下一个和区间 [left, right]
有重叠的段，那个段的字符就是答案。如果后面没有段落落在 right 范围内，就返回不存在。
本质上就是在前一题的基础上，结合数据有序这个条件，把"区间内大于 target 的最小值"优化到 O(log n) 完成。
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
    char find(string& encoded_str, int tgt_idx) {
        vector<int> range_idx;
        vector<char> decoded_char;
        int n = encoded_str.size();
        int total = 0;
        for (int i = 0; i < n; i++) {
            if (!isdigit(encoded_str[i])) {
                decoded_char.push_back(encoded_str[i]);
                continue;
            }

            int cnt = 0;
            while (i < n && isdigit(encoded_str[i])) {
                cnt = cnt * 10 + (encoded_str[i] - '0');
                i += 1;
            }
            i -= 1;

            total += cnt;
            range_idx.push_back(total);
        }

        if (tgt_idx >= total) {
            cout << "invalid tgt_idx" << endl;
            return ' ';
        }

        auto it = lower_bound(range_idx.begin(), range_idx.end(), tgt_idx + 1);
        return decoded_char[it - range_idx.begin()];
    }

    char find_by_value(string& encoded_str, char tgt_c, int left, int right) {
        vector<int> range_idx;
        vector<char> decoded_char;
        int n = encoded_str.size();
        int total = 0;
        for (int i = 0; i < n; i++) {
            if (!isdigit(encoded_str[i])) {
                decoded_char.push_back(encoded_str[i]);
                continue;
            }

            int cnt = 0;
            while (i < n && isdigit(encoded_str[i])) {
                cnt = cnt * 10 + (encoded_str[i] - '0');
                i += 1;
            }
            i -= 1;

            total += cnt;
            range_idx.push_back(total);
        }

        auto it = upper_bound(decoded_char.begin(), decoded_char.end(), tgt_c);
        if (it == decoded_char.end()) {
            return ' ';
        }

        int seg = it - decoded_char.begin();
        // check this segment overlaps with [left, right]
        int seg_start = (seg == 0) ? 0 : range_idx[seg - 1];
        int seg_end = range_idx[seg] - 1;

        if (seg_start > right || seg_end < left)
            return ' ';

        return decoded_char[seg];
    }
};
