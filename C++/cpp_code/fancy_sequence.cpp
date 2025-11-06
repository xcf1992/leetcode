/*
1622. Fancy Sequence
https://leetcode.com/problems/fancy-sequence/

Write an API that generates fancy sequences using the append, addAll, and multAll operations.
Implement the Fancy class:
Fancy() Initializes the object with an empty sequence.
void append(val)
Appends an integer val to the end of the sequence.

void addAll(inc)
Increments all existing values in the sequence by an integer inc.

void multAll(m)
Multiplies all existing values in the sequence by an integer m.

int getIndex(idx)
Gets the current value at index idx (0-indexed) of the sequence modulo 109 + 7.
If the index is greater or equal than the length of the sequence, return -1.

Example 1:
Input
["Fancy", "append", "addAll", "append", "multAll", "getIndex", "addAll", "append", "multAll", "getIndex", "getIndex",
"getIndex"]
[[], [2], [3], [7], [2], [0], [3], [10], [2], [0], [1], [2]]
Output
[null, null, null, null, null, 10, null, null, null, 26, 34, 20]
Explanation
Fancy fancy = new Fancy();
fancy.append(2);   // fancy sequence: [2]
fancy.addAll(3);   // fancy sequence: [2+3] -> [5]
fancy.append(7);   // fancy sequence: [5, 7]
fancy.multAll(2);  // fancy sequence: [5*2, 7*2] -> [10, 14]
fancy.getIndex(0); // return 10
fancy.addAll(3);   // fancy sequence: [10+3, 14+3] -> [13, 17]
fancy.append(10);  // fancy sequence: [13, 17, 10]
fancy.multAll(2);  // fancy sequence: [13*2, 17*2, 10*2] -> [26, 34, 20]
fancy.getIndex(0); // return 26
fancy.getIndex(1); // return 34
fancy.getIndex(2); // return 20

Constraints:
1 <= val, inc, m <= 100
0 <= idx <= 105
At most 105 calls total will be made to append, addAll, multAll, and getIndex.
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
#include <cfloat>
#include <stdio.h>
#include <map>
#include "extra_data_types.hpp"
using namespace std;
/*
We start with some math: Suppose we append a value append(x) at some moment,
then we have +2, *5, + 7, * 20. Then the value of x now is
(((x + 2) * 5) + 7) * 20 = x * 5 * 20 + ((2) * 5 + 7) * 20.
The product 5*20 is from all multipiers appearring after x,
and ((2) * 5 + 7) * 20 is from all multipliers and addends after x.
Thus, we can use prefix sum to calculate all of these values.

Let's call Q is the products of all multipliers from the beginning,
M is the sum and products of all multipliers and addens from the beggining
and we update them each time we call addAll and mulAll.
At the momment we get append(x),
we record M and Q together with it (say M_x and Q_x).
Later on when we need to calculate the current value of x,
the formula (as we analised at the begining) is: x_now = x*Q' + M', where Q' = Q_now / Q_x and M' = M_now - M_x*Q_x.

The only trick is how to do the division of Q_now / Q_x,
which can be done by calculating the inverse of Q_x modulo 10^9 + 7,
which is Q_x^(10^9 + 5) by Fermat Little Theorem.
Indeed, to facilitate calculation,
we don't need to calculate inverse Q_x each time,
but to calculate beforehand the inverse of multipliers (which is capped at most 100),
and use them to calculate P_x = Q_x^-1.
*/
int mod97 = 1000000007;
/**
Calculates multiplicative inverse
*/
unsigned long modPow(unsigned long x, int y) {
    unsigned long tot = 1, p = x;
    for (; y; y >>= 1) {
        if (y & 1)
            tot = (tot * p) % mod97;
        p = (p * p) % mod97;
    }
    return tot;
}

class Fancy {
public:
    unsigned long seq[100001];
    unsigned int length = 0;
    unsigned long increment = 0;
    unsigned long mult = 1;

    Fancy() {
        ios_base::sync_with_stdio(false);
        cin.tie(NULL);
    }

    void append(int val) {
        seq[length++] = (((mod97 + val - increment) % mod97) * modPow(mult, mod97 - 2)) % mod97;
    }

    void addAll(int inc) {
        increment = (increment + inc % mod97) % mod97;
    }

    void multAll(int m) {
        mult = (mult * m % mod97) % mod97;
        increment = (increment * m % mod97) % mod97;
    }

    int getIndex(int idx) {
        if (idx >= length) {
            return -1;
        } else {
            return ((seq[idx] * mult) % mod97 + increment) % mod97;
        }
    }
};

/**
 * Your Fancy object will be instantiated and called as such:
 * Fancy* obj = new Fancy();
 * obj->append(val);
 * obj->addAll(inc);
 * obj->multAll(m);
 * int param_4 = obj->getIndex(idx);
 */