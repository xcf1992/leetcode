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
    bool judgeCircle(string moves) {
        int vertical = 0;
        int horizontal = 0;

        for (char c : moves) {
            if (c == 'U') {
                vertical += 1;
            }
            else if (c == 'D') {
                vertical -= 1;
            }
            else if (c == 'L') {
                horizontal -= 1;
            }
            else if (c == 'R') {
                horizontal += 1;
            }
        }

        return vertical == 0 && horizontal == 0;
    }
};