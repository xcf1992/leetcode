/*
634. Find the Derangement of An Array

In combinatorial mathematics,
a derangement is a permutation of the elements of a set,
such that no element appears in its original position.

There's originally an array consisting of n integers from 1 to n in ascending order,
you need to find the number of derangement it can generate.

Also, since the answer may be very large, you should return the output mod 10^9 + 7.

Example 1:
Input: 3
Output: 2
Explanation: The original array is [1,2,3]. The two derangements are [2,3,1] and [3,1,2].

Note:
n is in the range of [1, 10^6].
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
In order to find the number of derangements for nn numbers,
firstly we can consider the the original array to be [1,2,3,...,n].
Now, in order to generate the derangements of this array, assume that firstly,
we move the number 1 from its original position and place at the place of the number i.
But, now, this ith position can be chosen in n-1 ways.

Now, for placing the number i we have got two options:
We place i at the place of 1:
By doing this, the problem of finding the derangements reduces to finding the derangements of the remaining n-2 numbers,
since we've got n-2 numbers and n-2 places,
such that every number can't be placed at exactly one position.
(n - 2 elements, n - 3 positions for each element)

We don't place i at the place of 1: By doing this,
the problem of finding the derangements reduces to finding the derangements for the n-1 elements(except 1).
This is because, now we've got n-1 elements and these n-1 elements can't be placed at exactly one location
(with i not being placed at the first position).
(n - 1 elements, n - 2 positions for each element)
*/
class Solution {
public:
    int findDerangement(int n) {
        if (n == 1) {
            return 0;
        }

        if (n == 2) {
            return 1;
        }

        int mod = 1e9 + 7;
        unsigned long long minus2 = 0;
        unsigned long long minus1 = 1;
        unsigned long long result = 1;
        for (int i = 3; i <= n; i++) {
            result = (i - 1) * (minus1 + minus2) % mod;
            minus2 = minus1;
            minus1 = result;
        }
        return result;
    }
};