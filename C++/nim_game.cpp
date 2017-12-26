#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <cmath>
#include <queue>
#include <stack>
#include <stdio.h>
using namespace std;


class Solution {
public:
    bool canWinNim(int n) {
        if (n <= 3) {
            return true;
        }

        bool take_one = true;
        bool take_two = true;
        bool take_three = true;
        bool result = false;

        for (int i = 4; i <= n; i++) {
            if (take_one && take_two && take_three) {
                result = false;
            }
            else {
                result = true;
            }

            take_three = take_two;
            take_two = take_one;
            take_one = result;
        }
        return result;
    }
};

int main() {
    Solution s;
    cout << s.canWinNim(4) << endl;
    return 0;
}