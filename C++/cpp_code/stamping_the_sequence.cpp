/*
936. Stamping The Sequence

You want to form a target string of lowercase letters.

At the beginning, your sequence is target.length '?' marks.
You also have a stamp of lowercase letters.

On each turn, you may place the stamp over the sequence,
and replace every letter in the sequence with the corresponding letter from the stamp.
You can make up to 10 * target.length turns.

For example, if the initial sequence is "?????",
and your stamp is "abc",
then you may make "abc??", "?abc?", "??abc" in the first turn.
(Note that the stamp must be fully contained in the boundaries of the sequence in order to stamp.)

If the sequence is possible to stamp,
then return an array of the index of the left-most letter being stamped at each turn.
If the sequence is not possible to stamp, return an empty array.

For example, if the sequence is "ababc", and the stamp is "abc", then we could return the answer [0, 2],
corresponding to the moves "?????" -> "abc??" -> "ababc".

Also, if the sequence is possible to stamp, it is guaranteed it is possible to stamp within 10 * target.length moves.
Any answers specifying more than this number of moves will not be accepted.

Example 1:
Input: stamp = "abc", target = "ababc"
Output: [0,2]
([1,0,2] would also be accepted as an answer, as well as some other answers.)

Example 2:
Input: stamp = "aabcaca", target = "abca"
Output: [3,0,1]

Note:
1 <= stamp.length <= target.length <= 1000
stamp and target only contain lowercase letters.
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
The operation token later will be more apperant than the operation token before.
And we really don't care about the letters which are covered.

*  *  *  *  *  *  *
*  *  * |a  b  c  a|
|a  b  c  a| b  c  a
a |a  b  c  a| c  a
We just try to match the stamp with the target.
Since we do not care about the letters which are coverd by others,
so we can apply a * match any letters.

For example:
"aabcaca" -> "a****ca" -> "*****ca"->"*******"

the time complexity should be N^2 * M,
where N is the length of target and M is the length of stamp
*/
class Solution {
private:
    int remove(string &target, string stamp) {
        int n = target.size();
        for (int i = 0; i < n; i++) {
            int pos = i;
            int j = 0;
            bool matched = false;
            while (j < stamp.size() and pos<target.size() and(target[pos] == stamp[j] or target[pos] == '*')
            )
            {
                if (target[pos] == stamp[j]) {
                    matched = true;
                }
                pos += 1;
                j += 1;
            }

            if (j == stamp.size() and matched
            )
            {
                for (int k = 0; k < stamp.size(); k++) {
                    target[i + k] = '*';
                }
                return i;
            }
        }
        return target.size();
    }

public:
    vector<int> movesToStamp(string stamp, string target) {
        int n = target.size();
        vector<int> result;
        string aim = string(n, '*');
        while (target != aim) {
            int pos = remove(target, stamp);
            if (pos == n) {
                return {};
            }
            result.push_back(pos);
        }
        reverse(result.begin(), result.end());
        return result;
    }
};

/*
It's better explained through an example.
Let's say the target is 'aabccbc', and stamp is 'abc'.
We first try to find 'abc' and replace it with '***'.
After there are no more replacements,
we will try '*bc' and 'ab*', and so on. Now, turn by turn:

'aabccbc' ? 'abc' = [1]
'a***cbc' ? '*bc' = []
'a***cbc' ? 'ab*' = []
'a***cbc' ? 'a**' = [0]
'****cbc' ? '*b*' = []
'****cbc' ? '**c' = [2]
'*****bc' ? '*bc' = [4]

still too slow https://leetcode.com/problems/stamping-the-sequence/discuss/285844/C%2B%2B-Very-Short-No-extra-space-(except-for-answer)-Beats-100100-(16ms-9mb)
*/
class Solution1 {
public:
    vector<int> movesToStamp(string stamp, string target) {
        int sLen = stamp.size();
        int tLen = target.size();

        vector<int> result;
        int modified = 0;
        int curModified = -1;
        while (curModified != 0) {
            curModified = 0;
            for (int sz = sLen; sz > 0; --sz) {
                // the stamp should at least have one letter
                for (int preStar = 0; preStar + sz <= sLen; ++preStar) {
                    string curStamp = string(preStar, '*') + stamp.substr(preStar, sz) + string(
                                          sLen - preStar - sz, '*');
                    auto pos = target.find(curStamp);
                    while (pos != string::npos) {
                        result.push_back(pos);
                        curModified += sz;
                        fill(target.begin() + pos, target.begin() + pos + stamp.size(), '*');
                        pos = target.find(curStamp);
                    }
                }
            }
            modified += curModified;
        }

        if (modified == tLen) {
            // check if all the target letters has been modified
            reverse(result.begin(), result.end());
            return result;
        }
        return {};
    }
};