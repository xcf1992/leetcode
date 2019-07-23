/*
 248. Strobogrammatic Number III

 A strobogrammatic number is a number that looks the same when rotated 180 degrees (looked at upside down).

 Write a function to count the total strobogrammatic numbers that exist in the range of low <= num <= high.

 Example:

 Input: low = "50", high = "100"
 Output: 3
 Explanation: 69, 88, and 96 are three strobogrammatic numbers.
 Note:
 Because the range might be a large number, the low and high numbers are represented as string.
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
#include <map>
#include <set>
#include <numeric>
using namespace std;

class Solution {
private:
    map<char, char> mp = {{'0', '0'}, {'1', '1'}, {'6', '9'}, {'8', '8'}, {'9', '6'}};

    void dfs(string& low, string& high, string str, int left, int right, int& count) {
        if (left > right) {
            if (str.length() == low.length() and str.compare(low) < 0) {
                return;
            }
            if (str.length() == high.length() and str.compare(high) > 0) {
                return;
            }
            count++;
            return;
        }

        for (auto p : mp) {
            str[left] = p.first;
            str[right] = p.second;
            if (str.size() != 1 and str[0] == '0') {
                continue;
            }
            if (left < right or (left == right and p.first == p.second)) {
                dfs(low, high, str, left + 1, right - 1, count);
            }
        }
    }
public:
    int strobogrammaticInRange(string low, string high) {
        int count = 0;
        for (int len = low.length(); len <= high.length(); len++) {
            string temp(len, '0');
            dfs(low, high, temp, 0, len - 1, count);
        }
        return count;
    }
};

class Solution1 { // brute force digit by digit, by chenfu
private:
    vector<char> digit{'0', '1', '6', '8', '9'};
    unordered_map<char, char> strobogrammatic{{'9', '6'}, {'1', '1'}, {'8', '8'}, {'6', '9'}, {'0', '0'}};

    void dfs(int n, int pos, int &result, string &temp, string &low, string &high) {
        if ((n % 2 == 1 and pos > n / 2) or (n % 2 == 0 and pos > n / 2 - 1)) {
            if (temp >= low and temp <= high) {
                result += 1;
            }
            return;
        }

        for (char c : digit) {
            if (pos == 0 and c == '0') {
                continue;
            }
            if (n % 2 == 1 and pos == n / 2 and (c == '6' or c == '9')) {
                continue;
            }
            temp[pos] = c;
            temp[n - pos - 1] = strobogrammatic[c];
            dfs(n, pos + 1, result, temp, low, high);
        }
    }
public:
    int strobogrammaticInRange(string low, string high) {
        int minLen = low.size();
        int maxLen = high.size();
        int result = 0;
        if (minLen == maxLen) {
            if (minLen == 1) {
                int count = 0;
                for (char d : digit) {
                    if (d != '6' and d != '9' and d >= low[0] and d <= high[0]) {
                        count += 1;
                    }
                }
                return count;
            }
            string temp(minLen, ' ');
            dfs(minLen, 0, result, temp, low, high);
            return result;
        }
        for (int i = minLen; i <= maxLen; ++i) {
            if (i == minLen) {
                int count = 0;
                string temp(minLen, ' ');
                string maxNum = string(minLen, '9');
                dfs(minLen, 0, count, temp, low, maxNum);
                result += count;
                if (minLen == 1) {
                    result += 1;
                }
            }
            else if (i == maxLen) {
                int count = 0;
                string temp(maxLen, ' ');
                string minNum = "1" + string(maxLen - 1, '0');
                dfs(maxLen, 0, count, temp, minNum, high);
                result += count;
            }
            else {
                if (i % 2 == 0) {
                    result += 4 * pow(5, i / 2 - 1);
                }
                else {
                    result += 4 * 3 * pow(5, i / 2 - 1);
                }
            }
        }
        return result;
    }
};
