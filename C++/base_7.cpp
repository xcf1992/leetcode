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
    string convertToBase7(int num) {
        string result = "";
        bool negative = false;
        if (num < 0) {
            negative = true;
            num = 0 - num;
        }
        do {
            result = to_string(num % 7) + result;
            num = num / 7;
        } while (num > 0);

        if (negative) {
            return "-" + result;
        }
        return result;
    }
};