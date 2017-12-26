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
    int maxRotateFunction(vector<int>& A) {
        int result = 0;
        int sum = 0;

        int n = A.size();
        for (int i = 0; i < n; i++) {
            sum += A[i];
            result += i * A[i];
        }
        int last = result;
        for (int i = 1; i < n; i++) {
            last += sum - n * A[n - i];
            result = max(result, last);
        }

        return result;
    }
};

int main() {
    Solution s;
    return 0;
}