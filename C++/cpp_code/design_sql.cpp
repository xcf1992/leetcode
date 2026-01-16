/*
https://leetcode.com/problems/design-sql/description/
2408. Design SQL

You are given two string arrays, names and columns, both of size n. The ith table is represented by the name names[i]
and contains columns[i] number of columns.

You need to implement a class that supports the following operations:

Insert a row in a specific table with an id assigned using an auto-increment method, where the id of the first inserted
row is 1, and the id of each new row inserted into the same table is one greater than the id of the last inserted row,
even if the last row was removed. Remove a row from a specific table. Removing a row does not affect the id of the next
inserted row. Select a specific cell from any table and return its value. Export all rows from any table in csv format.
Implement the SQL class:

SQL(String[] names, int[] columns)
Creates the n tables.
bool ins(String name, String[] row)
Inserts row into the table name and returns true.
If row.length does not match the expected number of columns, or name is not a valid table, returns false without any
insertion. void rmv(String name, int rowId) Removes the row rowId from the table name. If name is not a valid table or
there is no row with id rowId, no removal is performed. String sel(String name, int rowId, int columnId) Returns the
value of the cell at the specified rowId and columnId in the table name. If name is not a valid table, or the cell
(rowId, columnId) is invalid, returns "<null>". String[] exp(String name) Returns the rows present in the table name. If
name is not a valid table, returns an empty array. Each row is represented as a string, with each cell value (including
the row's id) separated by a ",".


Example 1:

Input:

["SQL","ins","sel","ins","exp","rmv","sel","exp"]
[[["one","two","three"],[2,3,1]],["two",["first","second","third"]],["two",1,3],["two",["fourth","fifth","sixth"]],["two"],["two",1],["two",2,2],["two"]]
Output:

[null,true,"third",true,["1,first,second,third","2,fourth,fifth,sixth"],null,"fifth",["2,fourth,fifth,sixth"]]
Explanation:

// Creates three tables.
SQL sql = new SQL(["one", "two", "three"], [2, 3, 1]);

// Adds a row to the table "two" with id 1. Returns True.
sql.ins("two", ["first", "second", "third"]);

// Returns the value "third" from the third column
// in the row with id 1 of the table "two".
sql.sel("two", 1, 3);

// Adds another row to the table "two" with id 2. Returns True.
sql.ins("two", ["fourth", "fifth", "sixth"]);

// Exports the rows of the table "two".
// Currently, the table has 2 rows with ids 1 and 2.
sql.exp("two");

// Removes the first row of the table "two". Note that the second row
// will still have the id 2.
sql.rmv("two", 1);

// Returns the value "fifth" from the second column
// in the row with id 2 of the table "two".
sql.sel("two", 2, 2);

// Exports the rows of the table "two".
// Currently, the table has 1 row with id 2.
sql.exp("two");
Example 2:

Input:

["SQL","ins","sel","rmv","sel","ins","ins"]
[[["one","two","three"],[2,3,1]],["two",["first","second","third"]],["two",1,3],["two",1],["two",1,2],["two",["fourth","fifth"]],["two",["fourth","fifth","sixth"]]]
Output:

[null,true,"third",null,"<null>",false,true]
Explanation:

// Creates three tables.
SQL sQL = new SQL(["one", "two", "three"], [2, 3, 1]);

// Adds a row to the table "two" with id 1. Returns True.
sQL.ins("two", ["first", "second", "third"]);

// Returns the value "third" from the third column
// in the row with id 1 of the table "two".
sQL.sel("two", 1, 3);

// Removes the first row of the table "two".
sQL.rmv("two", 1);

// Returns "<null>" as the cell with id 1
// has been removed from table "two".
sQL.sel("two", 1, 2);

// Returns False as number of columns are not correct.
sQL.ins("two", ["fourth", "fifth"]);

// Adds a row to the table "two" with id 2. Returns True.
sQL.ins("two", ["fourth", "fifth", "sixth"]);


Constraints:

n == names.length == columns.length
1 <= n <= 104
1 <= names[i].length, row[i].length, name.length <= 10
names[i], row[i], and name consist only of lowercase English letters.
1 <= columns[i] <= 10
1 <= row.length <= 10
All names[i] are distinct.
At most 2000 calls will be made to ins and rmv.
At most 104 calls will be made to sel.
At most 500 calls will be made to exp.


Follow-up: Which approach would you choose if the table might become sparse due to many deletions, and why? Consider the
impact on memory usage and performance.
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

struct Table {
    int row_id_;
    int col_cnt_;
    unordered_map<int, vector<string>> row_data_;

    Table() : row_id_(0), col_cnt_(0) {
    }

    bool add_row(vector<string>& row) {
        if (row.size() != col_cnt_) {
            return false;
        }

        row_id_ += 1;
        row_data_[row_id_] = row;
        return true;
    }

    void rmv_row(int row_id) {
        if (row_data_.find(row_id) == row_data_.end()) {
            return;
        }
        row_data_.erase(row_id);
    }

    string sel_data(int row_id, int col_id) {
        if (row_data_.find(row_id) == row_data_.end()) {
            return "<null>";
        }

        if (col_id - 1 >= col_cnt_) {
            return "<null>";
        }

        return row_data_[row_id][col_id - 1];
    }

    vector<string> exp_data() {
        vector<string> rst;
        for (int i = 1; i <= row_id_; i++) {
            if (row_data_.find(i) == row_data_.end()) {
                continue;
            }
            string data = to_string(i);
            for (string& val : row_data_[i]) {
                data += "," + val;
            }
            rst.push_back(data);
        }
        return rst;
    }
};

class SQL {
private:
    unordered_map<string, Table> name_to_table_;

public:
    SQL(vector<string>& names, vector<int>& columns) {
        for (int i = 0; i < names.size(); i++) {
            if (name_to_table_.find(names[i]) == name_to_table_.end()) {
                name_to_table_[names[i]] = Table();
                name_to_table_[names[i]].col_cnt_ = columns[i];
            }
        }

    }

    bool ins(string name, vector<string> row) {
        if (name_to_table_.find(name) == name_to_table_.end()) {
            return false;
        }
        return name_to_table_[name].add_row(row);
    }

    void rmv(string name, int rowId) {
        if (name_to_table_.find(name) == name_to_table_.end()) {
            return;
        }
        name_to_table_[name].rmv_row(rowId);
    }

    string sel(string name, int rowId, int columnId) {
        if (name_to_table_.find(name) == name_to_table_.end()) {
            return "<null>";
        }
        return name_to_table_[name].sel_data(rowId, columnId);
    }

    vector<string> exp(string name) {
        if (name_to_table_.find(name) == name_to_table_.end()) {
            return {};
        }
        return name_to_table_[name].exp_data();
    }
};

/**
 * Your SQL object will be instantiated and called as such:
 * SQL* obj = new SQL(names, columns);
 * bool param_1 = obj->ins(name,row);
 * obj->rmv(name,rowId);
 * string param_3 = obj->sel(name,rowId,columnId);
 * vector<string> param_4 = obj->exp(name);
 */