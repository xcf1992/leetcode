/*
528. Random Pick with Weight
https://leetcode.com/problems/random-pick-with-weight/

Given an array w of positive integers,
where w[i] describes the weight of index i,
write a function pickIndex which randomly picks an index in proportion to its weight.

Note:
1 <= w.length <= 10000
1 <= w[i] <= 10^5
pickIndex will be called at most 10000 times.

Example 1:
Input:
["Solution","pickIndex"]
[[[1]],[]]
Output: [null,0]

Example 2:
Input:
["Solution","pickIndex","pickIndex","pickIndex","pickIndex","pickIndex"]
[[[1,3]],[],[],[],[],[]]
Output: [null,0,1,1,1,0]
Explanation of Input Syntax:

The input is two lists:
the subroutines called and their arguments.
Solution's constructor has one argument,
the array w. pickIndex has no arguments.
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
First I want to explain the question a little bit,
an example would be helpful to understand:

e.g. w: [1,2,3,4] ,
so the total weight of this w array will be 1 + 2 + 3 + 4 = 10
then the probability(proportion of its weight) of each index would be 0: 1/10, 1: 2/10, 3: 3/10, 4: 4/10

If space complexity is not a problem,
then we can create a new array to store index by its frequency like this:
still use my previous example, [0, 1, 1, 2, 2, 2, 3, 3, 3, 3],
then generate a random number for 0 to its length.
This approach takes lots of space : O(N) here N equals sum of w, but pickIndex takes O(1) time
*/
class Solution {
private:
    vector<int> preSum;
public:

    Solution(vector<int> w) {
        partial_sum(w.begin(), w.end(), back_inserter(preSum));
        srand(time(nullptr));
    }

    int pickIndex() {
        int val = rand() % preSum.back();
        auto it = upper_bound(preSum.begin(), preSum.end(), val);
        return it - preSum.begin();
    }
};
/*
* Your Solution object will be instantiated and called as such:
* Solution obj = new Solution(w);
* int param_1 = obj.pickIndex();
*/
