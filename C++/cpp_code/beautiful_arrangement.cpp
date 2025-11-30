/*
526. Beautiful Arrangement

Suppose you have N integers from 1 to N.
We define a beautiful arrangement as an array that is constructed by these N numbers successfully
if one of the following is true for the ith position (1 <= i <= N) in this array:

1. The number at the ith position is divisible by i.
2. i is divisible by the number at the ith position.

Now given N, how many beautiful arrangements can you construct?

Example 1:

Input: 2
Output: 2
Explanation:

The first beautiful arrangement is [1, 2]:

Number at the 1st position (i=1) is 1, and 1 is divisible by i (i=1).

Number at the 2nd position (i=2) is 2, and 2 is divisible by i (i=2).

The second beautiful arrangement is [2, 1]:

Number at the 1st position (i=1) is 2, and 2 is divisible by i (i=1).

Number at the 2nd position (i=2) is 1, and i (i=2) is divisible by 1.


Note:

N is a positive integer and will not exceed 15.
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
#include <climits>
using namespace std;
/*
The idea behind this approach is simple. We try to create all the permutations of numbers from 1 to N.
We can fix one number at a particular position and check for the divisibility criteria of that number at the particular
position. But, we need to keep a track of the numbers which have already been considered earlier so that they aren't
reconsidered while generating the permutations. If the current number doesn't satisfy the divisibility criteria, we can
leave all the permutations that can be generated with that number at the particular position. This helps to prune the
search space of the permutations to a great extent. We do so by trying to place each of the numbers at each position.

We make use of a visited array of size N.
Here, visited[i] refers to the ith number being already placed/not
placed in the array being formed till now(True indicates that the number has already been placed).

We make use of a calculate function, which puts all the numbers pending numbers from 1 to N
(i.e. not placed till now in the array), indicated by a FalseFalse at the corresponding visited[i]visited[i] position,
and tries to create all the permutations with those numbers starting from the pospos index onwards in the current array.
While putting the pos^{th} number, we check whether the i^{th} number satisfies the divisibility criteria on the go
i.e. we continue forward with creating the permutations with the number ii at the pos^{th} position
only if the number ii and pospos satisfy the given criteria.
Otherwise, we continue with putting the next numbers at the same position and keep on generating the permutations.
*/
class Solution {
private:
    void count(vector<int>& numbers, int pos, int n, int& result) {
        if (pos > n) {
            result += 1;
            return;
        }

        for (int i = 1; i <= n; i++) {
            if (numbers[i] == 1 and (i % pos == 0 or pos % i == 0)) {
                numbers[i] = 0;
                count(numbers, pos + 1, n, result);
                numbers[i] = 1;
            }
        }
    }

public:
    int countArrangement(int N) {
        vector<int> numbers(N + 1, 1);
        int result = 0;
        count(numbers, 1, N, result);
        return result;
    }
};