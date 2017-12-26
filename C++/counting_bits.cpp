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
    vector<int> countBits(int num) {
        vector<int> result(num + 1, 0);
        for (int i = 1; i <= num; i++) {
            int quotient = i >> 1;
            if (i & 1) {
                result[i] = result[quotient] + 1;
            }
            else {
                result[i] = result[quotient];
            }
        }
        return result;
    }
};

int main() {
    Solution s;
    vector<int> result = s.countBits(5);
    for (int i = 0; i < result.size(); i++) {
        cout << result[i] << " ";
    }
    return 0;
}