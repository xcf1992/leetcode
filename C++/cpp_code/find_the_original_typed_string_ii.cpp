/*
https://leetcode.com/problems/find-the-original-typed-string-ii/description/
3333. Find the Original Typed String II
Alice is attempting to type a specific string on her computer.
However, she tends to be clumsy and may press a key for too long, resulting in a character being typed multiple times.

You are given a string word, which represents the final output displayed on Alice's screen.
You are also given a positive integer k.

Return the total number of possible original strings that Alice might have intended to type,
if she was trying to type a string of size at least k.

Since the answer may be very large, return it modulo 109 + 7.

Example 1:
Input: word = "aabbccdd", k = 7
Output: 5
Explanation:
The possible strings are: "aabbccdd", "aabbccd", "aabbcdd", "aabccdd", and "abbccdd".

Example 2:
Input: word = "aabbccdd", k = 8
Output: 1
Explanation:
The only possible string is "aabbccdd".

Example 3:
Input: word = "aaabbb", k = 3
Output: 8

Constraints:
1 <= word.length <= 5 * 105
word consists only of lowercase English letters.
1 <= k <= 2000
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

class Solution {
private:
    static const int MOD = 1e9 + 7;
public:
    int possibleStringCount(string word, int k) {
        size_t n = word.size();
        if (n == 0) {
            return 0;
        }

        vector<int> group;
        int cnt = 1;
        for (size_t i = 1; i < n; i++) {
            if (word[i - 1] == word[i]) {
                cnt += 1;
                continue;
            }

            group.push_back(cnt);
            cnt = 1;
        }
        group.push_back(cnt);

        long long total = 1;
        for (int num : group) {
            total = (total * num) % MOD;
        }
        if (k <= group.size()) {
            return total;
        }

        vector<int> dp(k, 0);
        dp[0] = 1;
        for (int num : group) {
            vector<int> temp(k, 0);
            long long sum = 0;
            for (int i = 0; i < k; i++) {
                if (i > 0) {
                    sum = (sum + dp[i - 1]) % MOD;
                }
                if (i >= num - 1) {
                    sum = (sum - dp[i - num - 1] + MOD) % MOD;
                }
                temp[i] = sum;
            }

            dp = temp;
        }

        long long invalid = 0;
        for (int i = group.size(); i < k; i++) {
            invalid = (invalid + dp[i]) % MOD;
        }
        return (total - invalid + MOD) % MOD;
    }
};

/*
https://leetcode.com/problems/find-the-original-typed-string-ii/solutions/6912996/leetcode-3333-dp-prefix-sum-a-more-detai-lnwj/
*Alice is trying to type a string, but she might press keys for too long, resulting in repeated characters.Given the final string she typed (word) and a minimum length k, we need to find how many possible original strings she could have intended to type, where the original string's length is at least k.The original string is formed by possibly reducing consecutive repeated characters in word tofewer repetitions (but at least one).

🤔 Approach
Group Consecutive Characters:

Traverse the string and group consecutive identical characters, storing their counts in a list groups.
Calculate Total Possible Original Strings:

The total number of possible original strings is the product of the counts in groups because for each group, we can choose any number from 1 to its count.
Check if Original Strings are Automatically Valid:

If the number of groups is at least k, every original string formed will have at least k characters (since each group contributes at least one character). Thus, the answer is the total number of possible original strings.
4. Dynamic Programming to Count Valid Original Strings:

If the number of groups is less than k, we need to count how many original strings have a sum of chosen counts that is at least k.

Use dynamic programming where dp[s] represents the number of ways to achieve a sum s of chosen counts.

Initialize dp[0] = 1 (one way to have sum 0).

For each group, update the DP array to include new sums by choosing between 1 and the group’s count.

After processing all groups, sum the DP values for sums from groups.size() to k-1 to find invalid strings (sum less than k).

Subtract the invalid count from the total to get the number of valid original strings.

Final Calculation:

The result is (total - invalid) % MOD, ensuring it’s non-negative by adding MOD before taking modulo.

Explanation
https://leetcode.com/problems/find-the-original-typed-string-ii/solutions/6908532/beginner-freindly-java-c-python/
Grouping Characters: The string is scanned to group consecutive identical characters, storing their counts in groups.

Total Original Strings: The product of counts in groups gives the total possible original strings.

Early Termination: If the number of groups is at least k, all original strings are valid, so return the total.

Dynamic Programming Setup: Initialize a DP array to count ways to achieve sums of chosen counts.

DP Update: For each group, update the DP array to reflect new sums achievable by choosing 1 to num characters from the group.

Invalid Counts: Sum the DP values for sums less than k to find invalid original strings.

Result Calculation: Subtract invalid counts from the total and return the result modulo MOD.

Example Walkthrough 🚶‍♂️
Input String (word): "aaabbc"
Minimum Length (k): 4
Step-by-Step Execution:
Group Consecutive Characters:

Traverse the string and group identical consecutive characters:
'aaa' → count = 3
'bb' → count = 2
'c' → count = 1
Groups: [3, 2, 1]
Calculate Total Possible Original Strings:

Total = product of all group counts = 3 * 2 * 1 = 6
Total Possible Original Strings: 6
Check if Original Strings are Automatically Valid:

Number of groups (m) = 3
Given k = 4, since 3 < 4, we need to proceed with dynamic programming to count valid strings.
Dynamic Programming to Count Valid Original Strings:

Initialize dp array of size k = 4:

dp = [1, 0, 0, 0] (since dp[0] = 1)
Process each group:

Group 1 (count = 3):

Update dp to include sums from 1 to 3:
newDp = [0, 1, 1, 1]
Group 2 (count = 2):

Update dp to include sums from 1 to 2:
newDp = [0, 0, 1, 2]
Group 3 (count = 1):

Update dp to include sum of 1:

newDp = [0, 0, 0, 1]

Final dp: [0, 0, 0, 1]
Calculate Valid Original Strings:
valid = total - invalid = 6 - 1 = 5
Since valid cannot be negative, we add MOD (though not needed here):
valid = (6 - 1 + MOD) % MOD = 5
 */