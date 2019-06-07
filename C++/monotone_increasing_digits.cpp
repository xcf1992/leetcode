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
    int monotoneIncreasingDigits(int N) {
        string num = to_string(N);
        int len = num.size();
        int pos = 0;
        while (pos < len and num[pos - 1] <= num[pos]) {
            pos += 1;
        }
        while (pos > 0 and pos < len and num[pos - 1] > num[pos]) {
            num[pos - 1] -= 1;
            pos -= 1;
        }
        for (int i = pos + 1; i < len; ++i) {
            num[i] = '9';
        }
        return stoi(num);
    }
};

class Solution {
public:
    int monotoneIncreasingDigits(int N) {
        string num = to_string(N);
        int i = 0;
        while (i < num.size() - 1) {
            if (num[i] > num[i + 1]) {
                break;
            }
            i++;
        }
        
        if (i == num.size() - 1) {
            return N;
        }
        
        while (i >= 1 && num[i - 1] == num[i]) {
            i--;
        }
        
        num[i] -= 1;
        do {
            i += 1;
            num[i] = '9';
        } while (i < num.size());
        
        int result = 0;
        for (char c : num) {
            result = result * 10 + c - '0';
        }
        return result;
    }
};
