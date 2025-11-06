/*
1410. HTML Entity Parser
https://leetcode.com/problems/html-entity-parser/

HTML entity parser is the parser that takes HTML code as input
and replace all the entities of the special characters by the characters itself.

The special characters and their entities for HTML are:
Quotation Mark: the entity is &quot; and symbol character is ".
Single Quote Mark: the entity is &apos; and symbol character is '.
Ampersand: the entity is &amp; and symbol character is &.
Greater Than Sign: the entity is &gt; and symbol character is >.
Less Than Sign: the entity is &lt; and symbol character is <.
Slash: the entity is &frasl; and symbol character is /.

Given the input text string to the HTML parser,
you have to implement the entity parser.

Return the text after replacing the entities by the special characters.

Example 1:
Input: text = "&amp; is an HTML entity but &ambassador; is not."
Output: "& is an HTML entity but &ambassador; is not."
Explanation: The parser will replace the &amp; entity by &

Example 2:
Input: text = "and I quote: &quot;...&quot;"
Output: "and I quote: \"...\""

Example 3:
Input: text = "Stay home! Practice on Leetcode :)"
Output: "Stay home! Practice on Leetcode :)"

Example 4:
Input: text = "x &gt; y &amp;&amp; x &lt; y is always false"
Output: "x > y && x < y is always false"

Example 5:
Input: text = "leetcode.com&frasl;problemset&frasl;all"
Output: "leetcode.com/problemset/all"

Constraints:
1 <= text.length <= 10^5
The string may contain any possible characters out of all the 256 ASCII characters.
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
    string entityParser(string text) {
        vector<pair<string, char>> encoded[8] = {{},
                                                 {},
                                                 {},
                                                 {},
                                                 {{"&gt;", '>'}, {"&lt;", '<'}},
                                                 {{"&amp;", '&'}},
                                                 {{"&quot;", '"'}, {"&apos;", '\''}},
                                                 {{"&frasl;", '/'}}};
        int st = 0, p = 0;
        for (auto i = 0; i < text.size(); ++i, ++p) {
            text[p] = text[i];
            if (text[p] == '&')
                st = p;
            if (text[p] == ';') {
                auto sz = p - st + 1;
                if (sz >= 4 && sz <= 7)
                    for (auto& [enc, dec] : encoded[sz]) {
                        if (text.compare(st, sz, enc) == 0) {
                            p -= sz - 1;
                            text[p] = dec;
                            break;
                        }
                    }
                st = p + 1;
            }
        }
        text.resize(p);
        return text;
    }
};