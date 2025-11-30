/*
810. Chalkboard XOR Game

We are given non-negative integers nums[i] which are written on a chalkboard.
Alice and Bob take turns erasing exactly one number from the chalkboard, with Alice starting first.

If erasing a number causes the bitwise XOR of all the elements of the chalkboard to become 0,
then that player loses.
(Also, we'll say the bitwise XOR of one element is that element itself,
and the bitwise XOR of no elements is 0.)

Also, if any player starts their turn with the bitwise XOR of all the elements of the chalkboard equal to 0,
then that player wins.

Return True if and only if Alice wins the game,
assuming both players play optimally.

Example:
Input: nums = [1, 1, 2]
Output: false
Explanation:
Alice has two choices: erase 1 or erase 2.
If she erases 1, the nums array becomes [1, 2].
The bitwise XOR of all the elements of the chalkboard is 1 XOR 2 = 3.
Now Bob can remove any element he wants,
because Alice will be the one to erase the last element and she will lose.
If Alice erases 2 first, now nums becomes [1, 1].
The bitwise XOR of all the elements of the chalkboard is 1 XOR 1 = 0. Alice will lose.

Notes:
1 <= N <= 1000.
0 <= nums[i] <= 2^16.
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
As in the problem statement, if the XOR of the entire array is 0, then Alice wins.

result = X1 ^ X2 ^ X3 ... ^ Xn
if result == 0:
then Alice wins directly

If result != 0 and length is even:
then Alice wins, as there will be at least 2 different numbers left.

Similarly, if there are an odd number of elements,
then Bob always faces an even number of elements, and has a move.
So the answer is just the parity of the number of elements in the array.

Those that are familiar with the Sprague-Grundy theorem may know that this game is a misère-form game,
meaning the theorem does not apply,
and giving a big hint that there may exist a simpler solution.
*/
class Solution {
public:
    bool xorGame(vector<int>& nums) {
        int result = 0;
        for (int num : nums) {
            result ^= num;
        }
        return result == 0 or nums.size() % 2 == 0;
    }
};