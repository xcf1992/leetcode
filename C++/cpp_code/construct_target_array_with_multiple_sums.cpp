/*
1354. Construct Target Array With Multiple Sums
https://leetcode.com/problems/construct-target-array-with-multiple-sums/

Given an array of integers target.
From a starting array, A consisting of all 1's,
you may perform the following procedure :

let x be the sum of all elements currently in your array.
choose index i, such that 0 <= i < target.size and set the value of A at index i to x.
You may repeat this procedure as many times as needed.
Return True if it is possible to construct the target array from A otherwise return False.

Example 1:
Input: target = [9,3,5]
Output: true
Explanation: Start with [1, 1, 1]
[1, 1, 1], sum = 3 choose index 1
[1, 3, 1], sum = 5 choose index 2
[1, 3, 5], sum = 9 choose index 0
[9, 3, 5] Done

Example 2:
Input: target = [1,1,1,2]
Output: false
Explanation: Impossible to create target array from [1,1,1,1].

Example 3:
Input: target = [8,5]
Output: true

Constraints:
N == target.length
1 <= target.length <= 5 * 10^4
1 <= target[i] <= 10^9
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
#include <map>
#include <numeric>

using namespace std;
/*
The total sum always bigger than all elements.
We can decompose the biggest number.
Each round we get the current maximum value,
delete it by the sum of other elements.

Time O(N) to build up the priority queue.
Time O(logMaxAlogN)) for the reducing value part.
We have O(maxA) loops, which is similar to gcd
Space O(N)

% operation is totally much more important than using heap.
If brute force solution is accepted,
then the solutions without % are right and good.

But the truth is that, solution without % should be TLE.
So I afraid that, without % is wrong to me.
*/
class Solution {
public:
    bool isPossible(vector<int>& target) {
        int n = target.size();
        priority_queue<int> pq(target.begin(), target.end());
        long sum = 0;
        for (int num : target) {
            sum += num;
        }

        while (true) {
            int num = pq.top();  // num should be equal to the sum of all values before replacing, rest + replaced
            pq.pop();

            sum -= num;  // now sum is equal to all values except the biggest number, rest
            if (num == 1 or sum == 1) {
                return true;
            }

            if (num < sum or sum == 0 or num % sum == 0) {
                return false;
            }

            num %= sum;  // by doing the mod we can the number get replaced
            sum += num;  // we add the value back and continue to do another round
            pq.push(num);
        }
    }
};
