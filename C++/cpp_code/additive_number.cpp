/*
306. Additive Number
https://leetcode.com/problems/additive-number/

Additive number is a string whose digits can form additive sequence.
A valid additive sequence should contain at least three numbers.
Except for the first two numbers, each subsequent number in the sequence must be the sum of the preceding two.

For example:
"112358" is an additive number because the digits can form an additive sequence: 1, 1, 2, 3, 5, 8.
1 + 1 = 2, 1 + 2 = 3, 2 + 3 = 5, 3 + 5 = 8
"199100199" is also an additive number, the additive sequence is: 1, 99, 100, 199.
1 + 99 = 100, 99 + 100 = 199

Note:
Numbers in the additive sequence cannot have leading zeros, so sequence 1, 2, 03 or 1, 02, 3 is invalid.

Given a string containing only digits '0'-'9',
write a function to determine if it's an additive number.

Follow up:
How would you handle overflow for very large input integers?
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
using namespace std;
/*
use a helper function to add two strings.

Choose first two number then recursively check.

Note that the length of first two numbers can't be longer than half of the initial string,
so the two loops in the first function will end
when i>num.size()/2 and j>(num.size()-i)/2,
this will actually save a lot of time.

Update the case of heading 0s
e.g. "100010" should return false
*/
class Solution1 {
private:
    bool check(string num1, string num2, string num) {
        if ((num1.size() > 1 and num1[0] == '0') or (num2.size() > 1 and num2[0] == '0')) {
            return false;
        }

        string sum = add(num1, num2);
        if (num == sum) {
            return true;
        }

        if (num.size() <= sum.size() or sum != num.substr(0, sum.size())) {
            return false;
        }
        return check(num2, sum, num.substr(sum.size()));
    }

    string add(string n, string m) {
        string res;
        int i = n.size() - 1;
        int j = m.size() - 1;
        int carry = 0;
        while (i >= 0 or j >= 0 or carry > 0) {
            int sum = carry;
            if (i >= 0) {
                sum += n[i] - '0';
                i -= 1;
            }
            if (j >= 0) {
                sum += m[j] - '0';
                j -= 1;
            }
            res.push_back(sum % 10 + '0');
            carry = sum / 10;
        }
        reverse(res.begin(), res.end());
        return res;
    }

public:
    bool isAdditiveNumber(string num) {
        int n = num.size();
        for (int i = 1; i <= n / 2; i++) {
            for (int j = 1; j <= (n - i) / 2; j++) {
                if (check(num.substr(0, i), num.substr(i, j), num.substr(i + j))) {
                    return true;
                }
            }
        }
        return false;
    }
};

class Solution1 {
private:
    bool isValid(string num1, string num2, string num3) {
        if (num1.size() > 1 and num1[0] == '0') {
            return false;
        }
        if (num2.size() > 1 and num2[0] == '0') {
            return false;
        }

        string sum = add(num1, num2);
        if (sum == num3) {
            return true;
        }

        if (num3.size() <= sum.size() or sum != num3.substr(0, sum.size())) {
            return false;
        }
        return isValid(num2, sum, num3.substr(sum.size()));
    }

    string add(string num1, string num2) {
        return to_string(stol(num1) + stol(num2));
    }

public:
    bool isAdditiveNumber(string num) {
        int n = num.size();
        for (int i = 1; i <= n / 2; i++) {
            for (int j = 1; j <= (n - i) / 2; j++) {
                if (isValid(num.substr(0, i), num.substr(i, j), num.substr(i + j))) {
                    return true;
                }
            }
        }
        return false;
    }
};