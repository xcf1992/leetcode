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
    int hammingDistance(int x, int y) {
        int xorValue = x ^ y;
        int distance = 0;
        while (xorValue != 0) {
            if (xorValue & 1 != 0) {
                distance++;
            }
            xorValue >>= 1;
        }
        return distance;
    }
};

int main() {
    Solution s;
    return 0;
}