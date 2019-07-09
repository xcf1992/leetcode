/*
1096. Brace Expresultion II
Under a grammar given below, strings can represent a set of lowercase words.  Let's use R(expr) to denote the set of words the expression represents.

Grammar can best be understood through simple examples:

Single letters represent a singleton set containing that word.
R("a") = {"a"}
R("w") = {"w"}
When we take a comma delimited list of 2 or more expressions, we take the union of possibilities.
R("{a,b,c}") = {"a","b","c"}
R("{{a,b},{b,c}}") = {"a","b","c"} (notice the final set only contains each word at most once)
When we concatenate two expressions, we take the set of possible concatenations between two words where the first word comes from the first expression and the second word comes from the second expression.
R("{a,b}{c,d}") = {"ac","ad","bc","bd"}
R("a{b,c}{d,e}f{g,h}") = {"abdfg", "abdfh", "abefg", "abefh", "acdfg", "acdfh", "acefg", "acefh"}
Formally, the 3 rules for our grammar:

For every lowercase letter x, we have R(x) = {x}
For expressions e_1, e_2, ... , e_k with k >= 2, we have R({e_1,e_2,...}) = R(e_1) ∪ R(e_2) ∪ ...
For expressions e_1 and e_2, we have R(e_1 + e_2) = {a + b for (a, b) in R(e_1) × R(e_2)}, where + denotes concatenation, and × denotes the cartesian product.
Given an expression representing a set of words under the given grammar, return the sorted list of words that the expression represents.



Example 1:

Input: "{a,b}{c,{d,e}}"
Output: ["ac","ad","ae","bc","bd","be"]
Example 2:

Input: "{{a,z},a{b,c},{ab,z}}"
Output: ["a","ab","ac","z"]
Explanation: Each distinct word is written only once in the final resultwer.


Constraints:

1 <= expression.length <= 50
expression[pos] consists of '{', '}', ','or lowercase English letters.
The given expression represents a set of words based on the grammar given in the description.
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
#include <set>
#include <numeric>
using namespace std;

/*
题意：告诉我们三个规则。

规则一：单个字符串集合，可以表示为a，代表一个字符串"a"。
规则二、字符串集合的并集，表示为{a,b,c,d}，代表"a","b","c"四个字符串。
规则三、字符串集合的叉集，表示为{a,b}{c,d}e，代表"ace","ade","bce","bde"四个字符串。

问题：告诉我们一个表达式，求最终的字符串集合。

思路： 这个规则描述其实不太好实现，我们稍微转化一下就简单了。

定义：a,b,c,d,e,f都是符合规则的表达式。
规则零、字符串，使用[a-z]+表示，代表一个集合，只有一个字符串。
规则一、字符串集合，使用{a}表示，代表a是一个合法的表达式，对应的结果是一个字符串集合。
规则二、字符串集合的并集，使用a,b,c,d表示，代表a,b,c,d四个集合求并集。
规则三、字符串集合的叉集，使用abcd表示，代表a,b,c,d四个集合求叉集。
叉集定义（两个集合为例）：第一个集合里的任何一个元素与第二个集合里的任何一个元素拼接在一起所形成的的字符串集合。

按照这个定义，问题给的表达式其实属于规则二。
规则一由花括号与规则二组成。
规则二由若干个逗号分隔的规则三组成。
规则三由若干相连的规则零或规则一组成。

由此，我们可以写出对应的递归方程来。
*/
class Solution {
private:
    set<string> merge(set<string>& a, set<string>& b) {
        if (a.empty() or b.empty()) {
            return a.empty() ? b : a;
        }

        set<string> result;
        for (string s1 : a) {
            for (string s2 : b) {
                result.insert(s1 + s2);
            }
        }
        return result;
    }

    //a{c,d}b = {acb, adb}
    set<string> combine(const string& str, int& pos) { // rule 3
        set<string> result;
        while (pos < str.length()) {
            if (str[pos] == '}' or str[pos] == ',') {
                break;
            }
            if (str[pos] == '{') {
                pos += 1;
                set<string> tmp = parse(str, pos);
                pos += 1;
                result = merge(result, tmp);
            }
            else {
                set<string> tmp;
                string cur;
                while(pos < str.length() and str[pos] <= 'z' and str[pos] >= 'a'){
                    cur.push_back(str[pos]);
                    pos += 1;
                }
                tmp.insert(cur);
                result = merge(result, tmp);
            }
        }
        return result;
    }

    //{a,c},{c,d} = {a, c, d}
    set<string> parse(const string& str, int& pos) { // rule 2
        set<string> result;
        result = combine(str, pos);
        while (pos < str.size()) {
            if (str[pos] != ',') {
                break;
            }
            pos += 1;

            set<string> tmp = combine(str, pos);
            result.insert(tmp.begin(), tmp.end());
        }
        return result;
    }
public:
    vector<string> braceExpansionII(string expression) {
        int pos = 0;
        set<string> result = parse(expression, pos);
        return vector<string>(result.begin(), result.end());
    }
};
