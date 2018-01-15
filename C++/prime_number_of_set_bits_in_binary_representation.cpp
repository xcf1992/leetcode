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
    set<int> primes = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29 };
public:
    int countPrimeSetBits(int l, int r) {
        int result = 0;
        for (int i = l; i <= r; i++) {
            int bits = 0;
            for (int n = i; n; n >>= 1)
                bits += n & 1;
            result += primes.count(bits);
        }
        return result;
    }
};
