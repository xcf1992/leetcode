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
    int arr[3] = {2, 3, 5};
public:
    bool isUgly(int num) {
        if (num <= 0) {
            return false;
        }
        
        for (auto i : arr) {
            while (num % i == 0) {
                num /= i;
            }
            if (num == 1) {
                return true;
            }
        }
        
        return num == 1;
    }
};

int main() {
    Solution s;
    return 0;
}