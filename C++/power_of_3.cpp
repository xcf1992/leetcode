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
    bool isPowerOfThree(int n) {
        return (n == 0x1) ||
            (n == 0x3) ||
            (n == 0x9) ||
            (n == 0x1b) ||
            (n == 0x51) ||
            (n == 0xf3) ||
            (n == 0x2d9) ||
            (n == 0x88b) ||
            (n == 0x19a1) ||
            (n == 0x4ce3) ||
            (n == 0xe6a9) ||
            (n == 0x2b3fb) ||
            (n == 0x81bf1) ||
            (n == 0x1853d3) ||
            (n == 0x48fb79) ||
            (n == 0xdaf26b) ||
            (n == 0x290d741) ||
            (n == 0x7b285c3) ||
            (n == 0x17179149) ||
            (n == 0x4546b3db);
    }
};

int main() {
    Solution s;
    return 0;
}