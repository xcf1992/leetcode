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
    int newInteger(int n) {
        int result = 0;
        int s = 1;
        while (n > 0) {
            result += n % 9 * s;
            s *= 10;
            n /= 9;
        }
        return result;
    }
};