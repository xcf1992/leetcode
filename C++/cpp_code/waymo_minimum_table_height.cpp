/*
想象一个两列的表格，总宽度固定为 W。有一条竖线把表格分成左右两列，左列宽度为 d，右列宽度为 W - d。
每列里有一段文字，文字会自动换行（word wrap）。列越窄，换的行就越多，列就越高。表格的总高度取决于两列中更高的那一列。
目标：找到分割线位置 d，使得表格高度最小。
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

/*
举个具体例子
假设总宽度 W = 20 字符，左列文字 = "aaaa bbbb cccc dddd eeee"（20字符），右列文字 = "xx yy"（5字符）。
分割线在 d=10（正中间）：
|  左列(10) |  右列(10) |
| aaaa bbbb | xx yy     |
| cccc dddd |           |
| eeee      |           |
高度: 左=3行, 右=1行, 表格高度=3
分割线在 d=15：
|  左列(15)       |右(5)|
| aaaa bbbb cccc  | xx  |
| dddd eeee       | yy  |
高度: 左=2行, 右=2行, 表格高度=2  ← 更优！
为什么能 Binary Search？
关键观察：当 d 增大时，左列行数单调不增（列越宽行越少），右列行数单调不减。表格高度 = max(左行数,
右行数)，这形成了一个先降后升的 U 形曲线，可以用二分搜索找最低点。 更精确地说，我们二分找最小的 d，使得左列行数 ≤
右列行数，那个交叉点附近就是最优解。
 */

class Solution {
private:
    void parse(string& text, vector<string>& words) {
        size_t pos = text.find_first_of(' ');
        while (pos != string::npos) {
            words.push_back(text.substr(0, pos));
            text = text.substr(pos + 1);
            pos = text.find_first_of(' ');
        }
        words.push_back(text);
    }

    int count_lines(vector<string>& words, int width) {
        if (width <= 0) {
            return INT_MAX;
        }

        if (words.empty()) {
            return 1;
        }

        int rst = 1;
        int remaining = width;
        for (string& w : words) {
            int w_len = w.size();

            // Corner case: 单词比列宽还长，强制拆行
            if (w_len > width) {
                if (remaining < width) {  // 当前行已有内容，先换行
                    remaining = width;
                    rst += 1;
                }

                rst += (w_len - 1) / width;  // 额外的行数（第一行已经算了）
                remaining = width - (w_len % width == 0 ? width : w_len % width);
            } else if (w_len <= remaining) {
                remaining -= w_len;
                if (remaining > 0) {
                    remaining -= 1;  // extra empty space
                }
            } else {
                rst += 1;
                remaining = width - w_len;
                if (remaining > 0) {
                    remaining -= 1;
                }
            }
        }
        return rst;
    }

public:
    int calc_min_table_height(string& left_text, string& right_text, int max_width) {
        vector<string> left_words;
        parse(left_text, left_words);
        vector<string> right_words;
        parse(right_text, right_words);

        int rst = INT_MAX;
        // 由于行数是整数且不严格单调（可能有平台期），
        // 最安全的做法是在二分缩小范围后，在小范围内线性扫描
        // 先用二分找到大致区域
        int left = 1;
        int right = max_width - 1;
        while (right - left > 5) {
            int mid = left + (right - left) / 2;
            int left_height = count_lines(left_words, mid);
            int right_height = count_lines(right_words, max_width - mid);
            if (left_height > right_height) {
                left = mid;  // 左边还太高，需要更多宽度
            } else {
                right = mid;  // 右边更高或相等，可以试着缩小左列
            }
        }

        for (int i = left; i <= right; i++) {
            int left_height = count_lines(left_words, i);
            int right_height = count_lines(right_words, max_width - i);
            int height = max(left_height, right_height);
            if (height < rst) {
                rst = height;
            }
        }
        return rst;
    }
};

// Brute force
int brute_force(string left_text, string right_text, int max_width) {
    auto split = [](string text) -> vector<string> {
        vector<string> words;
        size_t pos = text.find(' ');
        while (pos != string::npos) {
            words.push_back(text.substr(0, pos));
            text = text.substr(pos + 1);
            pos = text.find(' ');
        }
        words.push_back(text);
        return words;
    };
    auto count = [](vector<string>& words, int width) -> int {
        if (width <= 0)
            return INT_MAX;
        if (words.empty())
            return 1;
        int rst = 1, remaining = width;
        for (auto& w : words) {
            int wl = w.size();
            if (wl > width) {
                if (remaining < width) {
                    rst++;
                    remaining = width;
                }
                rst += (wl - 1) / width;
                remaining = width - (wl % width == 0 ? width : wl % width);
            } else if (wl <= remaining) {
                remaining -= wl;
                if (remaining > 0)
                    remaining--;
            } else {
                rst++;
                remaining = width - wl;
                if (remaining > 0)
                    remaining--;
            }
        }
        return rst;
    };
    auto lw = split(left_text);
    auto rw = split(right_text);
    int best = INT_MAX;
    for (int d = 1; d < max_width; d++) {
        int h = max(count(lw, d), count(rw, max_width - d));
        best = min(best, h);
    }
    return best;
}

void test(string name, string left, string right, int width) {
    Solution sol;
    string l = left, r = right;
    int result = sol.calc_min_table_height(l, r, width);
    int expected = brute_force(left, right, width);
    bool pass = (result == expected);
    cout << (pass ? "PASS" : "FAIL") << " | " << name << " | width=" << width << " | got=" << result
         << " | expected=" << expected << endl;
}

int main() {
    test("balanced", "aa bb cc dd", "ee ff gg hh", 20);
    test("left heavy", "aa bb cc dd ee ff gg hh ii jj kk", "xx", 30);
    test("right heavy", "hi", "aa bb cc dd ee ff gg hh ii jj kk ll mm", 30);
    test("single words", "hello", "world", 12);
    test("long word left", "abcdefghijklmnopqrstuvwxyz short", "aa bb cc", 30);
    test("long words both", "abcdefghij rest of text here", "klmnopqrst more text here too", 22);
    test("many small words", "a b c d e f g h i j k l m n", "o p q r s t u v w x y z", 20);
    test("exact fit", "ab cd", "ef gh", 12);
    test("tight width", "abc def ghi", "jk lm", 8);

    // Stress: random-ish larger inputs
    string big_left, big_right;
    for (int i = 0; i < 50; i++)
        big_left += "word" + to_string(i) + " ";
    for (int i = 0; i < 30; i++)
        big_right += "text" + to_string(i) + " ";
    big_left.pop_back();
    big_right.pop_back();
    test("stress", big_left, big_right, 60);

    // Edge: very narrow
    test("narrow", "aa bb cc", "dd ee ff", 6);

    // Edge: one side is one char
    test("one char left", "a", "bb cc dd ee ff gg hh", 20);

    // Edge: equal single long words
    test("two long words", "abcdefghij", "klmnopqrst", 22);

    // Edge: lots of 1-char words
    test("all 1-char", "a b c d e f g h i j", "k l m n o p q r s t", 15);

    return 0;
}