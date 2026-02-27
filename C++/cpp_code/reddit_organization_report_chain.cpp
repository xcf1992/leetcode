/*
https://www.hack2hire.com/companies/reddit/coding-questions/6941cebce79fe20cf9ff443e/practice?questionId=6941d017e79fe20cf9ff443f
Organization Report Chain

A company's reporting structure is described as a list relationships, where each element is a list of strings. The first
string represents a manager, and the remaining strings are that manager's direct reports. Each employee name is unique,
and there is exactly one top-level manager who does not report to anyone.

Write a function that prints the complete organizational hierarchy following the rules below:

The top-level manager is printed on its own line with no indentation.
Every direct report is indented by exactly four dots ("....") more than their manager.
The indentation depth equals the number of levels below the top-level manager.
All direct reports under the same manager must be printed in alphabetical order.
Each employee appears exactly once in the output, even if they only appear as a manager or only as a subordinate.
The input parameter relationships is a list of lists, where each inner list contains a manager followed by one or more
direct reports.

The final result must be returned as a single string, with each employee on its own line separated by a newline
character ('\n'). There should be no trailing newline after the last line.

Constraints:

All names in relationships are non-empty and unique.
There is exactly one top-level manager.
1
1 ≤ relationships.length ≤
10
4
10
4

Each relationships[i] contains at least one string (the manager), and possibly multiple direct reports.
Example 1:

Input: relationships = [["a", "b", "c"], ["b", "d"], ["d", "e"]]
Output: "a\n....b\n........d\n............e\n....c"
Explanation: The hierarchy is shown below:

a
....b
........d
............e
....c
"a" is the top-level manager.
"b" and "c" report directly to "a" and are printed alphabetically.
"d" reports to "b", and "e" reports to "d".
Example 2:

Input: relationships = [["ceo", "vp1", "vp2"], ["vp1", "mgr1", "mgr2"], ["vp2", "mgr3"]]

Output: "ceo\n....vp1\n........mgr1\n........mgr2\n....vp2\n........mgr3"
Explanation: The hierarchy is shown below:

ceo
....vp1
........mgr1
........mgr2
....vp2
........mgr3
Example 3:

Input: relationships = [["ceo", "cto", "cfo", "coo"], ["cto", "vp_eng", "vp_product"], ["cfo", "vp_finance",
"vp_accounting"], ["vp_eng", "eng1", "eng2", "eng3"], ["vp_product", "pm1", "pm2"], ["eng1", "junior1", "junior2"]]

Output:
"ceo\n....cfo\n........vp_accounting\n........vp_finance\n....coo\n....cto\n........vp_eng\n............eng1\n................junior1\n................junior2\n............eng2\n............eng3\n........vp_product\n............pm1\n............pm2"
Explanation: The hierarchy is shown below:

ceo
....cfo
........vp_accounting
........vp_finance
....coo
....cto
........vp_eng
............eng1
................junior1
................junior2
............eng2
............eng3
........vp_product
............pm1
............pm2
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
#include <set>
#include <map>
using namespace std;

class Solution {
private:
    unordered_map<string, set<string>> mgr_to_workers_;
    unordered_set<string> all_workers_;

    void print_org(string& cur, string indent, string& rst) {
        rst += indent + cur + "\n";
        if (mgr_to_workers_.find(cur) == mgr_to_workers_.end()) {
            return;
        }

        indent += "....";
        for (string worker : mgr_to_workers_[cur]) {
            print_org(worker, indent, rst);
        }
    }

public:
    string printOrganization(vector<vector<string>> relationships) {
        if (relationships.empty()) {
            return "";
        }

        for (vector<string>& relationship : relationships) {
            string mgr = relationship[0];
            if (mgr_to_workers_.find(mgr) == mgr_to_workers_.end()) {
                mgr_to_workers_[mgr] = set<string>();
            }

            for (int i = 1; i < relationship.size(); i++) {
                string worker = relationship[i];
                mgr_to_workers_[mgr].insert(worker);
                all_workers_.insert(worker);
                if (mgr_to_workers_.find(worker) == mgr_to_workers_.end()) {
                    mgr_to_workers_[worker] = set<string>();
                }
            }
        }

        string top_mgr = "";
        for (auto& [mgr, reporters] : mgr_to_workers_) {
            if (all_workers_.find(mgr) == all_workers_.end()) {
                top_mgr = mgr;
                break;
            }
        }

        string indent = "";
        string rst = "";
        print_org(top_mgr, indent, rst);
        // Trim trailing whitespace
        while (!rst.empty() && (rst.back() == ' ' || rst.back() == '\n' || rst.back() == '\t')) {
            rst.pop_back();
        }
        return rst;
    }
};

/*
Follow-up 1:
As a follow-up to the previous organizational hierarchy problem, you are given the same reporting structure
relationships.

This time, your task is to identify all skip-level relationships within the organization. A skip-level relationship is
defined as a pair (manager, employee) such that:

The manager is exactly two levels above the employee in the hierarchy.
In other words, there exists an intermediate employee mid so that manager manages mid, and mid manages employee.
Given relationships, return a list of all skip-level pairs that exist in the organization. The order of the output does
not matter.

Example 1:

Input: relationships = [["a", "b", "c"], ["b", "d"], ["d", "e"]]
Output: [["a", "d"], ["b", "e"]]
Explanation:

"a" is two levels above "d" via "a" -> "b" -> "d", so ("a", "d") is a skip-level pair.
"b" is two levels above "e" via "b" -> "d" -> "e", so ("b", "e") is also a skip-level pair.
No other skip-level pairs exist in this structure.
The hierarchy is shown below:

a
....b
........d
............e
....c
Example 2:

Input: relationships = [["ceo", "vp1", "vp2"], ["vp1", "mgr1", "mgr2"], ["vp2", "mgr3"], ["mgr1", "emp1"]]
Output: [["ceo", "mgr1"], ["ceo", "mgr2"], ["ceo", "mgr3"], ["vp1", "emp1"]]

Example 3:

Input: relationships = [["ceo", "cto", "cfo", "coo"], ["cto", "vp_eng", "vp_product"], ["cfo", "vp_finance",
"vp_accounting"], ["vp_eng", "eng1", "eng2", "eng3"], ["vp_product", "pm1", "pm2"], ["eng1", "junior1", "junior2"]]
Output: [["ceo", "vp_eng"], ["ceo", "vp_product"], ["ceo", "vp_finance"], ["ceo", "vp_accounting"], ["cto", "eng1"],
["cto", "eng2"], ["cto", "eng3"], ["cto", "pm1"], ["cto", "pm2"], ["vp_eng", "junior1"], ["vp_eng", "junior2"]]
 */

class Solution {
private:
    unordered_map<string, set<string>> mgr_to_workers_;
    unordered_set<string> all_workers_;
    unordered_map<string, string> worker_to_mgr_;

public:
    vector<vector<string>> getSkipLevelPairs(vector<vector<string>> relationships) {
        if (relationships.empty()) {
            return {};
        }

        for (vector<string>& relationship : relationships) {
            string mgr = relationship[0];
            if (mgr_to_workers_.find(mgr) == mgr_to_workers_.end()) {
                mgr_to_workers_[mgr] = set<string>();
            }

            for (int i = 1; i < relationship.size(); i++) {
                string worker = relationship[i];
                mgr_to_workers_[mgr].insert(worker);
                all_workers_.insert(worker);
                if (mgr_to_workers_.find(worker) == mgr_to_workers_.end()) {
                    mgr_to_workers_[worker] = set<string>();
                }
                worker_to_mgr_[worker] = mgr;
            }
        }

        vector<vector<string>> rst;
        for (string worker : all_workers_) {
            if (worker_to_mgr_.find(worker) == worker_to_mgr_.end()) {
                continue;
            }

            string& dir_mgr = worker_to_mgr_[worker];
            if (worker_to_mgr_.find(dir_mgr) == worker_to_mgr_.end()) {
                continue;
            }

            rst.push_back({worker_to_mgr_[dir_mgr], worker});
        }
        return rst;
    }
};

/*
Follow-up 2:
As a follow-up to the previous organizational hierarchy problems, you are given the same reporting structure
relationships.

Given a target employee target, return the minimal organization subtree that includes:

target
all managers above target up to the top-level manager
all direct and indirect reports under target
Each employee will only have one manager
The returned hierarchy must follow these requirements:

The returned root must always be the highest manager in target's chain.
Use exactly four dots ("....") per level of indentation below the root. For example, the root is not indented, its
direct reports are indented by four dots, the next level by eight dots, and so on. For any manager, return their direct
reports in alphabetical order. Return an empty string if target does not exist in the organization. Each employee must
appear on their own line. Lines are separated using a line break character ('\n'). There must be no trailing newline
after the last line.

Example 1:

Input: relationships = [["a", "b", "c"], ["b", "d"], ["d", "e"]], target = "d"
Output: "a\n....b\n........d\n............e"
Explanation: The result contains "d", its managers ("a", "b"), and all subordinates under "d" ("e"). Only the relevant
branch is returned. The subtree is shown below:

a
....b
........d
............e
Example 2:

Input: relationships = [["ceo", "sales", "engineering", "hr"], ["sales", "sales_mgr1", "sales_mgr2"], ["engineering",
"eng_mgr1", "eng_mgr2"], ["hr", "hr_mgr"], ["eng_mgr1", "alice", "bob"]], target = "eng_mgr1" Output:
"ceo\n....engineering\n........eng_mgr1\n............alice\n............bob" Explanation: The subtree is shown below:

ceo
....engineering
........eng_mgr1
............alice
............bob
Example 3:

Input: relationships = [["ceo", "cto", "cfo", "coo"], ["cto", "vp_eng", "vp_product", "vp_security"], ["cfo",
"vp_finance", "vp_accounting"], ["coo", "vp_ops"], ["vp_eng", "eng_mgr1", "eng_mgr2", "eng_mgr3"], ["vp_product", "pm1",
"pm2"], ["eng_mgr2", "dev1", "dev2", "dev3"], ["dev1", "intern1", "intern2"]], target = "dev1" Output:
"ceo\n....cto\n........vp_eng\n............eng_mgr2\n................dev1\n....................intern1\n....................intern2"
Explanation: The subtree is shown below:

ceo
....cto
........vp_eng
............eng_mgr2
................dev1
....................intern1
....................intern2
*/

class Solution {
private:
    unordered_map<string, set<string>> mgr_to_workers_;
    unordered_set<string> all_workers_;
    unordered_map<string, string> worker_to_mgr_;

    void print_org(string& cur, string indent, string& rst) {
        rst += indent + cur + "\n";
        if (mgr_to_workers_.find(cur) == mgr_to_workers_.end()) {
            return;
        }

        indent += "....";
        for (string worker : mgr_to_workers_[cur]) {
            print_org(worker, indent, rst);
        }
    }

public:
    string printReportChain(vector<vector<string>> relationships, string target) {
        if (relationships.empty()) {
            return {};
        }

        for (vector<string>& relationship : relationships) {
            string mgr = relationship[0];
            if (mgr_to_workers_.find(mgr) == mgr_to_workers_.end()) {
                mgr_to_workers_[mgr] = set<string>();
            }

            for (int i = 1; i < relationship.size(); i++) {
                string worker = relationship[i];
                mgr_to_workers_[mgr].insert(worker);
                all_workers_.insert(worker);
                if (mgr_to_workers_.find(worker) == mgr_to_workers_.end()) {
                    mgr_to_workers_[worker] = set<string>();
                }
                worker_to_mgr_[worker] = mgr;
            }
        }

        if (worker_to_mgr_.find(target) == worker_to_mgr_.end() &&
            mgr_to_workers_.find(target) == mgr_to_workers_.end()) {
            return "";
        }

        vector<string> upper_org;
        string cur = target;
        while (worker_to_mgr_.find(cur) != worker_to_mgr_.end()) {
            upper_org.push_back(worker_to_mgr_[cur]);
            cur = worker_to_mgr_[cur];
        }

        string rst = "";
        string indent = "";
        for (int i = upper_org.size() - 1; i >= 0; i--) {
            rst += indent + upper_org[i] + "\n";
            indent += "....";
        }

        print_org(target, indent, rst);
        // Trim trailing whitespace
        while (!rst.empty() && (rst.back() == ' ' || rst.back() == '\n' || rst.back() == '\t')) {
            rst.pop_back();
        }
        return rst;
    }
};

/*
Follow-up 3:
As a follow-up to the previous organizational hierarchy problem, you are given the same reporting structure
relationships.

Given two employees emp1 and emp2, return their lowest common manager. The lowest common manager is the deepest employee
in the hierarchy who is a manager of both emp1 and emp2. An employee can be considered a manager of themselves, so if
emp1 equals emp2, the answer is that employee.

If either emp1 or emp2 does not exist in the organization, return "".

Example 1:

Input: relationships = [["A", "B", "C"], ["C", "D"], ["B", "E"]], emp1 = "C", emp2 = "E"
Output: "A"
Explanation: The hierarchy is shown below:

A
....B
........E
....C
........D
Both employees are under "A" in the hierarchy, and "A" is the deepest manager that is common to both reporting chains.

Example 2:

Input: relationships = [["a", "b", "c"], ["b", "d"], ["d", "e"]], emp1 = "b", emp2 = "e"
Output: "b"

Example 3:

Input: relationships = [["ceo", "cto", "cfo", "coo"], ["cto", "vp_eng", "vp_product"], ["vp_eng", "eng1", "eng2",
"eng3"], ["eng1", "junior1", "junior2"], ["cfo", "vp_finance"]], emp1 = "eng1", emp2 = "eng2" Output: "vp_eng"
 */
class Solution {
private:
    unordered_map<string, set<string>> mgr_to_workers_;
    unordered_set<string> all_workers_;
    unordered_map<string, string> worker_to_mgr_;

public:
    string getCommonManager(vector<vector<string>> relationships, string emp1, string emp2) {
        if (emp1 == emp2) {
            return emp1;
        }

        if (relationships.empty()) {
            return {};
        }

        for (vector<string>& relationship : relationships) {
            string mgr = relationship[0];
            if (mgr_to_workers_.find(mgr) == mgr_to_workers_.end()) {
                mgr_to_workers_[mgr] = set<string>();
            }

            for (int i = 1; i < relationship.size(); i++) {
                string worker = relationship[i];
                mgr_to_workers_[mgr].insert(worker);
                all_workers_.insert(worker);
                if (mgr_to_workers_.find(worker) == mgr_to_workers_.end()) {
                    mgr_to_workers_[worker] = set<string>();
                }
                worker_to_mgr_[worker] = mgr;
            }
        }

        if (all_workers_.find(emp1) == all_workers_.end() && mgr_to_workers_.find(emp1) == mgr_to_workers_.end()) {
            return "";
        }
        if (all_workers_.find(emp2) == all_workers_.end() && mgr_to_workers_.find(emp2) == mgr_to_workers_.end()) {
            return "";
        }

        unordered_set<string> mgr_chain;
        string cur = emp1;
        while (worker_to_mgr_.find(cur) != worker_to_mgr_.end()) {
            mgr_chain.insert(cur);
            cur = worker_to_mgr_[cur];
        }
        mgr_chain.insert(cur);

        cur = emp2;
        while (worker_to_mgr_.find(cur) != worker_to_mgr_.end()) {
            if (mgr_chain.find(cur) != mgr_chain.end()) {
                return cur;
            }
            cur = worker_to_mgr_[cur];
        }
        if (mgr_chain.find(cur) != mgr_chain.end()) {
            return cur;
        }
        return "";
    }
};