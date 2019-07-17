/*
 792. Number of Matching Subsequences
 Given string S and a dictionary of words words, find the number of words[i] that is a subsequence of S.

 Example :
 Input:
 S = "abcde"
 words = ["a", "bb", "acd", "ace"]
 Output: 3
 Explanation: There are three words in words that are a subsequence of S: "a", "acd", "ace".
 Note:

 All words in words and S will only consists of lowercase letters.
 The length of S will be in the range of [1, 50000].
 The length of words will be in the range of [1, 5000].
 The length of words[i] will be in the range of [1, 50].
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
using namespace std;

/*
Since the length of S is large, let's think about ways to iterate through S only once,
instead of many times as in the brute force solution.

We can put words into buckets by starting character.
If for example we have words = ['dog', 'cat', 'cop'],
then we can group them 'c' : ('cat', 'cop'), 'd' : ('dog',).
This groups words by what letter they are currently waiting for.
Then, while iterating through letters of S, we will move our words through different buckets.

For example, if we have a string like S = 'dcaog':
heads = 'c' : ('cat', 'cop'), 'd' : ('dog',) at beginning;
heads = 'c' : ('cat', 'cop'), 'o' : ('og',) after S[0] = 'd';
heads = 'a' : ('at',), 'o' : ('og', 'op') after S[0] = 'c';
heads = 'o' : ('og', 'op'), 't': ('t',) after S[0] = 'a';
heads = 'g' : ('g',), 'p': ('p',), 't': ('t',) after S[0] = 'o';
heads = 'p': ('p',), 't': ('t',) after S[0] = 'g';

Algorithm
Instead of a dictionary,
we'll use an array heads of length 26,
one entry for each letter of the alphabet.
For each letter in S, we'll take all the words waiting for that letter,
and have them wait for the next letter in that word.
If we use the last letter of some word, it adds 1 to the answer.

For another description of this algorithm and a more concise implementation,
please see @StefanPochmann's excellent forum post here.
https://leetcode.com/problems/number-of-matching-subsequences/discuss/117634/Efficient-and-simple-go-through-words-in-parallel-with-explanation/
*/
class Solution {
private:
    bool isSubsequence(vector<vector<int>>& position, string& word) {
        if (position[word[0] - 'a'].empty()) {
            return false;
        }

        int curPos = position[word[0] - 'a'].front();
        for (int i = 1; i < word.size(); ++i) {
            auto it = upper_bound(position[word[i] - 'a'].begin(), position[word[i] - 'a'].end(), curPos);
            if (it == position[word[i] - 'a'].end()) {
                return false;
            }
            curPos = *it;
        }
        return true;
    }
public:
    int numMatchingSubseq(string S, vector<string>& words) {
        vector<vector<int>> position(26, vector<int>());
        for (int i = 0; i < S.size(); i++) {
            position[S[i] - 'a'].push_back(i);
        }

        int result = 0;
        for (string word : words) {
            if (isSubsequence(position, word)) {
                result += 1;
            }
        }
        return result;
    }
};

class Solution1 {
public:
    int numMatchingSubseq(string S, vector<string>& words) {
        vector<vector<int>> position(26, vector<int>());
        for (int i = 0; i < S.size(); i++) {
            position[S[i] - 'a'].push_back(i);
        }

        int result = 0;
        for (string word : words) {
            if (word.size() == 1 && !position[word[0] - 'a'].empty()) {
                result += 1;
                continue;
            }

            int curPos = 0;
            for (int i = 0; i < word.size(); i++) {
                if (position[word[i] - 'a'].empty()) {
                    break;
                }

                if (i == 0) {
                    curPos = position[word[i] - 'a'].front();
                }
                else {
                    bool find = false;
                    for (int newPos : position[word[i] - 'a']) {
                        if (newPos > curPos) {
                            find = true;
                            curPos = newPos;
                            break;
                        }
                    }
                    if (find) {
                        if (i == word.size() - 1) {
                            result += 1;
                        }
                    }
                    else {
                        break;
                    }
                }
            }
        }
        return result;
    }
};
