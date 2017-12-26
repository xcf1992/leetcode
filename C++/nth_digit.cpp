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
    int findNthDigit(int n) {int findNthDigit(int n) {
        if (n < 10) {
            return n;
        }
        int i = 0;

        while ( n > 0) {
            i += 1;
            int length = i * (pow(10, i) - pow(10, i - 1));
            if ( n - length > 0) {
                n -= length;
            }
            else {
                break;
            }
        }

        int res = pow(10, i - 1) + (n - 1) / i;
        string result = to_string(res);
        return result[(n - 1) % i] - '0';
    }
};

int main() {
    Solution s;
    return 0;
}