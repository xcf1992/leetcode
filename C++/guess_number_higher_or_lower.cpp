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
    int guessNumber(int n) {
        int left = 1;
        int right = n + 1;
        int result = left + ((right - left) >> 1);
        int guessResult = guess(result);
        while (guessResult != 0) {
            if (guessResult == 1) {
                left = result + 1;
            } else {
                right = result;
            }
            result = left + ((right - left) >> 1);
            guessResult = guess(result);
        }
        return result;
    }
};

int main() {
    Solution s;
    return 0;
}