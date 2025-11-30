/*
1178. Number of Valid Words for Each Puzzle
https://leetcode.com/problems/number-of-valid-words-for-each-puzzle/

With respect to a given puzzle string,
a word is valid if both the following conditions are satisfied:
word contains the first letter of puzzle.
For each letter in word, that letter is in puzzle.

For example, if the puzzle is "abcdefg",
then valid words are "faced", "cabbage", and "baggage";
while invalid words are "beefed" (doesn't include "a") and "based" (includes "s" which isn't in the puzzle).

Return an array answer,
where answer[i] is the number of words in the given word list words that are valid with respect to the puzzle
puzzles[i].


Example :
Input:
words = ["aaaa","asas","able","ability","actt","actor","access"],
puzzles = ["aboveyz","abrodyz","abslute","absoryz","actresz","gaswxyz"]
Output: [1,1,3,2,4,0]
Explanation:
1 valid word for "aboveyz" : "aaaa"
1 valid word for "abrodyz" : "aaaa"
3 valid words for "abslute" : "aaaa", "asas", "able"
2 valid words for "absoryz" : "aaaa", "asas"
4 valid words for "actresz" : "aaaa", "asas", "actt", "access"
There're no valid words for "gaswxyz" cause none of the words in the list contains letter 'g'.

Constraints:
1 <= words.length <= 10^5
4 <= words[i].length <= 50
1 <= puzzles.length <= 10^4
puzzles[i].length == 7
words[i][j], puzzles[i][j] are English lowercase letters.
Each puzzles[i] doesn't contain repeated characters.
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
#include <set>
#include <numeric>
using namespace std;
/*
First of all, create a map to cache the frequency of the encoded word.

Next, loop the puzzles. During the inner loop, instead of loop through map's keyset (which cause TLE), use sub = (sub -
1) & mask to find all possible char combinations of current puzzel.

We need update count only if combination contains first element of puzzle as well as map has a record of it (means this
puzzle's char combination is as the same as one of the encoded word).

Time Compliexity: O( n * 2 ^ 7 + m * k) = O(n + mk)
n = len(puzzles);
m = len(words);
k = len(single word)
https://leetcode.com/problems/number-of-valid-words-for-each-puzzle/discuss/372385/Java-Bit-manipulation-%2B-Map-Solution-90ms

if we have 7 different chars in the puzzle, each index have 2 options (1 or 0). This means on the worst case we have 2 ^
7 combinations need to loop.

For example:
mask: 1111111 (abcdefg)
sub: 1111111 -> 1111110 -> 1111101 -> 1111100 -> 1111011 -> .... -> 0000001 -> 0000000
*/
class Solution {
private:
    int getMask(string& word) {
        int mask = 0;
        for (char c : word) {
            mask |= 1 << (c - 'a');
        }
        return mask;
    }

public:
    vector<int> findNumOfValidWords(vector<string>& words, vector<string>& puzzles) {
        unordered_map<int, int> wordMask;
        for (string& w : words) {
            wordMask[getMask(w)] += 1;
        }

        vector<int> result;
        for (string& puz : puzzles) {
            int pmask = getMask(puz);
            int count = 0;
            int sub = pmask;
            int first = 1 << (puz[0] - 'a');
            while (true) {
                if ((sub & first) == first and wordMask.find(sub) != wordMask.end()) {
                    count += wordMask[sub];
                }
                if (sub == 0) {
                    break;
                }
                sub = (sub - 1) & pmask;  // get next substring
            }
            result.push_back(count);
        }
        return result;
    }
};