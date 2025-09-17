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
    bool hasAlternatingBits(int n) {
        int bit = 1 & n;
        n >>= 1;
        while (n != 0) {
            int temp = 1 & n;
            if (temp == bit) {
                return false;
            }
            bit = temp;
            n >>= 1;
        }
        return true;
    }
};