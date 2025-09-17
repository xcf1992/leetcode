/*
1432. Max Difference You Can Get From Changing an Integer
https://leetcode.com/problems/max-difference-you-can-get-from-changing-an-integer/

You are given an integer num.
You will apply the following steps exactly two times:

Pick a digit x (0 <= x <= 9).
Pick another digit y (0 <= y <= 9).
The digit y can be equal to x.
Replace all the occurrences of x in the decimal representation of num by y.
The new integer cannot have any leading zeros, also the new integer cannot be 0.
Let a and b be the results of applying the operations to num the first and second times, respectively.

Return the max difference between a and b.

Example 1:
Input: num = 555
Output: 888
Explanation: The first time pick x = 5 and y = 9 and store the new integer in a.
The second time pick x = 5 and y = 1 and store the new integer in b.
We have now a = 999 and b = 111 and max difference = 888

Example 2:
Input: num = 9
Output: 8
Explanation: The first time pick x = 9 and y = 9 and store the new integer in a.
The second time pick x = 9 and y = 1 and store the new integer in b.
We have now a = 9 and b = 1 and max difference = 8

Example 3:
Input: num = 123456
Output: 820000

Example 4:
Input: num = 10000
Output: 80000

Example 5:
Input: num = 9288
Output: 8700

Constraints:
1 <= num <= 10^8
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
#include <set>
#include <numeric>
using namespace std;

class Solution {
private:
    long long sti(string str) {
        reverse(str.begin(), str.end());
        long long ans=0, base=1;
        for (int i = 0; i < str.size(); i++) {
            ans += (str[i] - '0') * base;
            base *= 10;
        }
        return ans;
    }
public:
    int maxDiff(int num) {
        string a = to_string(num);
        int ind=0;
        //Maximizing the Integer value;
        //Starting from the first left, we move towards right till we get an Integer which is not 9, and we replace that with 9
        //Thereby, the number becomes Maximal
        while(a[ind]=='9')
            ind++;
        //We store the character
        char c = a[ind];
        for(int i=ind; i<a.size(); i++)
            if(a[i]==c)
                a[i]='9';
        //Store this value in a variable;
        long long ans = sti(a);
        string b = to_string(num);
        ind=0;
        //Since, we are to minimize the integer now
        //We traverse from left and ignore 1 and 0 from left;
        while(b[ind]=='1' || b[ind]=='0')
            ind++;
        //We store the character
        c = b[ind];
        for (int i=ind; i<b.size(); i++) {
            if(b[i]==c) {
                if(ind==0) //Since, integer cannot have leading zeroes, if ind==0, we replace the digits with 1;
                    b[i]='1';
                else // Else, we replace occurence of the digit with 0;
                    b[i]='0';
            }
        }
        //Subtract the value from previous maximal value;
        ans=ans-sti(b);
        return ans;
    }
};
