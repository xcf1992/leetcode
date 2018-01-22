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
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    int maximumSwap(int num) {
        if (num < 10) {
            return num;
        }
        
        vector<int> digits;
        while (num > 0) {
            digits.push_back(num % 10);
            num /= 10;
        }
        
        vector<int> leftMax(digits.size(), 0);
        for (int i = 1; i < digits.size(); i++) {
            leftMax[i] = digits[i] > digits[leftMax[i - 1]] ? i : leftMax[i - 1];
        }
        
        for (int i = digits.size() - 1; i >= 0; i--) {
            if (leftMax[i] < i) {
                swap(digits[i], digits[leftMax[i]]);
                break;
            }
        }
        
        int result = 0;
        for (int digit : digits) {
            result = result * 10 + digit;
        }
        return result;
    }
};

int main() {
    Solution s;
    vector<string> v({"ABD","BCE","DEF","FFF"});
    cout << s.maximumSwap(2739) << endl;
}
