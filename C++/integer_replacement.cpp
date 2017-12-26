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
    int integerReplacement(int n) {
        int result = 0;
        unsigned num = n;
        while (num > 3) {
            if (!(num & 1)) {
                num >>= 1;
            }
            else if (num & 2) {
                num += 1;
            }
            else {
                num -= 1;
            }
            result += 1;
        }
        return result + num - 1;
    }
};

int main() {
    Solution s;
    cout << s.integerReplacement(8);
    return 0;
}