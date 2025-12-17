/*
https://leetcode.com/problems/count-beautiful-substrings-ii/description/
2949. Count Beautiful Substrings II

You are given a string s and a positive integer k.

Let vowels and consonants be the number of vowels and consonants in a string.

A string is beautiful if:

vowels == consonants.
(vowels * consonants) % k == 0, in other terms the multiplication of vowels and consonants is divisible by k.
Return the number of non-empty beautiful substrings in the given string s.

A substring is a contiguous sequence of characters in a string.

Vowel letters in English are 'a', 'e', 'i', 'o', and 'u'.

Consonant letters in English are every letter except vowels.



Example 1:

Input: s = "baeyh", k = 2
Output: 2
Explanation: There are 2 beautiful substrings in the given string.
- Substring "baeyh", vowels = 2 (["a",e"]), consonants = 2 (["y","h"]).
You can see that string "aeyh" is beautiful as vowels == consonants and vowels * consonants % k == 0.
- Substring "baeyh", vowels = 2 (["a",e"]), consonants = 2 (["b","y"]).
You can see that string "baey" is beautiful as vowels == consonants and vowels * consonants % k == 0.
It can be shown that there are only 2 beautiful substrings in the given string.
Example 2:

Input: s = "abba", k = 1
Output: 3
Explanation: There are 3 beautiful substrings in the given string.
- Substring "abba", vowels = 1 (["a"]), consonants = 1 (["b"]).
- Substring "abba", vowels = 1 (["a"]), consonants = 1 (["b"]).
- Substring "abba", vowels = 2 (["a","a"]), consonants = 2 (["b","b"]).
It can be shown that there are only 3 beautiful substrings in the given string.
Example 3:

Input: s = "bcdf", k = 1
Output: 0
Explanation: There are no beautiful substrings in the given string.


Constraints:

1 <= s.length <= 5 * 104
1 <= k <= 1000
s consists of only English lowercase letters.
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
Need to know
If we only have the condition vowels == consonants,
we can count the difference between vowels and consonants in prefix substring,
and count the count in a hashmap,
to find out the number of substring with diff 0.

Explanation
In this problem, we have one more constrain of
(vowels * consonants) % k == 0.
Assume the length is l and vowels == consonants,
so (l / 2) * (l / 2) k == 0,
so l * l % (k * 4) == 0.

We only need to find out the smallest l satifying the above equation,
and only need to consider the substring with length l, 2l, 3l ...
In additional to the solution in "need to know" section,
we count the index in bucket with different module of l.


Complexity(
Time O(n + k)
Space O(n + k)

Both can improve to O(n + sqrt(k)).
 */
class Solution {
public:
    long long beautifulSubstrings(string s, int k) {
        set<char> vowels = {'a', 'e', 'i', 'o', 'u'};

        int v = 0;
        int l = 1;
        while (l * l % (k * 4) > 0) {
            l += 1;
        }

        int n = s.size();
        vector<unordered_map<int, int>> seen(l);
        seen[l - 1][0] = 1;
        long long res = 0;
        for (int i = 0; i < n; i++) {
            v += vowels.find(s[i]) != vowels.end() ? 1 : -1;
            res += seen[i % l][v]++;
        }
        return res;
    }
};

class Solution {
public:
#define ll long long

    bool isvowel(char ch) {
        return ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u';
    }

    ll beautifulSubstrings(string s, int k) {
        ll vowel_cnt = 0, consonant_cnt = 0, rst = 0;
        unordered_map<ll, unordered_map<ll, ll>> freq;
        freq[0][0] = 1;

        for (char ch : s) {
            ++(isvowel(ch) ? vowel_cnt : consonant_cnt);
            for (auto& [z, count] : freq[vowel_cnt - consonant_cnt])
                if ((vowel_cnt - z) * (vowel_cnt - z) % k == 0)
                    rst += count;

            freq[vowel_cnt - consonant_cnt][vowel_cnt % k] += 1;
        }

        return rst;
    }
};