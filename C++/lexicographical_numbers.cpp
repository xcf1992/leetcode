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
    vector<int> lexicalOrder(int n) {
        vector<int> result(n);
        int current = 1;
        for (int i = 0; i < n; i++) {
            result[i] = current;
            if (current * 10 <= n) {
                current *= 10;
            }
            else {
                if (current == n) {
                    current /= 10;
                }
                current += 1;
                while (current % 10 == 0) {
                    current /= 10;
                }
            }
        }
        return result;
    }
};

int main() {
    Solution s;
    vector<int> result = s.lexicalOrder(131);
    for (int i = 0; i < result.size(); i++) {
        cout << result[i] << " ";
    }
    return 0;
}