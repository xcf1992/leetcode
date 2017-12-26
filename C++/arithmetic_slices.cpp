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
    int numberOfArithmeticSlices(vector<int>& A) {
        int result = 0;

        if (A.size() < 3) {
            return result;
        }

        int gap = A[1] - A[0];
        int size = 2;
        int i = 2;
        while (i < A.size()) {
            if (A[i] - A[i - 1] == gap) {
                size += 1;
            }
            else {
                if (size >= 3) {
                    result += (size - 1) * (size - 2) / 2;
                }
                size = 2;
                gap = A[i] - A[i - 1];
            }
            i++;
        }
        if (size >= 3) {
            result += (size - 1) * (size - 2) / 2;
        }

        return result;
    }
};

int main() {
    Solution s;
    return 0;
}
