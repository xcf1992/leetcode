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
    int lastRemaining(int n) {
        int head = 1;
        bool left = true;
        int remain = n;
        int step = 2;
        while (remain > 1) {
            if (left || remain % 2 == 1) {
                head += step;
            }
            remain /= 2;
            step *= 2;
            left = !left;
        }
        return head;
    }
};