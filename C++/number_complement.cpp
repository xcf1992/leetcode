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
    int findComplement(int num) {
        unsigned int mask = ~0;
        while (num & mask) {
            mask <<= 1;
        }
        return (~num) ^ mask;
    }
};

int main() {
    Solution s;
    cout << s.reverseWords("Let's take LeetCode contest");
    return 0;
}