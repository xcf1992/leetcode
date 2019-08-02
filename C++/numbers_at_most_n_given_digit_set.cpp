/*
 902. Numbers At Most N Given Digit Set
 We have a sorted set of digits D,
 a non-empty subset of {'1','2','3','4','5','6','7','8','9'}.
 (Note that '0' is not included.)

 Now, we write numbers using these digits, using each digit as many times as we want.
 For example, if D = {'1','3','5'}, we may write numbers such as '13', '551', '1351315'.

 Return the number of positive integers that can be written (using the digits of D) that are less than or equal to N.

 Example 1:

 Input: D = ["1","3","5","7"], N = 100
 Output: 20
 Explanation:
 The 20 numbers that can be written are:
 1, 3, 5, 7, 11, 13, 15, 17, 31, 33, 35, 37, 51, 53, 55, 57, 71, 73, 75, 77.
 Example 2:

 Input: D = ["1","4","9"], N = 1000000000
 Output: 29523
 Explanation:
 We can write 3 one digit numbers, 9 two digit numbers, 27 three digit numbers,
 81 four digit numbers, 243 five digit numbers, 729 six digit numbers,
 2187 seven digit numbers, 6561 eight digit numbers, and 19683 nine digit numbers.
 In total, this is 29523 integers that can be written using the digits of D.


 Note:

 D is a subset of digits '1'-'9' in sorted order.
 1 <= N <= 10^9
 */
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
    // count the number with the same length as num but <= num
    long count(vector<int>& digit, string num, int pos) {
        if (pos >= num.size()) {
            // should return 1, means at have 1 number that is equal to num
            return 1;
        }

        long result = 0;
        int less = 0; // the number of digit which is less than current num[pos]
        for (int i = 0; i < digit.size(); i++) {
            if (digit[i] < (num[pos] - '0')) {
                less += 1;
            }
            else if (digit[i] == (num[pos] - '0')) {
                result += count(digit, num, pos + 1);
            }
            else {
                break;
            }
        }
        result += less * pow(digit.size(), num.size() - pos - 1);
        return result;
    }
public:
    int atMostNGivenDigitSet(vector<string>& D, int N) {
        string num = to_string(N);
        int length = num.size();

        /*
        * for any number length less than N,
        * the total count of each length is (D.size()) ^ i
        */
        long result = 0;
        int n = D.size();
        for (int i = 1; i < length; i++) {
            result += n;
            n *= D.size();
        }

        vector<int> digit;
        for (string d : D) {
            digit.push_back(stoi(d));
        }
        return result + count(digit, num, 0);
    }
};
