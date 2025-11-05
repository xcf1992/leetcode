/*
916. Word Subsets
We are given two arrays A and B of words.
Each word is a string of lowercase letters.

Now, say that word b is a subset of word a if every letter in b occurs in a, including multiplicity.
For example, "wrr" is a subset of "warrior", but is not a subset of "world".

Now say a word a from A is universal if for every b in B, b is a subset of a.

Return a list of all universal words in A.  You can return the words in any order.

Example 1:

Input: A = ["amazon","apple","facebook","google","leetcode"], B = ["e","o"]
Output: ["facebook","google","leetcode"]
Example 2:

Input: A = ["amazon","apple","facebook","google","leetcode"], B = ["l","e"]
Output: ["apple","google","leetcode"]
Example 3:

Input: A = ["amazon","apple","facebook","google","leetcode"], B = ["e","oo"]
Output: ["facebook","google"]
Example 4:

Input: A = ["amazon","apple","facebook","google","leetcode"], B = ["lo","eo"]
Output: ["google","leetcode"]
Example 5:

Input: A = ["amazon","apple","facebook","google","leetcode"], B = ["ec","oc","ceo"]
Output: ["facebook","leetcode"]


Note:

1 <= A.length, B.length <= 10000
1 <= A[i].length, B[i].length <= 10
A[i] and B[i] consist only of lowercase letters.
All words in A[i] are unique: there isn't i != j with A[i] == A[j].
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
public:
    vector<string> wordSubsets(vector<string> &A, vector<string> &B) {
        vector<int> maxLetter(26, 0);
        for (string wordB: B) {
            vector<int> letterCount(26, 0);
            for (char c: wordB) {
                letterCount[c - 'a'] += 1;
                maxLetter[c - 'a'] = max(maxLetter[c - 'a'], letterCount[c - 'a']);
            }
        }

        vector<string> result;
        for (string wordA: A) {
            vector<int> letterCount(26, 0);
            for (char c: wordA) {
                letterCount[c - 'a'] += 1;
            }

            bool isUniversal = true;
            for (int i = 0; i < 26; i++) {
                if (letterCount[i] < maxLetter[i]) {
                    isUniversal = false;
                    break;
                }
            }
            if (isUniversal) {
                result.push_back(wordA);
            }
        }
        return result;
    }
};

// Time limit exceed
class Solution1 {
private:
    void countLetter(string &word, unordered_map<string, vector<int> > &count) {
        count[word] = vector<int>(26, 0);
        for (char c: word) {
            count[word][c - 'a'] += 1;
        }
    }

    bool isSubset(string &wordA, string &wordB, unordered_map<string, vector<int> > &countA,
                  unordered_map<string, vector<int> > &countB) {
        for (int i = 0; i < countB[wordB].size(); i++) {
            if (countA[wordA][i] < countB[wordB][i]) {
                return false;
            }
        }
        return true;
    }

public:
    vector<string> wordSubsets(vector<string> &A, vector<string> &B) {
        unordered_map<string, vector<int> > countA;
        for (string wordA: A) {
            countLetter(wordA, countA);
        }

        unordered_map<string, vector<int> > countB;
        for (string wordB: B) {
            countLetter(wordB, countB);
        }

        vector<string> result;
        for (string wordA: A) {
            bool isUniversal = true;
            for (string wordB: B) {
                if (!isSubset(wordA, wordB, countA, countB)) {
                    isUniversal = false;
                    break;
                }
            }
            if (isUniversal) {
                result.push_back(wordA);
            }
        }
        return result;
    }
};