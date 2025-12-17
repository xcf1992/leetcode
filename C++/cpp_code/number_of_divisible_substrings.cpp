/*
https://leetcode.com/problems/number-of-divisible-substrings/description/
2950. Number of Divisible Substrings

Each character of the English alphabet has been mapped to a digit as shown below.
1       2       3
ab      cde     fgh

4       5       6
ijk     lmn     opq

7       8       9
rst     uvw     xyz


A string is divisible if the sum of the mapped values of its characters is divisible by its length.

Given a string s, return the number of divisible substrings of s.

A substring is a contiguous non-empty sequence of characters within a string.



Example 1:

Substring	Mapped	Sum	Length	Divisible?
a	1	1	1	Yes
s	7	7	1	Yes
d	2	2	1	Yes
f	3	3	1	Yes
as	1, 7	8	2	Yes
sd	7, 2	9	2	No
df	2, 3	5	2	No
asd	1, 7, 2	10	3	No
sdf	7, 2, 3	12	3	Yes
asdf	1, 7, 2, 3	13	4	No
Input: word = "asdf"
Output: 6
Explanation: The table above contains the details about every substring of word, and we can see that 6 of them are
divisible. Example 2:

Input: word = "bdh"
Output: 4
Explanation: The 4 divisible substrings are: "b", "d", "h", "bdh".
It can be shown that there are no other substrings of word that are divisible.
Example 3:

Input: word = "abcd"
Output: 6
Explanation: The 6 divisible substrings are: "a", "b", "c", "d", "ab", "cd".
It can be shown that there are no other substrings of word that are divisible.


Constraints:

1 <= word.length <= 2000
word consists only of lowercase English letters.
*/
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <unordered_set>
#include <algorithm>
#include <cmath>
#include <queue>
#include <stack>
#include <climits>
#include <set>
using namespace std;

/*
Intuition
For a substring, if we map characters into the numbers, say f(c) = x (x = 1, 2, ... 9),
the question is to ask
(f(c1) + f(c2) + f(c3) + ... + f(cp)) / p is an integer.
Meaning the average value is an integer.
So the average value can only be integers inside [1, 9].
Suppose the average value is a.

So we have
(f(c1) + f(c2) + f(c3) + ... + f(cp)) / p = a
f(c1) + f(c2) + f(c3) + ... + f(cp) = p * a
f(c1) + f(c2) + f(c3) + ... + f(cp)) - p * a = 0
(f(c1) - a) + (f(c2) - a) + ... + (f(cp) - a) = 0
So if we enumerate all the possible a values, subtracting it from. the original value and the sum should be 0. This is a
very common trick to do with questions related to average value. (Sometimes we can do binary search on the average
value.)

Approach
Try all the possible average value a from 1 to 9.
Subtract each character value by a.
Find the number of substrings/subarrays with sum 0 which can be done via prefix sum.
Complexity
Time complexity:
O(9 * n)

Space complexity:
O(n)
 */
class Solution {
public:
    int countDivisibleSubstrings(string word) {
        vector<int> num_mapping({1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5, 5, 6, 6, 6, 7, 7, 7, 8, 8, 8, 9, 9, 9});
        int rst = 0;
        for (int num = 1; num <= 9; num ++) {
            unordered_map<int, int> cnt = {{0, 1}};
            int sum = 0;
            for (char c : word) {
                sum += num_mapping[c - 'a'] - num;
                if (cnt.find(sum) != cnt.end()) {
                    rst += cnt[sum];
                } else {
                    cnt[sum] = 0;
                }
                cnt[sum] += 1;
            }
        }
        return rst;
    }
};
