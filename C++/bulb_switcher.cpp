/*
319. Bulb Switcher

There are n bulbs that are initially off.
You first turn on all the bulbs.
Then, you turn off every second bulb.
On the third round, you toggle every third bulb
(turning on if it's off or turning off if it's on).
For the i-th round, you toggle every i bulb.
For the n-th round, you only toggle the last bulb.
Find how many bulbs are on after n rounds.

Example:

Input: 3
Output: 1
Explanation:
At first, the three bulbs are [off, off, off].
After first round, the three bulbs are [on, on, on].
After second round, the three bulbs are [on, off, on].
After third round, the three bulbs are [on, off, off].

So you should return 1, because there is only one bulb is on.
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
Explanation:
A light will be toggled only during the round of its factors, e.g. number 6 light will be toggled at 1,2,3,6
and light 12 will be toggled at 1,2,3,4,6,12.
The final state of a light is on and off only depends on if the number of its factor is odd or even.
If odd, the light is on and if even the light is off.
The number of one number's factor is odd if and only if it is a perfect square!
So we will only need to loop to find all the perfect squares that are smaller than n
And the process can be looked as all the bulbs are off at the beginning,
Then you toggle every 1 bulb
Then toggle every 2 bulb
...
Then final result is actully sqrt(n)
*/
class Solution {
public:
    int bulbSwitch(int n) {
        int counts = 0;
        for (int i = 1; i * i <= n; ++i) {
            counts += 1;
        }
        return counts;
    }
};
