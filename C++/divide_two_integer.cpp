#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <cmath>
using namespace std;

int divide(int dividend, int divisor) {
        if (dividend == 0) {
            return 0;
        }
        if (divisor == 1) {
            return dividend;
        }
        if (divisor == -1) {
            return 0 - dividend;
        }
        
		long long a = dividend;
		long long b = divisor;
        if (a < 0) {
			a = 0 - a;
		}
		if (b < 0) {
			b = 0 - b;
		}
        if (a < b) {
            return 0;
        }
        
        long long result = 0;
        long long count = 1;
        long long temp = b;
        
        while (a >= b) {
            count = 1;
            temp = b;
            while (temp <= a) {
                a -= temp;
                result += count;
                
                temp = temp << 1;
                count = count << 1;
            }
        }
        
        if ((dividend ^ divisor) >> 31) {
            return 0 - result;
        }
        return result;
    }

int main() {
	int a = -2147483648;
	int b = 2;
	divide(a, b);
	return 0;
}