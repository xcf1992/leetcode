/*
519. Random Flip Matrix
You are given the number of rows n_rows and number of columns n_cols
of a 2D binary matrix where all values are initially 0.
Write a function flip which chooses a 0 value uniformly at random,
changes it to 1,
and then returns the position [row.id, col.id] of that value.
Also, write a function reset which sets all values back to 0.
Try to minimize the number of calls to system's Math.random() and optimize the time and space complexity.

Note:

1 <= n_rows, n_cols <= 10000
0 <= row.id < n_rows and 0 <= col.id < n_cols
flip will not be called when the matrix has no 0 values left.
the total number of calls to flip and reset will not exceed 1000.
Example 1:

Input:
["Solution","flip","flip","flip","flip"]
[[2,3],[],[],[],[]]
Output: [null,[0,1],[1,2],[1,0],[1,1]]
Example 2:

Input:
["Solution","flip","flip","reset","flip"]
[[1,2],[],[],[],[]]
Output: [null,[0,0],[0,1],null,[0,0]]

Explanation of Input Syntax:
The input is two lists: the subroutines called and their arguments.
Solution's constructor has two arguments, n_rows and n_cols.
flip and reset have no arguments.
Arguments are always wrapped with a list, even if there aren't any.
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
#include <numeric>
using namespace std;
/*
Reservoir sampling
Imagine you have an array of length n with the i-th element being i.
In reservoir sampling, you keep track of the number of elements left l.
In each get_next() call,
l is first decremented and a random integer r is chosen in the range of [0, l] (inclusive),
then you want to exchange the r-th value with the l-th value and return the l-th value after the exchange.
In this way all the elements will be popped once and will have equal probability of being chosen.
Then you'll just have to map the 1d array to a 2d matrix and you are done.

I structured code in the same way so readers can better understand the situation.

Time complexity O(1) each call. 1 random call per flip.
*/
class Solution {
private:
    unordered_map<int, int> pos;
    int m;
    int n;
    int total;
public:
    Solution(int n_rows, int n_cols) {
        m = n_rows;
        n = n_cols;
        reset();
        srand(NULL);
    }

    vector<int> flip() {
        int pick = rand() % total;
        total -= 1;

        int index = pos.find(pick) != pos.end() ? pos[pick] : pick;
        int last = pos.find(total) != pos.end() ? pos[total] : total;
        pos[pick] = last;
        return {index / n, index % n};
    }

    void reset() {
        total = m * n;
        pos.clear();
    }
};
/**
* Your Solution object will be instantiated and called as such:
* Solution obj = new Solution(n_rows, n_cols);
* vector<int> param_1 = obj.flip();
* obj.reset();
*/
