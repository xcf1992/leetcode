/*
843. Guess the Word
https://leetcode.com/problems/guess-the-word/

This problem is an interactive problem new to the LeetCode platform.

We are given a word list of unique words,
each word is 6 letters long,
and one word in this list is chosen as secret.

You may call master.guess(word) to guess a word.
The guessed word should have type string and must be from the original list with 6 lowercase letters.

This function returns an integer type,
representing the number of exact matches (value and position) of your guess to the secret word.
Also, if your guess is not in the given wordlist, it will return -1 instead.

For each test case,
you have 10 guesses to guess the word.
At the end of any number of calls,
if you have made 10 or less calls to master.guess and at least one of these guesses was the secret,
you pass the testcase.

Besides the example test case below,
there will be 5 additional test cases,
each with 100 words in the word list.
The letters of each word in those testcases were chosen independently at random from 'a' to 'z',
such that every word in the given word lists is unique.

Example 1:
Input: secret = "acckzz", wordlist = ["acckzz","ccbazz","eiowzz","abcczz"]
Explanation:
master.guess("aaaaaa") returns -1, because "aaaaaa" is not in wordlist.
master.guess("acckzz") returns 6, because "acckzz" is secret and has all 6 matches.
master.guess("ccbazz") returns 3, because "ccbazz" has 3 matches.
master.guess("eiowzz") returns 2, because "eiowzz" has 2 matches.
master.guess("abcczz") returns 4, because "abcczz" has 4 matches.
We made 5 calls to master.guess and one of them was the secret, so we pass the test case.

Note:
Any solutions that attempt to circumvent the judge will result in disqualification.
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
#include <stdio.h>
#include <set>
#include <numeric>
using namespace std;
/*
 * This is the Master's API interface.
 * You should not implement it, or speculate about its implementation
*/
class Master {
public:
    int guess(string word);
};

/*
Now we want to find a solution that improve this rate.

Generally, we will get 0 matches from the master.guess.

As a result, the size of wordlist reduces slowly.

Here we're going to assume that, we will always run into the worst case.

We need to guess a word that can minimum our worst outcome.

So we compare each two words and count their matches.

For each word, we note how many word of 0 matches it gets.

Then we guess the word with minimum words of 0 matches.

In this solution, we apply a minimax idea.

We minimize our worst case,

where the worst case is max(the number of words with i matches)
*/
class Solution {
private:
    int match(string &a, string &b) {
        int res = 0;
        for (int i = 0; i < a.size(); i++)
            res += a[i] == b[i] ? 1 : 0;
        return res;
    }

public:
    /*
    * Anyone who doesn't know why checking 0 match instead of 1,2,3...6 matches, please take a look at this comment.
    * The probability of two words with 0 match is (25/26)^6 = 80%.
    * That is to say, for a candidate word, we have 80% chance to see 0 match with the secret word.
    * In this case, we had 80% chance to eliminate the candidate word and its "family" words which have at least 1 match.
    * Additionally, in order to delete a max part of words, we select a candidate who has a big "family"
    * (fewest 0 match with other words).

    * Since the words are generated randomly.
    * So a word most probably has 0 matches with the secret word(80% possibility).
    * That's why we minimize the 0 matches rather than minimize the maximum matches.

    * randomly generate in the above solution
    * minimax: 因为你会保留其中一个group（和自己share 0,1,2,3,4,5,6这7个group中的一个），
    * 但是你不知道会保留哪一个group，所以使得所有group中的峰值最小的词，这样每一步可以保证删除比较多的词，而不至于落入极端情况，一步中删除很多，或者完全没怎么删除
    * 这个post解释得比较好：https://leetcode.com/problems/guess-the-word/discuss/134251/Optimal-MinMax-Solution-(+-extra-challenging-test-cases)

    * https://leetcode.com/problems/guess-the-word/discuss/134087/C++-elimination-histogram-beats-Minimax
    */
    void findSecretWord(vector<string> &wordlist, Master &master) {
        for (int i = 0, x = 0; i < 10 and x<6;
        ++i
        )
        {
            unordered_map<string, int> count;
            for (string w1: wordlist)
                for (string w2: wordlist)
                    if (match(w1, w2) == 0)
                        count[w1]++;
            pair<string, int> minimax = make_pair(wordlist[0], 1000);
            for (string w: wordlist)
                if (count[w] <= minimax.second)
                    minimax = make_pair(w, count[w]);
            x = master.guess(minimax.first);
            vector<string> wordlist2;
            for (string w: wordlist)
                if (match(minimax.first, w) == x)
                    wordlist2.push_back(w);
            wordlist = wordlist2;
        }
    }
};

class Solution2 {
private:
    int match(string &a, string &b) {
        int res = 0;
        for (int i = 0; i < a.size(); i++) {
            res += a[i] == b[i] ? 1 : 0;
        }
        return res;
    }

public:
    void findSecretWord(vector<string> &wordlist, Master &master) {
        vector<string> candidates = wordlist;
        for (int i = 0; i < 10; i++) {
            string s = candidates[rand() % candidates.size()];

            int x = master.guess(s);
            if (x == 6) {
                return;
            }

            //candidates =  neighbors with match x intersect candidates
            vector<string> intersect;
            for (auto w: wordlist) {
                if (match(w, s) == x and find(candidates.begin(), candidates.end(), w)
                !=
                candidates.end()
                )
                {
                    intersect.push_back(w);
                }
            }
            candidates = intersect;
        }
    }
};