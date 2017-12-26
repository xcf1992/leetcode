#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <cmath>
#include <queue>
#include <stack>
#include <stdio.h>
using namespace std;


class Solution {
public:
    int addDigits(int num) {
        return 1 + (num - 1) % 9;
    }
};

int main() {
    Solution s;
    return 0;
}