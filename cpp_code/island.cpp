#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

class Solution {
public:
    unsigned int reverseBits(unsigned int n) {
        if (n == 0) {
            return n;
        }

        int result = 0;
        int bit = 0;
        for (int i = 0; i < 32; i++) {
            bit = n & 1;
            if (bit == 1) {
                bit <<= (31 - i);
                result = result | bit;
            }
        }

        return result;
    }
};