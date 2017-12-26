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
    bool isPowerOfFour(int num) {
        if (num <= 0) {
            return false;
        }
        
        if ((num & (num - 1)) != 0) {
            return false;
        }
        
        while (num != 0) {
            if (num == 1) {
                return true;
            }
            num >>= 2;
        }
        return false;
    }
};

int main() {
    Solution s;
    return 0;
}