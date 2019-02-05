/*
 483. Smallest Good Base

 For an integer n, we call k>=2 a good base of n, if all digits of n base k are 1.

 Now given a string representing n, you should return the smallest good base of n in string format.

 Example 1:

 Input: "13"
 Output: "3"
 Explanation: 13 base 3 is 111.


 Example 2:

 Input: "4681"
 Output: "8"
 Explanation: 4681 base 8 is 11111.


 Example 3:

 Input: "1000000000000000000"
 Output: "999999999999999999"
 Explanation: 1000000000000000000 base 999999999999999999 is 11.


 Note:

 The range of n is [3, 10^18].
 The string representing n is always valid and will not have leading zeros.
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

/*
 First things first. Let's see the math behind it.

 From given information, we can say one thing- Numbers will be of form-

 n = k^m + k^(m-1) + ... + k + 1
 => n-1 = k^m + k^(m-1) + ... + k
 => n-1 = k (k^(m-1) + k^(m-2) + ... + k + 1) ...... [1]

 Also, from n = k^m + k^(m-1) + ... + k + 1, we can say,
 n-k^m = k^(m-1) + k^(m-2) + ... + k + 1 ...... [2]

 from [1] and [2],

 n-1 = k (n - k^m)
 =>k^(m+1) = nk - n + 1

 if you shuffle sides you will end up getting following form,

 (k^(m+1) - 1)/(k - 1) = n .... [3]

 Also from [1] note that, (n - 1) must be divisible by k.

 We know that, n = k^m + k^(m-1) + ... + k + 1

 => n > k^m
 => m-th root of n > k .... [4]

 [EDIT] -->

 With inputs from @StefanPochmann we can also say, from binomial thorem, n = k^m + ... + 1 < (k+1)^m .... [5]
 Therefore, k+1 > m-th root of n > k. .... from [4] and [5]
 Thus ⌊m-th root of n⌋ is the only candidate that needs to be tested. [6]

 <--

 So our number should satisfy this equation where k will be our base and m will be (number of 1s - 1)

 This brings us to the search problem where we need to find k and m.

 Linear search from 1 to n does not work. it gives us TLE. So it leaves us with performing some optimization on search space.

 From [6] we know that the only candidate that needs to be tested is, ⌊m-th root of n⌋

 We also know that the smallest base is 2 so we can find our m must be between 2 and log2n else m is (n-1) [7]

 That brings me to the code:
 */
/*
 The input can be stored in a long long int, here I use unsigned long long int for a larger range. We need to find k, for 1+k^1+k^2+k^3+...+k^d=n. The smallest possible base is k=2, with has the longest possible representation, i.e., largest d. So, to find the smallest base means to find the longest possible representation "11111....1" based on k. As n<=10^18, so n<(1<<62). We iterate the length of the representation from 62 to 2 (2 can always be valid, with base=n-1), and check whether a given length can be valid.

 For a given length d, we use binary search to check whether there is a base k which satisfies 1+k^1+k^2+...k^d=n. The left limit is 1, and the right limit is pow(n,1/d)+1, i.e., the d th square root of n. The code is shown below.
 */
class Solution {
private:
    unsigned long long check(unsigned long long num, int len) {
        double n = (double) num;
        unsigned long long left = 1;
        unsigned long long right  = (unsigned long long) (pow(n, 1.0 / len) + 1);
        while (left <= right) {
            unsigned long long mid = left + (right - left) / 2;
            unsigned long long sum = 1, cur = 1;
            for (int i = 1; i <= len; i++) {
                cur *= mid;
                sum += cur;
            }

            if (sum == num) {
                return mid;
            }
            if (sum > num) {
                right = mid - 1;
            }
            else {
                left = mid + 1;
            }
        }
        return 0;
    }
public:
    string smallestGoodBase(string n) {
        unsigned long long num = (unsigned long long) stoll(n);
        unsigned long long x = 1;
        for (int len = 62; len > 1; len--) {
            if ((x << len) < num) {
                unsigned long long cur = check(num, len);
                if (cur != 0) {
                    return to_string(cur);
                }
            }
        }
        return to_string(num - 1);
    }
};
