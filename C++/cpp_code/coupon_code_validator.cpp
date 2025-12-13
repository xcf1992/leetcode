/*
https://leetcode.com/problems/coupon-code-validator/description/
3606. Coupon Code Validator

You are given three arrays of length n that describe the properties of n coupons: code, businessLine, and isActive. The
ith coupon has:

code[i]: a string representing the coupon identifier.
businessLine[i]: a string denoting the business category of the coupon.
isActive[i]: a boolean indicating whether the coupon is currently active.
A coupon is considered valid if all of the following conditions hold:

code[i] is non-empty and consists only of alphanumeric characters (a-z, A-Z, 0-9) and underscores (_).
businessLine[i] is one of the following four categories: "electronics", "grocery", "pharmacy", "restaurant".
isActive[i] is true.
Return an array of the codes of all valid coupons, sorted first by their businessLine in the order: "electronics",
"grocery", "pharmacy", "restaurant", and then by code in lexicographical (ascending) order within each category.



Example 1:

Input: code = ["SAVE20","","PHARMA5","SAVE@20"], businessLine = ["restaurant","grocery","pharmacy","restaurant"],
isActive = [true,true,true,true]

Output: ["PHARMA5","SAVE20"]

Explanation:

First coupon is valid.
Second coupon has empty code (invalid).
Third coupon is valid.
Fourth coupon has special character @ (invalid).
Example 2:

Input: code = ["GROCERY15","ELECTRONICS_50","DISCOUNT10"], businessLine = ["grocery","electronics","invalid"], isActive
= [false,true,true]

Output: ["ELECTRONICS_50"]

Explanation:

First coupon is inactive (invalid).
Second coupon is valid.
Third coupon has invalid business line (invalid).


Constraints:

n == code.length == businessLine.length == isActive.length
1 <= n <= 100
0 <= code[i].length, businessLine[i].length <= 100
code[i] and businessLine[i] consist of printable ASCII characters.
isActive[i] is either true or false.
*/
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

class Solution {
private:
    bool valid_code(string& code) {
        for (char c : code) {
            if (!isalnum(c) && c != '_') {
                return false;
            }
        }
        return true;
    }

    bool valid_business_line(string& business) {
        return business == "electronics" || business == "grocery" || business == "pharmacy" || business == "restaurant";
    }

public:
    vector<string> validateCoupons(vector<string>& code, vector<string>& businessLine, vector<bool>& isActive) {
        int n = code.size();
        vector<pair<string, string>> coupons;
        for (int i = 0 ; i < n; i++) {
            if (!isActive[i] || code[i].empty() || !valid_code(code[i]) || !valid_business_line(businessLine[i])) {
                continue;
            }
            coupons.push_back(make_pair(businessLine[i], code[i]));
        }

        unordered_map<string, int> order = {
            {"electronics", 0},
            {"grocery", 1},
            {"pharmacy", 2},
            {"restaurant", 3}
        };
        sort(coupons.begin(), coupons.end(), [&](pair<string, string> p1, pair<string, string> p2) {
            return order[p1.first] < order[p2.first] || (p1.first == p2.first && p1.second < p2.second);
        });

        vector<string> rst;
        for (pair<string, string>& p : coupons) {
            rst.push_back(p.second);
        }
        return rst;
    }
};