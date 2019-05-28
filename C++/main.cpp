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
#include <map>
#include <numeric>
using namespace std;

class Solution {
public:
    int nextGreaterElement(int n) {
        string num = to_string(n);
        int len = num.size();
        if (len == 1) {
            return -1;
        }
        if (len == 2) {
            if (num.front() >= num.back()) {
                return -1;
            }
            swap(num[0], num[1]);
            return stoi(num);
        }

        int left = len - 1;
        while (left - 1 >= 0 and num[left - 1] >= num[left]) {
            left -= 1;
        }
        if (left == 0) {
            return -1;
        }

        int right = len - 1;
        while (num[right] <= num[left - 1]) {
            right -= 1;
        }
        swap(num[left - 1], num[right]);

        right = len - 1;
        while (left < right) {
            swap(num[left++], num[right--]);
        }

        long long result = stol(num);
        return result > (long)INT_MAX ? -1 : result;
    }
};

int main() {
    Solution s;
    vector<int> temp({0,1,3,50,75});
    vector<vector<int>> matrix({
        {1,2,3},
        {4,5,6},
        {7,8,9}
    });
    s.nextGreaterElement(12443322);
}
