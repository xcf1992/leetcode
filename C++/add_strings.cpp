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
    string addStrings(string num1, string num2) {
        if (num1.size() < num2.size()) {
            swap(num1, num2);
        }
        string result = "";
        int i = num1.size() - 1;
        int j = num2.size() - 1;
        int carry = 0;
        while (i >= 0 && j >= 0) {
            int sum = (num1[i] - '0') + (num2[j] - '0') + carry;
            carry = sum / 10;
            result = to_string(sum % 10) + result;
            i -= 1;
            j -= 1;
        }

        while (i >= 0) {
            int sum = (num1[i] - '0') + carry;
            carry = sum / 10;
            result = to_string(sum % 10) + result;
            i -= 1;
        }

        return carry == 0 ? result : to_string(carry) + result;
    }
};