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
    bool checkRecord(string s) {
        int absent = 0;
        for (int i = 0; i < s.size(); i++) {
            char c = s[i];
            if (c == 'A') {
                absent += 1;
                if (absent > 1) {
                    return false;
                }
            }
            else if (c == 'L') {
                if (i > 1 && s[i - 1] == 'L' && s[i - 2] == 'L') {
                    return false;
                }
            }
        }
        return true;
    }
};