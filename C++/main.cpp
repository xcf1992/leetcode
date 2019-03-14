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
private:
    string toBinary(int num) {
        // change num to its binary string, so 6 will be 0011, the most significant bit will be right-most
        string result = "";
        while (num != 0) {
            result.push_back('0' + (num & 1));
            num >>= 1;
        }
        return result;
    }
public:
    int findIntegers(int num) {
        string nStr = toBinary(num);
        int n = nStr.size();
        vector<int> a(n, 1);
        vector<int> b(n, 1);
        for (int i = 1; i < n; i++) {
            a[i] = a[i - 1] + b[i - 1];
            b[i] = a[i - 1];
        }

        int result = a[n - 1] + b[n - 1];
        /*
         the count of valid number has n bit, some of them are bigger than num we want and we need to subtract them below
         then we subtract the solutions which is larger than num, we iterate from the MSB to LSB of num:

         if bit[i] == 1
         if bit[i + 1] == 0, there's no solutions in res that is larger than num, we go further into smaller bit and subtract.
         if bit[i + 1] == 1, we know in those res solutions it won't have any consecutive ones. when bit[i + 1] == 1, in one[i + 1], the i-th bit in valid solutions must be 0, which are all smaller than 'num', we don't need to check smaller bits and subtract, so we break form the loop.
         if bit[i] == 0
         if bit[i + 1] == 1, there's no solutions in res that is larger than num, we go further into smaller bit and subtract.
         if bit[i + 1] == 0, we know zero[i + 1] includes solutions of i-th == 0 (00***) and i-th bit == 1 (01***), we know the i-th bit of num is 0, so we need to subtract all the 01*** solutions because it is larger than num. Therefore, one[i] is subtracted from res.
         */
        for (int i = n - 2; i >= 0; i--) {
            if (nStr[i] == '1' and nStr[i + 1] == '1') {
                break;
            }
            if (nStr[i] == '0' and nStr[i + 1] == '0') {
                result -= b[i];
            }
        }
        return result;
    }
};

int main() {
    Solution s;
    s.findIntegers(12);
    return 0;
}
