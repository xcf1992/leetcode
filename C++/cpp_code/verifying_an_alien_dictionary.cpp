/*
 953. Verifying an Alien Dictionary
 In an alien language, surprisingly
 they also use english lowercase letters,
 but possibly in a different order.
 The order of the alphabet is some permutation of lowercase letters.

 Given a sequence of words written in the alien language,
 and the order of the alphabet,
 return true if and only if the given words are sorted lexicographicaly in this alien language.

 Example 1:

 Input: words = ["hello","leetcode"], order = "hlabcdefgijkmnopqrstuvwxyz"
 Output: true
 Explanation: As 'h' comes before 'l' in this language, then the sequence is sorted.
 Example 2:

 Input: words = ["word","world","row"], order = "worldabcefghijkmnpqstuvxyz"
 Output: false
 Explanation: As 'd' comes after 'l' in this language, then words[0] > words[1], hence the sequence is unsorted.
 Example 3:

 Input: words = ["apple","app"], order = "abcdefghijklmnopqrstuvwxyz"
 Output: false
 Explanation: The first three characters "app" match, and the second string is shorter (in size.) According to lexicographical rules "apple" > "app", because 'l' > '∅', where '∅' is defined as the blank character which is less than any other character (More info).


 Note:

 1 <= words.length <= 100
 1 <= words[i].length <= 20
 order.length == 26
 All characters in words[i] and order are english lowercase letters.
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
private:
    bool comeBefore(string word1, string word2, vector<int> letter) {
        int i = 0;
        int j = 0;
        while (i < word1.size() and j<word2.size()
        )
        {
            if (letter[word1[i] - 'a'] > letter[word2[j] - 'a']) {
                return false;
            }

            if (letter[word1[i] - 'a'] < letter[word2[j] - 'a']) {
                return true;
            }
            i++;
            j++;
        }
        return i == word1.size();
    }

public:
    bool isAlienSorted(vector<string> &words, string order) {
        vector<int> letter(26, -1);
        for (int i = 0; i < order.size(); i++) {
            letter[order[i] - 'a'] = i;
        }

        for (int i = 1; i < words.size(); i++)
            if (!comeBefore(words[i - 1], words[i], letter)) {
                return false;
            }
        return true;
    }
};