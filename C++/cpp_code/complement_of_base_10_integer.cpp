/*
 1012. Complement of Base 10 Integer

 Every non-negative integer N has a binary representation.
 For example, 5 can be represented as "101" in binary,
 11 as "1011" in binary, and so on.
 Note that except for N = 0, there are no leading zeroes in any binary representation.

 The complement of a binary representation is the number in binary you get when changing every 1 to a 0 and 0 to a 1.
 For example, the complement of "101" in binary is "010" in binary.

 For a given number N in base-10,
 return the complement of it's binary representation as a base-10 integer.
 Example 1:

 Input: 5
 Output: 2
 Explanation: 5 is "101" in binary, with complement "010" in binary, which is 2 in base-10.
 Example 2:

 Input: 7
 Output: 0
 Explanation: 7 is "111" in binary, with complement "000" in binary, which is 0 in base-10.
 Example 3:

 Input: 10
 Output: 5
 Explanation: 10 is "1010" in binary, with complement "0101" in binary, which is 5 in base-10.


 Note:

 0 <= N < 10^9
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
public:
    int bitwiseComplement(int N) {
        int X = 1;
        while (N > X) {
            X = X * 2 + 1;
        }
        return X - N;
    }
};

class Solution1 {
public:
    int bitwiseComplement(int N) {
        if (N == 0) {
            return 0;
        }

        string binary = "";
        while (N > 0) {
            binary.push_back('0' + (N & 1));
            N >>= 1;
        }

        int result = 0;
        for (int i = binary.size() - 1; i >= 0 ; i--) {
            result = result * 2 + 1 - (binary[i] - '0');
        }
        return result;
    }
};
