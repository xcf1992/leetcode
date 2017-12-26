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
    vector<vector<int> > hours{
                                {0},
                                {1, 2, 4, 8},
                                {3, 5, 9, 6, 10},
                                {7, 11}
    };
    vector<vector<int> > minutes{
                                    {0},
                                    {1, 2, 4, 8, 16, 32},
                                    {3, 5, 9, 17, 33, 6, 10, 18, 34, 12, 20, 36, 24, 40, 48},
                                    {7, 11, 19, 35, 13, 21, 37, 25, 41, 49, 14, 22, 38, 26, 42, 50, 28, 44, 52, 56},
                                    {15, 23, 39, 27, 43, 51, 29, 45, 53, 57, 30, 46, 54, 58},
                                    {31, 47, 55, 59}
    };
public:
    vector<string> readBinaryWatch(int num) {
        vector<string> result;
        for (int i = 0; i <= num && i < hours.size(); i++) {
            for (int j = 0; j < hours[i].size(); j++) {
                for (int k = 0; num - i < minutes.size() && k < minutes[num - i].size(); k++) {
                    string hour = to_string(hours[i][j]);
                    string minute = minutes[num - i][k] < 10 ? "0" + to_string(minutes[num - i][k]) : to_string(minutes[num - i][k]);
                    result.push_back(hour + ":" + minute);
                }
            }
        }
        return result;
    }
};

int main() {
    Solution s;
    std::vector<string> v = s.readBinaryWatch(1);
    for (int i = 0; i < v.size(); i++) {
        cout << v[i] << "  |  ";
    }
    return 0;
}