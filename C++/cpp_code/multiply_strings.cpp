/*
43. Multiply Strings
Given two non-negative integers num1 and num2 represented as strings,
return the product of num1 and num2, also represented as a string.

Example 1:

Input: num1 = "2", num2 = "3"
Output: "6"
Example 2:

Input: num1 = "123", num2 = "456"
Output: "56088"
Note:

The length of both num1 and num2 is < 110.
Both num1 and num2 contain only digits 0-9.
Both num1 and num2 do not contain any leading zero, except the number 0 itself.
You must not use any built-in BigInteger library or convert the inputs to integer directly.

*/
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

class Solution {
private:
    string addString(string num1, string num2) {
        if (num1.size() < num2.size()) {
            swap(num1, num2);
        }

        int add = 0;
        int n1 = num1.size() - 1;
        int n2 = num2.size() - 1;
        while (n1 >= 0 or n2
        >=
        0
        )
        {
            int sum = 0;
            sum += add;
            if (n1 >= 0) {
                sum += num1[n1] - '0';
            }
            if (n2 >= 0) {
                sum += num2[n2] - '0';
            }
            num1[n1] = sum % 10 + '0';
            add = sum / 10;
            n1 -= 1;
            n2 -= 1;
        }
        return add == 0 ? num1 : to_string(add) + num1;
    }

public:
    string multiply(string num1, string num2) {
        if (num1.empty() or
        num2.empty()
        or num1
        ==
        "0"
        or num2
        ==
        "0"
        )
        {
            return "0";
        }
        if (num1.size() < num2.size()) {
            swap(num1, num2);
        }

        vector<string> products;
        string tail = "";
        for (int pos = num2.size() - 1; pos >= 0; pos--) {
            if (num2[pos] == '0') {
                tail.push_back('0');
                continue;
            }

            string product = "";
            int add = 0;
            int d2 = num2[pos] - '0';
            for (int idx = num1.size() - 1; idx >= 0; idx--) {
                int d1 = num1[idx] - '0';
                int result = d1 * d2 + add;
                product.push_back('0' + result % 10);
                add = result / 10;
            }
            reverse(product.begin(), product.end());
            if (add != 0) {
                product = to_string(add) + product;
            }
            product += tail;
            products.push_back(product);
            tail.push_back('0');
        }

        string addSum = products[0];
        for (int i = 1; i < products.size(); i++) {
            addSum = addString(addSum, products[i]);
        }
        return addSum;
    }
};