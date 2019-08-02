/*
 233. Number of Digit One
 Given an integer n, count the total number of digit 1 appearing in all non-negative integers less than or equal to n.

 For example:
 Given n = 13,
 Return 6, because digit 1 occurred in the following numbers: 1, 10, 11, 12, 13.
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
using namespace std;

/*
Solution explanation:

Let's start by counting the ones for every 10 numbers...

0, 1, 2, 3 ... 9 (1)

10, 11, 12, 13 ... 19 (1) + 10

20, 21, 22, 23 ... 29 (1)

...

90, 91, 92, 93 ... 99 (1)

100, 101, 102, 103 ... 109 (10 + 1)

110, 111, 112, 113 ... 119 (10 + 1) + 10

120, 121, 122, 123 ... 129 (10 + 1)

...

190, 191, 192, 193 ... 199 (10 + 1)

1). If we don't look at those special rows (start with 10, 110 etc),
we know that there's a one at ones' place in every 10 numbers,
there are 10 ones at tens' place in every 100 numbers,
and 100 ones at hundreds' place in every 1000 numbers, so on and so forth.

Ok, let's start with ones' place and count how many ones at this place,
set k = 1, as mentioned above, there's a one at ones' place in every 10 numbers,
so how many 10 numbers do we have?
The answer is (n / k) / 10.

Now let's count the ones in tens' place,
set k = 10, as mentioned above,
there are 10 ones at tens' place in every 100 numbers,
so how many 100 numbers do we have?
The answer is (n / k) / 10,
and the number of ones at ten's place is (n / k) / 10 * k.

Let r = n / k, now we have a formula to count the ones at k's place: r / 10 * k

2). So far, everything looks good, but we need to fix those special rows, how?

We can use the mod.
Take 10, 11, and 12 for example,
if n is 10, we get (n / 1) / 10 * 1 = 1 ones at ones's place, perfect,
but for tens' place, we get (n / 10) / 10 * 10 = 0,
that's not right, there should be a one at tens' place!
Calm down, from 10 to 19, we always have a one at tens's place,
let m = n % k, the number of ones at this special place is m + 1,

so let's fix the formula to be:
r / 10 * k + (r % 10 == 1 ? m + 1 : 0)

3). Wait, how about 20, 21 and 22?
Let's say 20, use the above formula we get 0 ones at tens' place,
but it should be 10! How to fix it?
We know that once the digit is larger than 2,
we should add 10 more ones to the tens' place,
a clever way to fix is to add 8 to r, so our final formula is:
(r + 8) / 10 * k + (r % 10 == 1 ? m + 1 : 0)

As you can see, it's all about how we fix the formula. Really hope that makes sense to you.
*/

/*
For every digit in n (Suppose n = 240315, the digits are 2, 4, 0, 3, 1, 5)，
I respectively count the number of digit 1 assuming the position of current digit is 1 and other digits of n is arbitrary.

For example, I select 3 in n as the current digit,
and I suppose the position of 3 is 1.

The highn is the number composed with the digits before the current digit.
In the example, highn = 240;

The lown is the number composed with the digits after the current digit.
In the example, lown = 15.

The lowc = 10 ^ (the number of lower digits).
In the example, lowc = 100;

As curn = 3 and curn > 1,
(highn * 10 + 1) must be less than (highn * 10 + curn).
Then the higher part can be 0 ~ highn,
the lower part can be 0 ~ (lowc-1),
and the current result = (highn + 1) * lowc.

=====
From the figure, we can see that from digit '1' at ones place repeat in group of 1 after interval of 10.
Similarly, '1' at tens place repeat in group of 10 after interval of 100.
This can be formulated as (n / (i*10)) * i

Also, notice that if the digit at tens place is 1,
then the number of terms with 1s is increased by x+1,
if the number is say "ab1x".
As if digits at tens place is greater than 1, then all the 10 occurances of numbers with '1'
at tens place have taken place, hence, we add 10.
This is formluated as min(max((n mod (i*10))−i+1,0), i).

Lets take an example, say n= 1234

No of ’1’ in ones place = 1234/10 (corresponding to 1,11,21,...1221) + min(4,1)(corresponding to 1231) = 124

No of ’1’ in tens place = (1234/100)*10 (corresponding to 10,11,12,...,110,111,...1919) + min(25,10)(corresponding to 1210,1211,...1219)=130

No of ’1’ in hundreds place = (1234/1000)*100 (corresponding to 100,101,102,...,199) + min(135,100)(corresponding to 1100,1101...1199)=200

No of ’1’ in thousands place = (1234/10000)*10000 + min(235,1000)(corresponding to 1000,1001,...1234)= 235

Therefore, Total = 124+130+200+235 = 689
Herein, one formula has been devised,
but many other formulae can be devised for faster implementations,
but the essence and complexity remains the same.
The users are encouraged to try to divise their own version of solution using the mathematical concepts.
*/
class Solution {
public:
    int countDigitOne(int n) {
        int result = 0;
        for (long i = 1; i <= n; i *= 10) {
            long divider = i * 10;
            result += (n / divider) * i;
            if (n % divider - i + 1 > 0) {
                result += min(i, n % divider - i + 1);
            }
        }
        return result;
    }
};

class Solution1 {
public:
    int countDigitOne(int n) {
        int result = 0;
        int factor = 1;
        int lowerNum = 0;
        int curNum = 0;
        int higherNum = 0;

        while (n / factor != 0) {
            lowerNum = n - (n / factor) * factor;
            curNum = (n / factor) % 10;
            higherNum = n / (factor * 10);

            if (curNum == 0) {
                result += higherNum * factor;
            }
            else if (curNum == 1) {
                result += higherNum * factor + lowerNum + 1;
            }
            else {
                result += (higherNum + 1) * factor;
            }
            factor *= 10;
        }
        return result;
    }
};
