/*
 Given a positive 32-bit integer n, you need to find the smallest 32-bit integer which has exactly the same digits existing in the integer n and is greater in value than n. If no such positive 32-bit integer exists, you need to return -1.
 
 Example 1:
 
 Input: 12
 Output: 21
 
 
 Example 2:
 
 Input: 21
 Output: -1
 */

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <map>
#include <unordered_set>
#include <algorithm>
#include <cmath>
#include <queue>
#include <stack>
#include <stdio.h>
#include <set>
using namespace std;

class Solution {
private:
    long getNum(vector<int> digit) {
        long result = 0;
        for (int i = digit.size() - 1; i >= 0; i--) {
            result = result * 10 + digit[i];
        }
        return result;
    }
public:
    int nextGreaterElement(int n) {
        if (n == 0) {
            return -1;
        }
        
        bool positive = true;
        if (n < 0) {
            positive = false;
            n = 0 - n;
        }
        
        int num = n;
        vector<int> digit;
        for (int i = 0; num != 0; i++) {
            digit.push_back(num % 10);
            num /= 10;
        }
        
        if (positive) {
            for (int i = 1; i < digit.size(); i++) {
                int newPos = i;
                int newDigit = 9;
                for (int j = i - 1; j >=0; j--) {
                    if (digit[j] > digit[i] && digit[j] < newDigit) {
                        newPos = j;
                        newDigit = digit[j];
                    }
                }
                if (newPos < i) {
                    swap(digit[i], digit[newPos]);
                    sort(digit.begin(), digit.begin() + i, greater<int>());
                    break;
                }
            }
            
            long result = getNum(digit);
            if (result > INT_MAX || result == n) {
                return -1;
            }
            return result;
        }
        
        for (int i = digit.size() - 1; i >= 0; i--) {
            int newPos = i;
            int newDigit = 0;
            for (int j = i - 1; j >=0; j--) {
                if (digit[j] < digit[i] && digit[j] > newDigit) {
                    newPos = j;
                    newDigit = digit[j];
                }
            }
            if (newPos < i) {
                swap(digit[i], digit[newPos]);
                sort(digit.begin(), digit.begin() + i, less<int>());
                break;
            }
        }
        
        long result = getNum(digit);
        if (result > INT_MAX || result == n) {
            return -1;
        }
        return 0 - result;
    }
};
