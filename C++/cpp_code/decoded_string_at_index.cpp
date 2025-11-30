/*
880. Decoded String at Index
An encoded string S is given.  To find and write the decoded string to a tape,
the encoded string is read one character at a time and the following steps are taken:

If the character read is a letter, that letter is written onto the tape.
If the character read is a digit (say d), the entire current tape is repeatedly written d-1 more times in total.
Now for some encoded string S, and an index K, find and return the K-th letter (1 indexed) in the decoded string.

Example 1:

Input: S = "leet2code3", K = 10
Output: "o"
Explanation:
The decoded string is "leetleetcodeleetleetcodeleetleetcode".
The 10th letter in the string is "o".
Example 2:

Input: S = "ha22", K = 5
Output: "h"
Explanation:
The decoded string is "hahahaha".  The 5th letter is "h".
Example 3:

Input: S = "a2345678999999999999999", K = 1
Output: "a"
Explanation:
The decoded string is "a" repeated 8301530446056247680 times.  The 1st letter is "a".


Note:

2 <= S.length <= 100
S will only contain lowercase letters and digits 2 through 9.
S starts with a letter.
1 <= K <= 10^9
The decoded string is guaranteed to have less than 2^63 letters.
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
#include <numeric>
using namespace std;
/*
We decode the string and N keeps the length of decoded string, until N >= K.
Then we go back from the decoding position.
If it's S[i] = d is a digit, then N = N / d before repeat and K = K % N is what we want.
If it's S[i] = c is a character, we return c if K == 0 or K == N
*/

/*
Intuition

If we have a decoded string like appleappleappleappleappleapple and an index like K = 24,
the answer is the same if K = 4.

In general, when a decoded string is equal to some word with size length repeated some number of times
(such as apple with size = 5 repeated 6 times), the answer is the same for the index K as it is for the index K % size.

We can use this insight by working backwards, keeping track of the size of the decoded string.
Whenever the decoded string would equal some word repeated d times, we can reduce K to K % (word.length).

Algorithm

First, find the length of the decoded string.
After, we'll work backwards, keeping track of size:
the length of the decoded string after parsing symbols S[0], S[1], ..., S[i].

If we see a digit S[i],
it means the size of the decoded string after parsing S[0], S[1], ..., S[i-1] will be size / Integer(S[i]).
Otherwise, it will be size - 1.
*/
// cause the length of expaned string will be
// a3 * (a2 * (a1 * b0 + b1) + b2) + b3.......
// so we need to check
// if K is in the b3 part, with len -= 1, K % len will equal to 0 after several decrease
// if K is in a2 part then after len / a3, we can get the pos
class Solution {
public:
    string decodeAtIndex(string S, int K) {
        long len = 0;
        int n = S.size();
        for (int i = 0; i < n; ++i) {
            if (isdigit(S[i])) {
                len *= S[i] - '0';
            } else {
                len += 1;
            }
        }

        string result = "";
        for (int i = n - 1; i >= 0; --i) {
            K %= len;
            if (K == 0 and isalpha(S[i])) {
                result = string(1, S[i]);
                break;
            }
            if (isdigit(S[i])) {
                len /= S[i] - '0';
            } else {
                len -= 1;
                ;
            }
        }
        return result;
    }
};

class Solution1 {
public:
    string decodeAtIndex(string S, int K) {
        long N = 0, i;
        for (i = 0; N < K; ++i)
            N = isdigit(S[i]) ? N * (S[i] - '0') : N + 1;
        while (i--)
            if (isdigit(S[i]))
                N /= S[i] - '0', K %= N;
            else if (K % N-- == 0)
                return string(1, S[i]);
        return "lee215";
    }
};

class Solution2 {
public:
    string decodeAtIndex(string S, int K) {
        string decoded = "";
        for (char c : S) {
            if (decoded.size() >= K) {
                break;
            }
            if (isalpha(c)) {
                decoded.push_back(c);
            } else {
                string temp = decoded;
                for (int i = 0; i < c - '0' - 1; i++) {
                    decoded += temp;
                    if (decoded.size() >= K) {
                        break;
                    }
                }
            }
        }
        string result = "";
        result.push_back(decoded[K - 1]);
        return result;
    }
};