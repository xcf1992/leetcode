/*
390. Elimination Game
https://leetcode.com/problems/elimination-game/

There is a list of sorted integers from 1 to n.
Starting from left to right,
remove the first number and every other number afterward until you reach the end of the list.

Repeat the previous step again,
but this time from right to left,
remove the right most number and every other number from the remaining numbers.

We keep repeating the steps again,
alternating left to right and right to left,
until a single number remains.

Find the last number that remains starting with a list of length n.

Example:
Input:
n = 9,
1 2 3 4 5 6 7 8 9
2 4 6 8
2 6
6
Output:
6
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

class Solution {
public:
    int lastRemaining(int n) {
        int head = 1;
        bool moveForward = true;
        int remain = n;
        int step = 2;
        while (remain > 1) {
            if (moveForward or remain %2 == 1
            )
            {
                head += step / 2;
            }
            remain /= 2;
            step *= 2;
            moveForward = !moveForward;
        }
        return head;
    }
};