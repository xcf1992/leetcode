/*
288. Unique Word Abbreviation
https://leetcode.com/problems/unique-word-abbreviation/

An abbreviation of a word follows the form <first letter><number><last letter>.
Below are some examples of word abbreviations:
a) it                      --> it    (no abbreviation)

     1
     ↓
b) d|o|g                   --> d1g

              1    1  1
     1---5----0----5--8
     ↓   ↓    ↓    ↓  ↓
c) i|nternationalizatio|n  --> i18n

              1
     1---5----0
     ↓   ↓    ↓
d) l|ocalizatio|n          --> l10n

Assume you have a dictionary and given a word,
find whether its abbreviation is unique in the dictionary.
A word's abbreviation is unique if no other word from the dictionary has the same abbreviation.

Example:
Given dictionary = [ "deer", "door", "cake", "card" ]
isUnique("dear") -> false
isUnique("cart") -> true
isUnique("cane") -> false
isUnique("make") -> true
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
这题题目不难，但题目定义的让我一脸懵逼。
就是给了一组List，里面有若干个英语单词。然后除去头和尾，其他的字符都缩成了数字，比如：
"dear"的头是d，尾巴是r，中间的ea一共是2个字母，所以变成了2，最终缩完的output是：d2r

主方程isUnique()的判定条件是

缩写完以后的input是否出现在字典中过，如果没出现过，则代表字典不包含当前input，则返回True。

如果出现过，继续比对两个缩写单词的原词，举例：
比如dear和door缩写完以后都为d2r，虽然在字典里的key同为d2r，但实际原词不一样
如果原词一样，则表示这个单词任然是Unique，因为字典里包含的就是原词本身。
如果不一样，则代表字典里有其他缩写相等的词，返回False
*/
class ValidWordAbbr {
private:
    unordered_map<string, unordered_set<string>> abbreviation;

    string getAbbrev(string word) {
        if (word.size() <= 2) {
            return word;
        }
        return string(1, word.front()) + to_string(word.size() - 2) + string(1, word.back());
    }

public:
    ValidWordAbbr(vector<string> dictionary) {
        for (string word : dictionary) {
            abbreviation[getAbbrev(word)].insert(word);
        }
    }

    bool isUnique(string word) {
        string abbrev = getAbbrev(word);
        if (abbreviation.find(abbrev) != abbreviation.end()) {
            if (abbreviation[abbrev].size() == 1) {
                return abbreviation[abbrev].find(word) != abbreviation[abbrev].end();
            }
            return false;
        }
        return true;
    }
};

/*
 * Your ValidWordAbbr object will be instantiated and called as such:
 * ValidWordAbbr obj = new ValidWordAbbr(dictionary);
 * bool param_1 = obj.isUnique(word);
 */