/*
https://www.hack2hire.com/companies/openai/coding-questions/691cfb44ba2fba0a9e173e8b/practice?questionId=691cfb5cba2fba0a9e173e8c
Design In-Memory SQL

(This question is a variation of the LeetCode question 2408. Design SQL. If you haven't completed that question yet, it
is recommended to solve it first.)

Design an in-memory SQL database system that supports creating tables, inserting data with dynamic type inference, and
performing queries with filtering and sorting capabilities.

Implement the SQLManager class:

SQLManager() Initializes the empty database system.

void createTable(String tableName, List<String> columnNames) Creates a new table with the given tableName and a list of
fixed columnNames.

The tableName is guaranteed to be unique.
Columns are initially untyped, but data inserted will be inferred as either integers or strings.
void insert(String tableName, List<String> values) Inserts a row into the specified table.

The row ID is auto-incremented starting from 0 for each table.
values corresponds to the column names defined during table creation (in the same order).
Your implementation must infer the data type. If a value represents a valid integer (e.g., "123"), it is treated as a
number for comparison; otherwise, it is treated as a string. List<Integer> select(String tableName, List<List<String>>
conditions, List<String> orderBy) Selects rows from the table that satisfy all conditions (only consider "AND" logic)
and returns their IDs in correct order.

conditions: A list of filters, where each filter is [<columnName>, <operator>, <value>].
Supported operators: "=" , ">" and "<" .
orderBy: A list of column names. Results should be sorted by these columns in ascending order.
If orderBy is empty, return rows in insertion order.
If two rows have the same value for the first order column, use the second, and so on.
Constraints:

1 ≤ columnNames.length ≤ 100
All queries are valid (referenced tables and columns always exist).
Example:

Input:
["SQLManager", "createTable", "insert", "insert", "insert", "insert", "select", "select", "select", "select"]

[[],
 ["users", ["name", "age"]],
 ["users", ["Alice", "30"]],
 ["users", ["Bob", "25"]],
 ["users", ["Charlie", "35"]],
 ["users", ["Mary", "25"]],
 ["users", [["age", ">", "28"]], []],
 ["users", [["age", ">", "25"], ["name", "<", "C"]], []],
 ["users", [["age", ">", "20"]], ["name"]],
 ["users", [["age", ">", "24"]], ["age", "name"]]]

Output:
[null, null, null, null, null, null, [0, 2], [0], [0, 1, 2, 3], [1, 3, 0, 2]]

Explanation:

SQLManager db = new SQLManager(); // Initializes the database.
db.createTable("users", ["name", "age"]); // Creates table "users".
db.insert("users", ["Alice", "30"]); // Inserts row with ID 0. "30" is treated as an integer.
db.insert("users", ["Bob", "25"]); // Inserts row with ID 1.
db.insert("users", ["Charlie", "35"]); // Inserts row with ID 2.
db.insert("users", ["Mary", "25"]); // Inserts row with ID 3.
db.select("users", [["age", ">", "28"]], []); // Returns [0, 2]. "Alice" (30) and "Charlie" (35) are > 28. "Bob" and
"Mary" are not. db.select("users", [["age", ">", "25"], ["name", "<", "C"]], []); // Returns [0]. Only "Alice" matches
both. db.select("users", [["age", ">", "20"]], ["name"]); // Returns [0, 1, 2, 3]. All match. Sorted by name: "Alice",
"Bob", "Charlie", "Mary". db.select("users", [["age", ">", "24"]], ["age", "name"]); // Returns [1, 3, 0, 2]. All match.
Sorted by age first: "Bob" (25) and "Mary" (25) come before "Alice" (30) and "Charlie" (35). Tie-break for 25 uses name:
"Bob" comes before "Mary".
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
using namespace std;

struct Value {
    bool is_integer;
    int int_val;
    string str_val;

    Value() : is_integer(false), int_val(0), str_val("") {
    }

    Value(string s) {
        int_val = 0;
        for (int i = 0; i < s.size(); i++) {
            if (!isdigit(s[i])) {
                is_integer = false;
                int_val = 0;
                str_val = s;
                return;
            }

            int_val = int_val * 10 + s[i] - '0';
        }
        is_integer = true;
        str_val = "";
    }

    bool operator==(const Value& other) const {
        if (is_integer != other.is_integer) {
            return false;
        }

        if (is_integer) {
            return int_val == other.int_val;
        }
        return str_val == other.str_val;
    }

    bool operator<(const Value& other) const {
        if (is_integer && other.is_integer) {
            return int_val < other.int_val;
        }

        if (!is_integer && !other.is_integer) {
            return str_val < other.str_val;
        }

        return (is_integer ? to_string(int_val) : str_val) <
               (other.is_integer ? to_string(other.int_val) : other.str_val);
    }

    bool operator>(const Value& other) const {
        return other < *this;
    }
};

struct Table {
    vector<string> col_names;
    unordered_map<string, int> col_to_idx;
    vector<vector<Value>> row_data;
    vector<int> ids;

    Table(vector<string> names) : col_names(names) {
        for (int i = 0; i < names.size(); i++) {
            col_to_idx[names[i]] = i;
        }
    }
};

class SQLManager {
private:
    unordered_map<string, Table*> tables;
public:
    SQLManager() {
        tables.clear();
    }

    void createTable(string tableName, vector<string> columnNames) {
        if (tables.find(tableName) != tables.end()) {
            return;
        }
        tables[tableName] = new Table(columnNames);
    }

    void insert(string tableName, vector<string> values) {
        if (tables.find(tableName) == tables.end()) {
            return;
        }

        Table* cur_table = tables[tableName];
        vector<Value> cur_row;
        for (string& val : values) {
            cur_row.push_back(Value(val));
        }
        cur_table->ids.push_back(cur_table->row_data.size());
        cur_table->row_data.push_back(cur_row);
    }

    vector<int> select(string tableName, vector<vector<string>> conditions, vector<string> orderBy) {
        if (tables.find(tableName) == tables.end()) {
            return {};
        }

        Table* cur_table = tables[tableName];
        vector<int> rst;

        // filtering logic
        for (int i = 0; i < cur_table->row_data.size(); i++) {
            bool matched = true;
            for (vector<string>& cond : conditions) {
                int col_idx = cur_table->col_to_idx[cond[0]];
                string op = cond[1];
                Value tgt_val = Value(cond[2]);

                Value& cur_val = cur_table->row_data[i][col_idx];
                if (op == "=" && !(cur_val == tgt_val)) {
                    matched = false;
                    break;
                }

                if (op == ">" && !(cur_val > tgt_val)) {
                    matched = false;
                    break;
                }

                if (op == "<" && !(cur_val < tgt_val)) {
                    matched = false;
                    break;
                }
            }
            if (matched) {
                rst.push_back(i);
            }
        }

        // sorting logic
        if (rst.empty() || orderBy.empty()) {
            return rst;
        }

        sort(rst.begin(), rst.end(), [&](int a, int b) {
            for (string& col_name : orderBy) {
                int col_idx = cur_table->col_to_idx[col_name];
                if (cur_table->row_data[a][col_idx] == cur_table->row_data[b][col_idx]) {
                    continue;
                }

                return cur_table->row_data[a][col_idx] < cur_table->row_data[b][col_idx];
            }
            return a < b;
        });
        return rst;
    }
};
