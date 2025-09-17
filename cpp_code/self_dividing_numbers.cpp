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
private:
    bool selfDivisable(int num) {
        for (int i = num; i > 0; i /= 10) {
            if (i % 10 == 0 or num % (i % 10) != 0) {
                return false;
            }
        }
        return true;
    }
public:
    vector<int> selfDividingNumbers(int left, int right) {
        vector<int> result;
        for (int i = left; i <= right; i++) {
            if (selfDivisable(i)) {
                result.push_back(i);
            }
        }
        return result;
    }
};
