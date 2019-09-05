/*
 564. Find the Closest Palindrome
 Given an integer n, find the closest integer (not including itself), which is a palindrome.

 The 'closest' is defined as absolute difference minimized between two integers.

 Example 1:
 Input: "123"
 Output: "121"
 Note:
 The input n is a positive integer represented by string, whose length will not exceed 18.
 If there is a tie, return the smaller one as answer.
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
#include <numeric>
using namespace std;

/*
Let's build a list of candidate answers for which the final answer must be one of those candidates.
Afterwards, choosing from these candidates is straightforward.

If the final answer has the same number of digits as the input string S,
then the answer must be the middle digits + (-1, 0, or 1) flipped into a palindrome.
For example, 23456 had middle part 234, and 233, 234, 235 flipped into a palindrome yields
23332, 23432, 23532. Given that we know the number of digits,
the prefix 235 (for example) uniquely determines the corresponding palindrome 23532,
so all palindromes with larger prefix like 23732 are strictly farther away from S than 23532 >= S.

If the final answer has a different number of digits,
it must be of the form 999....999 or 1000...0001,
as any palindrome smaller than 99....99 or bigger than 100....001 will be farther away from S.
*/
class Solution {
private:
    string makePalindromic(string s) {
        for (int i = 0, j = s.size() - 1; i < j; i++, j--) {
            s[j] = s[i];
        }
        return s;
    }
public:
    string nearestPalindromic(string n) {
        if (n == "0") {
            return "1";
        }

        long long orgVal = stoll(n);
        // candidate #1 (ex: 123xx -> 12321, 123xxx -> 123321)
        string result = makePalindromic(n);
        long long resVal = stoll(result);
        long long diff = abs(resVal - orgVal);

        long long scale = (long long)pow(10, n.size() / 2);
        // candidate #2 (ex: 123xx -> 12221, 123xxx -> 122221, 100xx -> 9999)
        string smaller = makePalindromic(to_string((orgVal / scale) * scale - 1));
        // candidate #3 (ex: 123xx -> 12421, 123xxx -> 124421, 99xx -> 10001)
        string bigger = makePalindromic(to_string((orgVal / scale) * scale + scale));

        long long smallerVal = stoll(smaller);
        if (diff == 0 or abs(orgVal - smallerVal) <= diff) {
            result = smaller;
            diff = abs(orgVal - smallerVal);
        }

        long long biggerVal = stoll(bigger);
        if (abs(orgVal - biggerVal) < diff) {
            result = bigger;
        }
        return result;
    }
};

// wrong answer
class Solution1 {
private:
    long long getNum(string n) {
        long long result = 0;
        for (char c : n) {
            result = result * 10 + (c - '0');
        }
        return result;
    }

    char getClosetPalindrome(string num, string original, int len) { // make sure we get the smaller and closet number, test case 1938013391, 1938943391, "12389"
        long long num1;
        long long num2;
        string n1 = num;
        string n2 = num;
        if (num[0] == '9') {
            for (int i = 0; i < len; i++) {
                n1[i] = '8';
            }
            num1 = getNum(n1);
            for (int i = 0; i < len; i++) {
                n2[i] = '9';
            }
            num2 = getNum(n2);
        }
        else {
            for (int i = 0; i < len; i++) {
                n1[i] = num[0];
            }
            num1 = getNum(n1);
            for (int i = 0; i < len; i++) {
                n2[i] = num[0] + 1;
            }
            num2 = getNum(n2);
        }
        long long oldNum = getNum(original);
        if (abs(num1 - oldNum) > abs(num2 - oldNum)) {
            return n2[0];
        }
        return n1[0];
    }
public:
    string nearestPalindromic(string n) {
        if (n.size() == 1) { // 0 to -1, 9 to 8
            return to_string(stoi(n) - 1);
        }
        int left = 0;
        int right = n.size() - 1;
        string temp = n;
        bool allZero = true;
        bool onlyNine = true;
        while (left <= right) {
            if (n[left] != n[right]) {
                if (left + 1 == right) { // 28 should change to 33 but not 22
                    char closet = getClosetPalindrome(n.substr(left), temp.substr(left), 2);
                    n[left] = closet;
                    n[right] = closet;
                }
                else {
                    n[right] = n[left];
                }
                if (left != 0) {
                    allZero = false;
                }
                onlyNine = false;
            }
            else {
                if (left != 0 and n[left] != '0') {
                    allZero = false;
                }
                if (n[left] != '9') {
                    onlyNine = false;
                }
                if (left == right) {
                    char closet = getClosetPalindrome(n.substr(left), temp.substr(left), 1);
                    n[left] = closet;
                }
            }
            left += 1;
            right -= 1;
        }
        if (onlyNine) { // 999 should be changed to 1001
            return "1" + string(n.size() - 1, '0') + "1";
        }
        if (allZero) { // 10001 should be changed to 9999
            if (temp.front() == '1') {
                if (temp.back() == '0' or temp.back() == '1') {
                    return string(n.size() - 1, '9');
                }
            }
        }
        if (temp != n) {
            return n;
        }

        n[left] -= n[left] == '0' ? -1 : 1;
        if (left == right) {
            return n;
        }
        n[right] -= n[right] == '0' ? -1 : 1;
        return n;
    }
};
