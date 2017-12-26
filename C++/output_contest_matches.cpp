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
    string findContestMatch(int n) {
        vector<string> result;
        for (int i = 1; i <= n; i++) {
            result.push_back(to_string(i));
        }

        while (n > 1) {
            for (int i = 0; i < n / 2; i++) {
                result[i] = "(" + result[i] + "," + result[n - i - 1] + ")";
            }
            n /= 2;
        }
        return result[0];
    }
};