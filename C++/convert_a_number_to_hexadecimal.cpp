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
    const string HEX = "0123456789abcdef";
public:
    string toHex(int num) {
        if (num == 0) {
            return "0";
        }

        string result;
        int count = 0;
        while (num && count < 8) {
            result = HEX[num & 0xf] + result;
            num >>= 4;
            count++;
        }
        return result;
    }
};

int main() {
    Solution s;
    return 0;
}