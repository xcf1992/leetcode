/*
1147. Longest Chunked Palindrome Decomposition
Return the largest possible k such that there exists a_1, a_2, ..., a_k such that:

Each a_i is a non-empty string;
Their concatenation a_1 + a_2 + ... + a_k is equal to text;
For all 1 <= i <= k,  a_i = a_{k+1 - i}.


Example 1:

Input: text = "ghiabcdefhelloadamhelloabcdefghi"
Output: 7
Explanation: We can split the string on "(ghi)(abcdef)(hello)(adam)(hello)(abcdef)(ghi)".
Example 2:

Input: text = "merchant"
Output: 1
Explanation: We can split the string on "(merchant)".
Example 3:

Input: text = "antaprezatepzapreanta"
Output: 11
Explanation: We can split the string on "(a)(nt)(a)(pre)(za)(tpe)(za)(pre)(a)(nt)(a)".
Example 4:

Input: text = "aaa"
Output: 3
Explanation: We can split the string on "(a)(a)(a)".


Constraints:

text consists only of lowercase English characters.
1 <= text.length <= 1000
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
using namespace std;

/*
https://leetcode.com/problems/longest-chunked-palindrome-decomposition/discuss/350560/JavaC%2B%2BPython-Easy-Greedy-with-Prove

Intuition
Honestly I wrote a DP solution first, to ensure it get accepted.
Then I realized greedy solution is right.

Give a quick prove here.
If we have long prefix matched and a shorter prefix matched at the same time.
The longer prefix can always be divided in to smaller part.

image

Assume we have a longer blue matched and a shorter red matched.
As definition of the statement, we have B1 = B2, R1 = R4.

Because B1 = B2,
the end part of B1 = the end part of B2,
equal to R2 = R4,
So we have R1 = R4 = R2.

B is in a pattern of R + middle part + R.
Instead take a longer B with 1 point,
we can cut it in to 3 parts to gain more points.

This proves that greedily take shorter matched it right.
Note that the above diagram shows cases when shorter length <= longer length/ 2
When shorter length > longer length/ 2, this conclusion is still correct.


To be more general,
the longer prefix and shorter prefix will alway be in these patter:

longer = a + ab * N
shorter = a + ab * (N - 1)

for example:
longer = "abc" + "def" + "abc"
shorter = "abc"

for example:
longer = "abc" * M
shorter = "abc" * N
where M > N
*/
class Solution {  // greedy
public:
    int longestDecomposition(string text) {
        int n = text.size();
        if (n <= 1) {
            return n;
        }

        int result = 0;
        string left = "";
        string right = "";
        for (int i = 0; i < n; ++i) {
            left.push_back(text[i]);
            right = text[n - i - 1] + right;
            if (left == right) {
                result += 1;
                left = "";
                right = "";
            }
        }
        return result;
    }
};

class Solution1 {  // dfs with memo 17.73%
private:
    unordered_map<string, int> memo;

public:
    int longestDecomposition(string text) {
        int n = text.size();
        if (n <= 1) {
            return n;
        }

        if (memo.find(text) != memo.end()) {
            return memo[text];
        }

        memo[text] = 1;
        for (int len = 1; len <= n / 2; ++len)
            if (text.substr(0, len) == text.substr(n - len, len)) {
                memo[text] = max(memo[text], 2 + longestDecomposition(text.substr(len, n - len * 2)));
            }
        return memo[text];
    }
};
