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
    int minSteps(int n) {
        if (n == 1) {
            return 0;
        }
        for (int i = 2; i <= sqrt(n); i++) {
            if (n % i == 0) {
                return i + minSteps(n / i);
            }
        }
        return n;
    }
};