/*
591. Tag Validator
Given a string representing a code snippet, you need to implement a tag validator to parse the code and return whether it is valid. A code snippet is valid if all the following rules hold:

The code must be wrapped in a valid closed tag. Otherwise, the code is invalid.
A closed tag (not necessarily valid) has exactly the following format : <TAG_NAME>TAG_CONTENT</TAG_NAME>. Among them, <TAG_NAME> is the start tag, and </TAG_NAME> is the end tag. The TAG_NAME in start and end tags should be the same. A closed tag is valid if and only if the TAG_NAME and TAG_CONTENT are valid.
A valid TAG_NAME only contain upper-case letters, and has length in range [1,9]. Otherwise, the TAG_NAME is invalid.
A valid TAG_CONTENT may contain other valid closed tags, cdata and any characters (see note1) EXCEPT unmatched <, unmatched start and end tag, and unmatched or closed tags with invalid TAG_NAME. Otherwise, the TAG_CONTENT is invalid.
A start tag is unmatched if no end tag exists with the same TAG_NAME, and vice versa. However, you also need to consider the issue of unbalanced when tags are nested.
A < is unmatched if you cannot find a subsequent >. And when you find a < or </, all the subsequent characters until the next > should be parsed as TAG_NAME (not necessarily valid).
The cdata has the following format : <![CDATA[CDATA_CONTENT]]>. The range of CDATA_CONTENT is defined as the characters between <![CDATA[ and the first subsequent ]]>.
CDATA_CONTENT may contain any characters. The function of cdata is to forbid the validator to parse CDATA_CONTENT, so even it has some characters that can be parsed as tag (no matter valid or invalid), you should treat it as regular characters.
Valid Code Examples:
Input: "<DIV>This is the first line <![CDATA[<div>]]></DIV>"

Output: True

Explanation:

The code is wrapped in a closed tag : <DIV> and </DIV>.

The TAG_NAME is valid, the TAG_CONTENT consists of some characters and cdata.

Although CDATA_CONTENT has unmatched start tag with invalid TAG_NAME, it should be considered as plain text, not parsed as tag.

So TAG_CONTENT is valid, and then the code is valid. Thus return true.


Input: "<DIV>>>  ![cdata[]] <![CDATA[<div>]>]]>]]>>]</DIV>"

Output: True

Explanation:

We first separate the code into : start_tag|tag_content|end_tag.

start_tag -> "<DIV>"

end_tag -> "</DIV>"

tag_content could also be separated into : text1|cdata|text2.

text1 -> ">>  ![cdata[]] "

cdata -> "<![CDATA[<div>]>]]>", where the CDATA_CONTENT is "<div>]>"

text2 -> "]]>>]"


The reason why start_tag is NOT "<DIV>>>" is because of the rule 6.
The reason why cdata is NOT "<![CDATA[<div>]>]]>]]>" is because of the rule 7.
Invalid Code Examples:
Input: "<A>  <B> </A>   </B>"
Output: False
Explanation: Unbalanced. If "<A>" is closed, then "<B>" must be unmatched, and vice versa.

Input: "<DIV>  div tag is not closed  <DIV>"
Output: False

Input: "<DIV>  unmatched <  </DIV>"
Output: False

Input: "<DIV> closed tags with invalid tag name  <b>123</b> </DIV>"
Output: False

Input: "<DIV> unmatched tags with invalid tag name  </1234567890> and <CDATA[[]]>  </DIV>"
Output: False

Input: "<DIV>  unmatched start tag <B>  and unmatched end tag </C>  </DIV>"
Output: False
Note:
For simplicity, you could assume the input code (including the any characters mentioned above) only contain letters, digits, '<','>','/','!','[',']' and ' '.
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

#define FIND_DATA_END 0
#define FIND_DATA_NOT_END 1
#define NOT_FIND_DATA 2
class Solution {
public:
    string seekTag(string& code, int &idx){
        string endTag;
        while( idx < code.size() ){
            char c = code[idx++];
            if( c == '>'){
                return endTag.size() <= 9 ? endTag:"";
            }
            else if( c <'A' || c >'Z')
                return "";
            endTag.push_back(c);
        }
        return "";
    }
    int seekEndData(string &str, int &idx){
        if( str.substr(idx, 9) == "<![CDATA[" ){
            size_t found = str.find( "]]>", idx);
            if( found != string::npos ){
                idx = found + 3;
                return FIND_DATA_END;
            }
            return FIND_DATA_NOT_END;
        }
        return NOT_FIND_DATA;
    }

    bool isValid(string code) {
        if( code.size() == 0 ) return true;
        if( code[0] != '<') return false;
        if( code.back() != '>') return false;
        stack<string> stk;
        for( int i = 0; i < code.size(); ){
            char c = code[i];
            if( c == '<' && code[i+1] !='/' ){  //tag start
                int res = seekEndData(code, i);  //try to find data content and skip it.
                if( res == FIND_DATA_END){  //skip data tag.

                }else if( res == FIND_DATA_NOT_END)  //include data tag but not include ']]>'
                    return false;
                else{                   //try to find tag.
                    i++;
                    string tag = seekTag(code, i);
                    if( tag.size() > 0 )
                        stk.push(tag);
                    else
                        return false;
                }
            }else if( c=='<' && code[i+1] =='/'){  // try to find end tag.
                i+=2;
                string endTag = seekTag(code, i);
                if( endTag.size() > 0 ){
                    if( stk.size() == 0 || endTag != stk.top() )
                        return false;
                    stk.pop();
                }else
                    return false;
            }else
                i++;
            if( i < code.size() && stk.size() == 0 )  //it is not closed by a tag.
                return false;
        }
        return stk.size() > 0 ? false : true;
    }
};
