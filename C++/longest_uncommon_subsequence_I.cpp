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
    int findLUSlength(string a, string b) {
        if (a.length() != b.length()) {
            return max(a.length(), b.length());
        }

        for (int i = 0; i < a.length(); i++) {
            if (a[i] != b[i]) {
                return a.length();
            }
        }

        return -1;
    }
};

int main() {
    Solution s;
    return 0;
}
