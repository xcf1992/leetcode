/*
https://www.hack2hire.com/companies/stripe/coding-questions/696fea94b7afade5b30a39c4/practice?questionId=696feb8db7afade5b30a39ca
Business CSV Data Validator
You are developing a data ingestion component for a large-scale analytics platform. The platform receives raw data in a
simplified CSV format, where each line represents a record with specific attributes. Before storage or analysis, all
incoming data must be strictly validated to maintain data quality and comply with business requirements.

The system provides three inputs:

data: A list of strings, with each string representing a row in a CSV table containing n rows and 6 columns per row.
Each row follows the format "col1,col2,col3,col4,col5,col6", and the first row is always the header. forbiddenWords: A
list of strings containing words that are prohibited in specific fields. ignoreWords: A list of strings consisting of
common words (stop words) that should be ignored only during cross-column content comparison. For each data row
(excluding the header), determine whether it is "VALID" or "INVALID" by applying the following four rules in order:

RULE_1: Schema & Completeness.
Every column value must be non-empty after trimming any leading or trailing whitespace.

RULE_2: Column 5 Length Check.
The 5th column (col5), once trimmed, must have a length between 5 and 31 characters (inclusive).

RULE_3: Forbidden Words in Column 2.
The 2nd column (col2) must not contain any word from forbiddenWords.

Matching is case-insensitive.
Words are defined as tokens separated by whitespace.
RULE_4: Cross-Column Word Match.
A valid word is a lowercase word not found in ignoreWords. The row meets this rule only if at least 50% of valid words
in col2 are also present as valid words in either col4 or col5.

If col2 has zero valid words, the row is invalid.
Repeated valid words in col2 are only counted once for percentage calculation.
If a row satisfies all rules, label it as "VALID". If it fails any rule, label it as "INVALID: RULE_X", where X is the
number of the first failed rule. Return a list of validation results of length n - 1 (excluding the header), with each
result corresponding to a data row.

Constraints:
1 ≤ data.length ≤ 10^4

data[i] consists of ASCII characters.

forbiddenWords and ignoreWords can contain up to 10^3 elements.

Fields are separated strictly by a single comma (',').

There is no support for quotes or escape characters.

Commas will never appear as part of the content within a field.

Example 1:

Input: data = ["col1,col2,col3,col4,col5,col6",
               "id1,Land Water,c,d,land water llc,f",
               "id2,Good Company,c,d,land water,f",
               "id3,Apple banana,c,d,banana orange,f",
               "id4, ,c,d,hello world,f",
               "id5,LLC Inc,c,d,something real,f",
               "id6,blue sky ocean,c,d,green yellow pink,f",
               "id7,Best Group,c,d,hello group,f",
               "id8,land water,c,d,land,f"],
forbiddenWords = ["company", "firm", "co.", "corporation", "group"],
ignoreWords = ["llc", "inc"]
Output: ["VALID", "INVALID:RULE_3", "VALID", "INVALID:RULE_1", "INVALID:RULE_4", "INVALID:RULE_4", "INVALID:RULE_3",
"INVALID:RULE_2"] Explanation: All violations are listed below:

Row 2: col2 violates "RULE_3" as it contains forbiddenWords "Company". It violates "RULE_3".
Row 4: col2 violates "RULE_1" as it contains only whitespace.
Row 5: col2 violates "RULE_4" as both words are in ignoreWords.
Row 6: col2 violates "RULE_4" as words ("blue", "sky", "ocean") do not appear in col4 or col5.
Row 8: col5 violates "RULE_2"as its length is 4.
Example 2:

Input: data = ["col1,col2,col3,col4,col5,col6",
               "id1,hello world,c,d,hello there,f"],
forbiddenWords = ["bad", "wrong"],
ignoreWords = []
Output: ["VALID"]

Example 3:

Input: data = ["col1,col2,col3,col4,col5,col6",
               "id1,good name,c,d,test,f"],
forbiddenWords = [],
ignoreWords = []
Output: ["INVALID:RULE_2"]
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
using namespace std;

class Solution {
private:
    string trim(const string& str) {
        size_t start = str.find_first_not_of(" \t\n\r");
        if (string::npos == start) {
            return "";
        }
        size_t end = str.find_last_not_of(" \t\n\r");
        return str.substr(start, end - start + 1);
    }

    string to_lower(const string& str) {
        string rst = str;
        transform(rst.begin(), rst.end(), rst.begin(), ::tolower);
        return rst;
    }

    vector<string> split(const string& str, const char delimiter) {
        vector<string> rst;
        string cur = "";
        int n = str.size();
        for (int i = 0; i < n; i++) {
            if (str[i] == delimiter) {
                rst.push_back(cur);
                cur = "";
                continue;
            }

            cur += str[i];
        }
        rst.push_back(cur);
        return rst;
    }

    void add_words(const string& s, unordered_set<string>& rst) {
        string t = to_lower(trim(s));
        if (t.empty()) {
            return;
        }

        vector<string> parts = split(t, ' ');
        for (int i = 0; i < parts.size(); i = i + 1) {
            string w = parts[i];
            if (w.empty()) {
                continue;
            }

            if (ignore_words_.count(w)) {
                continue;
            }

            rst.insert(w);
        }
    }

    string validate(string& row) {
        vector<string> col_str = split(row, ',');

        // rule 1
        if (col_str.size() != 6) {
            return "INVALID:RULE_1";
        }

        for (int i = 0; i < 6; i++) {
            if (trim(col_str[i]).empty()) {
                return "INVALID:RULE_1";
            }
        }

        // rule 2
        string col5 = trim(col_str[4]);
        if (col5.size() < 5 || col5.size() > 31) {
            return "INVALID:RULE_2";
        }

        // rule 3
        string col2 = to_lower(trim(col_str[1]));
        vector<string> col2_words = split(col2, ' ');
        unordered_set<string> col2_valid_words;
        for (int i = 0; i < col2_words.size(); i++) {
            if (forbidden_words_.find(col2_words[i]) != forbidden_words_.end()) {
                return "INVALID:RULE_3";
            }

            if (ignore_words_.find(col2_words[i]) == ignore_words_.end()) {
                col2_valid_words.insert(col2_words[i]);
            }
        }

        // rule 4
        if (col2_valid_words.empty()) {
            return "INVALID:RULE_4";
        }

        string col4 = to_lower(trim(col_str[3]));
        unordered_set<string> col45_valid_words;
        add_words(col4, col45_valid_words);
        add_words(col5, col45_valid_words);

        int match_cnt = 0;
        for (string word : col2_valid_words) {
            if (col45_valid_words.find(word) != col45_valid_words.end()) {
                match_cnt += 1;
            }
        }
        if (match_cnt * 2 >= col2_valid_words.size()) {
            return "VALID";
        }
        return "INVALID:RULE_4";
    }
public:
    vector<string> validateDatasetRows(vector<string> data, vector<string> forbiddenWords, vector<string> ignoreWords) {
        int n = data.size();
        if (n <= 1) {
            return {};
        }

        for (const string& word : forbiddenWords) {
            forbidden_words_.insert(to_lower(trim(word)));
        }

        for (const string& word : ignoreWords) {
            ignore_words_.insert(to_lower(trim(word)));
        }

        vector<string> rst;
        for (int i = 1; i < n; i++) {
            rst.push_back(validate(data[i]));
        }
        return rst;
    }

private:
    unordered_set<string> forbidden_words_;
    unordered_set<string> ignore_words_;
};
