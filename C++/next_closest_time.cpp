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
    string nextClosestTime(string time) {
        vector<char> digits;
        for (char c : time) {
            if (c != ':') {
                digits.push_back(c);
            }
        }
        sort(digits.begin(), digits.end());

        for (int i = 0; i < 4; i++) {
            if (digits[i] > time[4]) {
                time[4] = digits[i];
                return time;
            }
        }

        time[4] = digits[0];

        for (int i = 0; i < 4; i++) {
            if (digits[i] > '5') {
                break;
            }
            if (digits[i] > time[3]) {
                time[3] = digits[i];
                return time;
            }
        }

        time[3] = digits[0];

        for (int i = 0; i < 4; i++) {
            if (time[0] == '2' && digits[i] > '3') {
                break;
            }
            if (digits[i] > time[1]) {
                time[1] = digits[i];
                return time;
            }
        }

        time[1] = digits[0];

        for (int i = 0; i < 4; i++) {
            if (digits[i] > '2') {
                break;
            }
            if (digits[i] > time[0]) {
                time[0] = digits[i];
                return time;
            }
        }

        time[0] = digits[0];
        return time;
    }
};