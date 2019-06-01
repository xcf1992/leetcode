/*
372. Super Pow

 Your task is to calculate ab mod 1337 where a is a positive integer and b is an extremely large positive integer given in the form of an array.
 
 Example1:
 
 a = 2
 b = [3]
 
 Result: 8
 Example2:
 
 a = 2
 b = [1,0]
 
 Result: 1024
 */

#include <iostream>
#include <sstream>
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
    int MOD = 1337;

    int calculate(int a, int k) {
        a %= MOD;
        int result = 1;
        for (int i = 0; i < k; i++) {
            result = (result * a) % MOD;
        }
        return result % MOD;
    }
public:
    int superPow(int a, vector<int>& b) {
        if (b.empty()) {
            return 1;
        }
        
        int k = b.back();
        b.pop_back();
        return calculate(superPow(a, b), 10) * calculate(a, k) % MOD;
    }
};
