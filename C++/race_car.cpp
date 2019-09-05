/*
 818. Race Car
 Your car starts at position 0 and speed +1 on an infinite number line.
 (Your car can go into negative positions.)

 Your car drives automatically according to a sequence of instructions A (accelerate) and R (reverse).

 When you get an instruction "A", your car does the following:
 position += speed, speed *= 2.

 When you get an instruction "R", your car does the following:
 if your speed is positive then speed = -1 , otherwise speed = 1.  (Your position stays the same.)

 For example, after commands "AAR", your car goes to positions 0->1->3->3, and your speed goes to 1->2->4->-1.

 Now for some target position, say the length of the shortest sequence of instructions to get there.

 Example 1:
 Input:
 target = 3
 Output: 2
 Explanation:
 The shortest instruction sequence is "AA".
 Your position goes from 0->1->3.
 Example 2:
 Input:
 target = 6
 Output: 5
 Explanation:
 The shortest instruction sequence is "AAARA".
 Your position goes from 0->1->3->7->7->6.


 Note:

 1 <= target <= 10000.
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
#include <map>
#include <numeric>
using namespace std;

/*
 Dynamic Programming
 Consider two general cases for number i with bit_length n.

 i == 2^n-1, this case, n is the best way
 2 ^ (n - 1) - 1 < i < 2^n - 1, there are two ways to arrive at i:
 Use n A to arrive at 2^n - 1 first, then use R to change the direction,
 by here there are n+1 operations (n A and one R), then the remaining is same as dp[2^n-1-i]

 Use n-1 A to arrive at 2^(n-1)-1 first,
 then R to change the direction,
 use m A to go backward,
 then use R to change the direction again to move forward,
 by here there are n-1+2+m=n+m+1 operations (n-1 A, two R, m A),
 current position is 2^(n-1)-1 - (2^m-1) = 2^(n-1)-2^m,
 the remaining operations is same as dp[i-(2^(n-1)-1)+(2^m-1)]=dp[i-2^(n-1)+2^m)].

 Why dp in this way?
 I first think the dp way should be:
 dp[i] = min(n+1+dp[2^n-1-i], n-1+2+dp[i-2^(n-1)+1])
 But it's wrong, look at the (n-1) A case, we do A for (n-1) times, then do two R,
 then the situation is the same as dp[i-2^(n-1)+1].
 This can be larger than the actual min operations since, there may be redundant R operations,
 we can combine RR operation with the remaining (2^(n-1)-1) to i path.
 So we use m to go backward between the two R operations and count the remaining (2^(n-1)-2^m) to i path to include the combining situation.

 For example:

 target = 5

 The right answer should be AARARAA, positions: 0, 1, 3, 3, 2, 2, 3, 5
 But if we use the above formula, the answer is AA (0->3) RR (make speed at 1 again) AARA (3->5)

 We can move the last A to the middle of RR, so that we save an operation. That's where the combine can happen.
 So we do dp by adding m A between the RR and add the # operations for remaining distance.

 If you have better explanation, please let me know. Thanks.
*/
class Solution {
public:
    int racecar(int target) {
        vector<int> dp(target + 1, 0);
        for (int i = 1; i <= target; i++) {
            int n = floor(log2(i)) + 1;
            if (i == pow(2, n) - 1) {
                dp[i] = n;
                continue;
            }
            dp[i] = n + 1 + dp[pow(2, n) - 1 - i];
            for (int m = 0; m < n - 1; m++) {
                dp[i] = min(dp[i], n - 1 + 1 + m + 1 + dp[i - pow(2, n - 1) + pow(2, m)]);
            }
        }
        return dp[target];
    }
};

/*
 BFS and pruning and memory states
 too slow beat 11.03%
 932 ms
*/
class Solution1 {
public:
    int racecar(int target) {
        unordered_set<string> memo;
        queue<vector<int>> bfs; // {curPos, speed}
        bfs.push({0, 1});
        memo.insert("0_1");
        int result = 0;
        while (!bfs.empty()) {
            int curSize = bfs.size();
            for (int i = 0; i < curSize; i++) {
                int curPos = bfs.front()[0];
                int curSpeed = bfs.front()[1];
                bfs.pop();

                if (curPos == target) {
                    return result;
                }

                if (abs(target - curPos) > target) {
                    continue;
                }

                int newPos = curPos + curSpeed;
                int newSpeed = curSpeed * 2;
                string key = to_string(newPos) + "_" + to_string(newSpeed);
                if (memo.find(key) == memo.end()) {
                    bfs.push({newPos, newSpeed});
                    memo.insert(key);
                }

                newSpeed = -1 * curSpeed / abs(curSpeed);
                key = to_string(curPos) + "_" + to_string(newSpeed);
                if (memo.find(key) == memo.end()) {
                    bfs.push({curPos, newSpeed});
                    memo.insert(key);
                }
            }
            result += 1;
        }
        return result;
    }
};
