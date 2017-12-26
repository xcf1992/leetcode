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
private:
    int count(vector<int>& numbers, int n) {
        if (n <= 0) {
            return 1;
        }
        int result = 0;
        for (int i = 0; i < n; i++) {
            if (numbers[i] % n == 0 || n % numbers[i] == 0) {
                swap(numbers[i], numbers[n - 1]);
                result += count(numbers, n - 1);
                swap(numbers[i], numbers[n - 1]);
            }
        }
        return result;
    }
public:
    int countArrangement(int N) {
        vector<int> numbers;
        for (int i = 1; i <= N; i++) {
            numbers.push_back(i);
        }
        return count(numbers, N);
    }
};

int main() {
    Solution s;
    return 0;
}
