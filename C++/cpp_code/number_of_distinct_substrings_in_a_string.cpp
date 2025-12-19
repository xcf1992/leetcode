/*
https://leetcode.com/problems/number-of-distinct-substrings-in-a-string/description/
1698. Number of Distinct Substrings in a String

Given a string s, return the number of distinct substrings of s.

A substring of a string is obtained by deleting any number of characters (possibly zero) from the front of the string
and any number (possibly zero) from the back of the string.



Example 1:

Input: s = "aabbaba"
Output: 21
Explanation: The set of distinct strings is
["a","b","aa","bb","ab","ba","aab","abb","bab","bba","aba","aabb","abba","bbab","baba","aabba","abbab","bbaba","aabbab","abbaba","aabbaba"]
Example 2:

Input: s = "abcdefg"
Output: 28


Constraints:

1 <= s.length <= 500
s consists of lowercase English letters.


Follow up: Can you solve this problem in O(n) time complexity?
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
#include <climits>
#include <set>

using namespace std;
/*
Intuition: any two string with different sizes are distinct. In order to boost the performance, we can process strings
of size n independently of strings of any other size.

Now, we can roll the window of size n and de-dup string using a hash map. Calculating a hash for a string is
proportional to the string size. So, the second optimization is to use a rolling hash so it takes a constant time.
Beware of the collisions; here, the fact that we are only de-dup strings with the same size reduces the collision
probability.

The final optimization is to re-use rolling hash for s[0, n -1) to calculate the starting hash (s_hash) for s[0, n).
 */
class Solution {
private:
    long mod = 1000000009;
public:
    int countDistinct(string s) {
        long rst = 1, s_hash = 0, base = 1;
        for (auto i = 0; i + 1 < s.size(); ++i) {
            s_hash = (s_hash * 26 + s[i]) % mod;
            base = base * 26 % mod;
            unordered_set<int> us{(int)s_hash};
            for (long j = i + 1, hash = s_hash; j < s.size(); ++j) {
                hash = (mod + hash * 26 + s[j] - base * s[j - i - 1] % mod) % mod;
                us.insert((int)hash);
            }
            rst += us.size();
        }
        return rst;
    }
};
