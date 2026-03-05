/*
https://www.hack2hire.com/companies/stripe/coding-questions/697c3da69731315964cfb08a/practice?questionId=697c3db29731315964cfb08b
Linked User Records by Similarity

A data-quality team is working to identify duplicate or highly similar user profiles within a large dataset. Each user
profile is represented as a row in a 2D string array records, where the first row is a header specifying field names
(such as "id", "name", "email", "company"). All subsequent rows contain string values for each field.

You are also given an array weights, where each element is formatted as "<field>:<weight>". Each <field> corresponds to
a field in the header other than "id", and <weight> is a decimal number between [0, 1]. The sum of all <weight> values
is exactly 1.0. A higher weight means that matching on that field is more important.

The similarity score between two user profiles is defined as the sum of the weights for all fields where their values
are equal. Fields not listed in weights do not contribute to the similarity score.

Given a similarity threshold threshold, and a targetUserId, find all user profiles that are directly linked to the
target profile. A profile is directly linked if its similarity score with the target profile is greater than or equal to
threshold. The target profile itself should not be included in the result. Return the list of matching id values in any
order. If the target profile itself does not exist in the records, return an empty list.

Constraints:

2 ≤ records.length ≤ 104
records[0] contains field names; one of them is always id
All id values are unique strings that represent integers.
1 ≤ weights.length ≤ records[0].length - 1
0 < threshold ≤ 1.0
Example 1:

Input: records = [["id", "name", "email", "company"],
                  ["1", "Alice", "alice@gmail.com", "Stripe"],
                  ["2", "Alicia", "alice@gmail.com", "Stripe"],
                  ["3", "Alice", "alice@yahoo.com", "Google"],
                  ["4", "Bob", "bob@gmail.com", "Stripe"]],
       weights = ["name:0.2", "email:0.5", "company:0.3"], threshold = 0.5, targetUserId = 1
Output: [2]
Explanation: Profile 2 shares both "email" and "company" with the target (ID = 1), resulting in a similarity score of
0.5 + 0.3 = 0.8, which meets the threshold. Profiles 3 and 4 do not reach the threshold.

Example 2:

Input: records = [["id", "city", "age"],
                  ["1", "NYC", "25"],
                  ["2", "NYC", "25"],
                  ["3", "NYC", "30"],
                  ["4", "LA", "25"]],
       weights = ["city:0.6", "age:0.4"], threshold = 0.6, targetUserId = 1
Output: [2, 3]

Example 3:

Input: records = [["id", "name", "email"],
                  ["1", "Alice", "alice@a.com"],
                  ["2", "Bob", "bob@b.com"],
                  ["3", "Charlie", "charlie@c.com"]],
       weights = ["name:0.5", "email:0.5"], threshold = 0.5, targetUserId = 1
Output: []
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
#include <chrono>
#include <iostream>
#include <thread>
using namespace std;

class Solution {
private:
    void parse_weight(string& str, unordered_map<string, double>& field_to_weight) {
        int pos = str.find(":");
        string field = str.substr(0, pos);
        double weight = stod(str.substr(pos + 1));
        field_to_weight[field] = weight;
    }

public:
    vector<int> findLinkedUsers(vector<vector<string>> records, vector<string> weights, double threshold,
                                int targetUserId) {
        unordered_map<string, double> field_to_weight;
        for (string& str : weights) {
            parse_weight(str, field_to_weight);
        }

        vector<string> tgt_record;
        for (int i = 1; i < records.size(); i++) {
            if (records[i][0] == to_string(targetUserId)) {
                tgt_record = records[i];
                break;
            }
        }
        if (tgt_record.empty()) {
            return vector<int>{};
        }

        vector<int> rst;
        for (int i = 1; i < records.size(); i++) {
            vector<string>& record = records[i];
            int usr_id = stoi(record[0]);
            if (usr_id == targetUserId) {
                continue;
            }

            double score = 0.0;
            for (int j = 1; j < record.size(); j++) {
                if (field_to_weight.find(records[0][j]) == field_to_weight.end()) {
                    continue;
                }

                if (record[j] == tgt_record[j]) {
                    score += field_to_weight[records[0][j]];
                }
            }

            if (score >= threshold) {
                rst.push_back(usr_id);
            }
        }
        return rst;
    }
};

/*
Follow-up 1:
In this follow-up, your task is to find all profiles that are at most one hop of the target profile. Specifically,
return all id values that are either directly connected to the target or directly connected to target-linked profiles,
excluding duplicates and the target itself. You may return the result in any order.

Example 1:

Input: records = [["id", "f1", "f2"],
                  ["1", "a", "b"],
                  ["2", "a", "c"],
                  ["3", "d", "c"],
                  ["4", "a", "b"]],
       weights = ["f1:0.5", "f2:0.5"], threshold = 0.5, targetUserId = 1
Output: [2, 3, 4]
Explanation: Profiles 2 and 4 are directly linked to the target. Profile 3 is directly linked to profile 2. All are
within one hop, so the answer is [2, 3, 4].

Example 2:

Input: records = [["id", "name", "email", "company"],
                  ["1", "Alice", "alice@gmail.com", "Stripe"],
                  ["2", "Alicia", "alice@gmail.com", "Stripe"],
                  ["3", "Alice", "alice@yahoo.com", "Google"],
                  ["4", "Bob", "bob@gmail.com", "Stripe"]],
       weights = ["name:0.2", "email:0.5", "company:0.3"], threshold = 0.5, targetUserId = 1
Output: [2]

Example 3:

Input: records = [["id", "city", "age"],
                  ["1", "NYC", "25"],
                  ["2", "NYC", "30"],
                  ["3", "LA", "30"],
                  ["4", "LA", "40"]],
       weights = ["city:0.6", "age:0.4"], threshold = 0.4, targetUserId = 1
Output: [2, 3]
 */

class Solution {
private:
    unordered_map<string, double> field_to_weight_;
    vector<string> fields_;

    void parse_weight(string& str) {
        int pos = str.find(":");
        string field = str.substr(0, pos);
        double weight = stod(str.substr(pos + 1));
        field_to_weight_[field] = weight;
    }

    void get_linked_users(vector<int>& rst, unordered_map<int, unordered_map<string, string>>& user_record, int tgt_id,
                          double threshold) {
        unordered_map<string, string>& tgt_record = user_record[tgt_id];
        for (auto& [uid, record] : user_record) {
            if (uid == tgt_id) {
                continue;
            }

            double score = 0.0;
            for (auto& [key, val] : record) {
                if (field_to_weight_.find(key) == field_to_weight_.end()) {
                    continue;
                }

                if (val == tgt_record[key]) {
                    score += field_to_weight_[key];
                }
            }

            if (score >= threshold) {
                rst.push_back(uid);
            }
        }
    }

public:
    vector<int> findLinkedUsers(vector<vector<string>> records, vector<string> weights, double threshold,
                                int targetUserId) {
        for (string& str : weights) {
            parse_weight(str);
        }

        unordered_map<int, unordered_map<string, string>> user_record;
        for (int i = 1; i < records.size(); i++) {
            vector<string>& record = records[i];
            int usr_id = stoi(record[0]);
            user_record[usr_id] = unordered_map<string, string>();
            for (int j = 1; j < record.size(); j++) {
                user_record[usr_id][records[0][j]] = record[j];
            }
        }

        if (user_record.find(targetUserId) == user_record.end()) {
            return vector<int>{};
        }

        vector<int> direct_users;
        unordered_set<int> rst;
        get_linked_users(direct_users, user_record, targetUserId, threshold);
        rst.insert(direct_users.begin(), direct_users.end());
        for (int uid : direct_users) {
            vector<int> linked_users;
            get_linked_users(linked_users, user_record, uid, threshold);
            for (int id : linked_users) {
                if (id != targetUserId) {
                    rst.insert(id);
                }
            }
        }
        return vector<int>(rst.begin(), rst.end());
    }
};

/*
Follow-up 2:
In this follow-up, return all record ids that are in the same connected component as the target record, where an edge
exists between any two records whose similarity score is at least threshold. Include all records that are reachable from
the target through a sequence of such similarity links, using the rules from the previous questions, excluding the
target profile itself. You may return the result in any order.

Example 1:

Input: records = [["id", "city", "age"],
                  ["1", "NYC", "25"],
                  ["2", "NYC", "30"],
                  ["3", "LA", "30"],
                  ["4", "LA", "40"]],
       weights = ["city:0.6", "age:0.4"], threshold = 0.4, targetUserId = 1
Output: [2, 3, 4]
Explanation: Profiles 2, 3, and 4 are all connected to the target (ID = 1) through a sequence of similarity links, so
the answer is [2, 3, 4].

Example 2:

Input: records = [["id", "name", "email", "company"],
                  ["1", "Alice", "alice@gmail.com", "Stripe"],
                  ["2", "Alicia", "alice@gmail.com", "Stripe"],
                  ["3", "Alice", "alice@yahoo.com", "Google"],
                  ["4", "Bob", "bob@gmail.com", "Stripe"]],
       weights = ["name:0.2", "email:0.5", "company:0.3"], threshold = 0.5, targetUserId = 1
Output: [2]

Example 3:

Input: records = [["id", "f1", "f2"],
                  ["1", "a", "b"],
                  ["2", "a", "c"],
                  ["3", "a", "b"],
                  ["4", "x", "y"],
                  ["5", "x", "z"]],
       weights = ["f1:0.5", "f2:0.5"], threshold = 0.5, targetUserId = 1
Output: [2, 3]
*/

#include <vector>
#include <string>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <queue>
using namespace std;

class Solution {
private:
    bool isLinked(const vector<vector<string>>& records, const vector<int>& cols, const vector<double>& weightList,
                  double threshold, int row1, int row2) {
        double score = 0.0;

        for (int i = 0; i < cols.size(); i++) {
            int col = cols[i];
            double weight = weightList[i];
            if (records[row1][col] == records[row2][col]) {
                score += weight;
            }
        }

        return score >= threshold;
    }

public:
    vector<int> findLinkedUsers(vector<vector<string>> records, vector<string> weights, double threshold,
                                int targetUserId) {
        // Parse header
        unordered_map<string, int> field_to_idx;
        for (int i = 0; i < records[0].size(); i++) {
            field_to_idx[records[0][i]] = i;
        }

        // Parse weights
        int usr_id_idx = field_to_idx["id"];
        vector<int> cols;
        vector<double> weightList;
        for (const string& w : weights) {
            size_t colonPos = w.find(':');
            string field = w.substr(0, colonPos);
            double weight = stod(w.substr(colonPos + 1));
            cols.push_back(field_to_idx[field]);
            weightList.push_back(weight);
        }

        unordered_map<int, int> idRow;  // Build id -> row lookup
        for (int i = 1; i < records.size(); i++) {
            int id = stoi(records[i][usr_id_idx]);
            idRow[id] = i;
        }

        if (idRow.find(targetUserId) == idRow.end()) {
            return vector<int>();
        }

        // BFS
        unordered_set<int> seenIds;
        unordered_set<int> result;
        queue<int> queue;

        seenIds.insert(targetUserId);
        queue.push(targetUserId);

        while (!queue.empty()) {
            int curId = queue.front();
            queue.pop();
            int curRow = idRow[curId];
            for (int r = 1; r < records.size(); r++) {
                int candId = stoi(records[r][usr_id_idx]);
                if (seenIds.count(candId)) {
                    continue;
                }

                if (isLinked(records, cols, weightList, threshold, curRow, r)) {
                    seenIds.insert(candId);
                    if (candId != targetUserId) {
                        result.insert(candId);
                    }
                    queue.push(candId);
                }
            }
        }

        return vector<int>(result.begin(), result.end());
    }
};