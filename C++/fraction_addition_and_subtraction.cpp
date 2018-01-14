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
    int getGCD(int a, int b) {
        if (a == 0) {
            return b == 0 ? 0 : b;
        }
        else if (b == 0) {
            return a;
        }
        
        return a >= b ? getGCD(b, a % b) : getGCD(a, b % a);
    }
    
    int getLCM(int a, int b) {
        return a * b / getGCD(a, b);
    }
public:
    string fractionAddition(string expression) {
        int n = 0;
        int d = 1;
        int p = 1;
        
        int i = 0;
        while (i < expression.size()) {
            int n1 = 0;
            int d1 = 0;
            int p1 = 1;
            if (expression[i] == '-') {
                p1 = -1;
                i++;
            }
            else if (expression[i] == '+') {
                i++;
            }
            
            while (expression[i] >= '0' && expression[i] <= '9') {
                n1 = n1 * 10 + (expression[i] - '0');
                i++;
            }
            
            i++;
            
            while (expression[i] >= '0' && expression[i] <= '9' && i < expression.size()) {
                d1 = d1 * 10 + (expression[i] - '0');
                i++;
            }
            
            int lcm = getLCM(d, d1);
            int newn = p * n * (lcm / d) + p1 * n1 * (lcm / d1);
            d = lcm;
            if (newn >= 0) {
                p = 1;
                n = newn;
            }
            else {
                p = -1;
                n = 0 - newn;
            }
        }
        
        int gcd = getGCD(n, d);
        string result = p == 1 ? "" : "-";
        return result + to_string(n / gcd) + "/" + to_string(d / gcd);
    }
};
