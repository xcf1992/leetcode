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
    bool isPowerOfTwo(int n) {
        if (n <= 0) {
            return false; 
        }

        return (n & (n - 1)) == 0;
    }
};

int main() {
    Solution s;
    return 0;
}