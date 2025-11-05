/*
470. Implement Rand10() Using Rand7()
https://leetcode.com/problems/implement-rand10-using-rand7/

Given a function rand7 which generates a uniform random integer in the range 1 to 7,
write a function rand10 which generates a uniform random integer in the range 1 to 10.
Do NOT use system's Math.random().

Example 1:
Input: 1
Output: [7]

Example 2:
Input: 2
Output: [8,4]

Example 3:
Input: 3
Output: [8,1,10]

Note:
rand7 is predefined.
Each testcase has one argument: n, the number of times that rand10 is called.

Follow up:
What is the expected value for the number of calls to rand7() function?
Could you minimize the number of calls to rand7()?
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
using namespace std;
/*
Approach 1: Rejection Sampling
Intuition

What if you could generate a random integer in the range 1 to 49?
How would you generate a random integer in the range of 1 to 10?
What would you do if the generated number is in the desired range?
What if it is not?

Algorithm

This solution is based upon Rejection Sampling.
The main idea is when you generate a number in the desired range,
output that number immediately.
If the number is out of the desired range,
reject it and re-sample again.
As each number in the desired range has the same probability of being chosen,
a uniform distribution is produced.

Obviously, we have to run rand7() function at least twice,
as there are not enough numbers in the range of 1 to 10.
By running rand7() twice, we can get integers from 1 to 49 uniformly. Why?
    1  2  3  4  5  6  7
1 | 1  2  3  4  5  6  7
2 | 8  9 10  1  2  3  4
3 | 5  6  7  8  9 10  1
4 | 2  3  4  5  6  7  8
5 | 9 10  1  2  3  4  5
6 | 6  7  8  9 10  *  *
7 | *  *  *  *  *  *  *

rejectionSamplingTable
A table is used to illustrate the concept of rejection sampling.
Calling rand7() twice will get us row and column index that corresponds to a unique position in the table above.
Imagine that you are choosing a number randomly from the table above.
If you hit a number, you return that number immediately.
If you hit a * , you repeat the process again until you hit a number.

Since 49 is not a multiple of 10, we have to use rejection sampling.
Our desired range is integers from 1 to 40,
which we can return the answer immediately.
If not (the integer falls between 41 to 49),
we reject it and repeat the whole process again.
*/

// The rand7() API is already defined for you.
int rand7();

// @return a random integer in the range 1 to 7
class Solution {
public:
    int rand10() {
        int n;
        while (true) {
            n = 7 * (rand7() - 1) + rand7() - 1;
            if (n < 40) {
                return n % 10 + 1;
            }
        }
    }
};

/*
Idea: rand7() -> rand49() -> rand40() -> rand10()

public int rand10() {
    int result = 40;
    while (result >= 40) {result = 7 * (rand7() - 1) + (rand7() - 1);}
    return result % 10 + 1;
}

Time Complexity
The total number of iterations follows geometric distribution.
For each iteration in the while loop, the probabilty of exiting the loop is p = 40/49.
So the average time complexity T(n) = O(1/p) = O(49/40) = O(1).

Correctness
Note that rand49() generates a uniform random integer in [1, 49],
so any number in this range has the same probability to be generated.
Suppose k is an integer in range [1, 40], P(rand49() = k) = 1/49.

P(result = k)
= P(rand49() = k in the 1st iteration) +
P(rand49() > 40 in the 1st iteration) * P(rand49() = k in the 2nd iteration) +
P(rand49() > 40 in the 1st iteration) * P(rand49() > 40 in the 2nd iteration) * P(rand49() = k in the 3rd iteration) +
P(rand49() > 40 in the 1st iteration) * P(rand49() > 40 in the 2nd iteration) * P(rand49() > 40 in the 3rd iteration) * P(rand49() = k in the 4th iteration) +
...
= (1/49) + (9/49) * (1/49) + (9/49)^2 * (1/49) + (9/49)^3 * (1/49) + ...
= (1/49) * [1 + (9/49) + (9/49)^2 + (9/49)^3 + ... ]
= (1/49) * [1/(1-9/49)]
= (1/49) * (49/40)
= 1/40

Generalization
Implement randM() using randN() when M > N:
Step 1: Use randN() to generate randX(), where X >= M.
In this problem, I use 7 * (rand7() - 1) + (rand7() - 1) to generate rand49() - 1.

Step 2: Use randX() to generate randM().
In this problem, I use rand49() to generate rand40() then generate rand10.

Note: N^b * (randN() - 1) + N^(b - 1) * (randN() - 1) + N^(b - 2) * (randN() - 1) + ... + N^0 * (randN() - 1)
generates randX() - 1, where X = N^(b + 1).

More Examples
(1) Implement rand11() using rand3():

public int rand11() {
    int result = 22;
    while (result >= 22) {result = 3 * 3 * (rand3() - 1) + 3 * (rand3() - 1) + (rand3() - 1);}
    return result % 11 + 1;
}
Idea: rand3() -> rand27() -> rand22 -> rand11
Time Comlexity: O(27/22)

(2) Implement rand9() using rand7():

public int rand9() {
    int result = 45;
    while (result >= 45) {result = 7 * (rand7() - 1) + (rand7() - 1);}
    return result % 9 + 1;
}
Idea: rand7() -> rand49() -> rand45() -> rand9()
Time Comlexity: O(49/45)

(3) Implement rand13() using rand6():

public int rand13() {
    int result = 26;
    while (result >= 26) {result = 6 * (rand6() - 1) + (rand6() - 1);}
    return result % 13 + 1;
}
Idea: rand6() -> rand36() -> rand26 -> rand13()
Time Comlexity: O(36/26)
*/