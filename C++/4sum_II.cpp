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
    int fourSumCount(vector<int>& A, vector<int>& B, vector<int>& C, vector<int>& D) {
        int result = 0;
        unordered_map<int ,int> count;
        for (int a : A) {
            for (int b : B) {
                count[a + b] += 1;
            }
        }

        for (int c : C) {
            for (int d : D) {
                auto it = count.find(0 - c - d);
                if (it != count.end()) {
                    result += it -> second;
                }
            }
        }

        return result;
    }
};

int main() {
    Solution s;
    return 0;
}
