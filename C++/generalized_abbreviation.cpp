/*
320. Generalized Abbreviation

Write a function to generate the generalized abbreviations of a word. 

Note: The order of the output does not matter.

Example:

Input: "word"
Output:
["word", "1ord", "w1rd", "wo1d", "wor1", "2rd", "w2d", "wo2", "1o1d", "1or1", "w1r1", "1o2", "2r1", "3d", "w3", "4"]

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
using namespace std;

class Solution {
private:
    void generate(vector<string>& result, int start, int preNum, string abbreviation, string& word) {
        if (start >= word.size()) {
            if (preNum != 0) {
                abbreviation += to_string(preNum);
            }
            result.push_back(abbreviation);
            return;
        }

        generate(result, start + 1, preNum + 1, abbreviation, word);
        if (preNum != 0) {
            abbreviation += to_string(preNum);
        }
        abbreviation.push_back(word[start]);
        generate(result, start + 1, 0, abbreviation, word);
    }
public:
    vector<string> generateAbbreviations(string word) {
        vector<string> result;
        generate(result, 0, 0, "", word);
        return result;
    }
};

/*
 Write a function to generate the generalized abbreviations of a word.
 
 Example:
 Given word = "word", return the following list (order does not matter):
 ["word", "1ord", "w1rd", "wo1d", "wor1", "2rd", "w2d", "wo2", "1o1d", "1or1", "w1r1", "1o2", "2r1", "3d", "w3", "4"]
 
 这道题让我们对一个单词进行部分简写，简写的规则是若干个字母可以用数字来表示，但是不能有两个相邻的数字
 */

class Solution1 {
public:
    vector<string> generateAbbreviations(string word) {
        vector<string> result;
        int n = word.size();
        for (int i = 0; i < pow(2, n); i++) {
            string abbreviation = "";
            int count = 0;
            int temp = i;
            for (int j = 0; j < n; j++) {
                if (temp & 1 == 1) {
                    count += 1;
                    if (j == n - 1) {
                        abbreviation += to_string(count);
                    }
                }
                else {
                    if (count != 0) {
                        abbreviation += to_string(count);
                        count = 0;
                    }
                    abbreviation += word[j];
                }
                temp >>= 1;
            }
            result.push_back(abbreviation);
        }
        return result;
    }
};

class Solution2 {
private:
    void dfs(vector<string>& result, string word, int pos, string cur, int count) {
        if (pos == word.size()) {
            if (count > 0) {
                cur += to_string(count);
            }
            result.push_back(cur);
            return;
        }
        
        dfs(result, word, pos + 1, cur, count + 1);
        cur = cur + (count > 0 ? to_string(count) : "") + word[pos];
        dfs(result, word, pos + 1, cur, 0);
    }
public:
    vector<string> generateAbbreviations(string word) {
        vector<string> result;
        dfs(result, word, 0, "", 0);
        return result;
    }
};
