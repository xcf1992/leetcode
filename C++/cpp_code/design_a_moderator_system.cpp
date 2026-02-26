/*
https://www.hack2hire.com/companies/reddit/coding-questions/694af9626e481a4b09cbc77c/practice?questionId=694af9676e481a4b09cbc77d
Design a Moderator System
You are designing a system that tracks moderator privileges for an online community using a time-ordered log of
moderation actions. Each log record captures when a user gains or loses moderator status. The system must support
permission checks for removing moderators and also return the current moderator list in the correct hierarchy.

In this system, moderators have a ranking based on when they most recently became moderators. Among all active
moderators, a user who became a moderator earlier has a higher level than a user who became a moderator later.

Implement the ModSystem class:

ModSystem(List<String> logs) Initializes the moderator system using the given chronological list of log entries. Each
entry is a string in the format "<targetUser>,<action>,<actorUser>,<timestamp>", where

targetUser is the user whose moderator status is affected.
action is either "added" or "removed", indicating whether the user is granted or revoked moderator status.
actorUser is the user who performed the action.
timestamp is a string represented integer.
The log entries are sorted in increasing order by timestamp.

boolean canRemoveMod(String targetUser, String actorUser) Returns true only if all of the following conditions are met.
Otherwise, returns false.

Both targetUser and actorUser are currently moderators.
actorUser is not the same user as targetUser.
actorUser has a higher moderator level than targetUser according to the ranking rules.
List<String> getModRanking() Returns the current list of moderators ordered from highest level to lowest level.

Constraints:

You may assume all the operations in the logs are valid.
All log entries are sorted in increasing order by timestamp.
1
1 ≤ logs.size() ≤
10
5
10
5

All user names are non-empty strings without commas.
All timestamps are positive numbers.
Example:

Input:
["ModSystem", "getModRanking", "canRemoveMod", "canRemoveMod"]
[["alice,added,admin,1", "bob,added,alice,2", "charlie,added,bob,3"], [], ["bob", "alice"], ["alice", "bob"]]

Output:
[null, ["alice", "bob", "charlie"], true, false]

Explanation:

ModSystem modSystem = new ModSystem(logs);
modSystem.getModRanking(); // Returns ["alice", "bob", "charlie"]. Three users are moderators; "alice" is the most
senior and "charlie" is least senior. modSystem.canRemoveMod("bob", "alice"); // Returns true. Both are moderators, and
"alice" became a moderator before "bob", so "alice" is more senior. modSystem.canRemoveMod("alice", "bob"); // Returns
false. "bob" is less senior than "alice" and cannot remove her.
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
#include <set>
#include <string>
#include <iostream>
using namespace std;

class ModSystem {
private:
    set<pair<string, string>> moderators_;
    unordered_map<string, string> active_time_;

    void parse_log(vector<string>& rst, string& log) {
        int pos = log.find(',');
        int start = 0;
        while (pos != string::npos) {
            rst.push_back(log.substr(start, pos - start));
            start = pos + 1;
            pos = log.find(',', start);
        }
        rst.push_back(log.substr(start));
    }

public:
    ModSystem(vector<string> logs) {
        for (string& log : logs) {
            vector<string> log_vals;
            parse_log(log_vals, log);
            if (log_vals[1] == "added") {
                moderators_.insert({log_vals[3], log_vals[0]});
                active_time_[log_vals[0]] = log_vals[3];
            } else if (active_time_.find(log_vals[0]) != active_time_.end()) {
                moderators_.erase({active_time_[log_vals[0]], log_vals[0]});
                active_time_.erase(log_vals[0]);
            }
        }
    }

    bool canRemoveMod(string targetUser, string actorUser) {
        if (targetUser == actorUser) {
            return false;
        }

        if (active_time_.find(targetUser) == active_time_.end() || active_time_.find(actorUser) == active_time_.end()) {
            return false;
        }
        return active_time_[targetUser] > active_time_[actorUser];
    }

    vector<string> getModRanking() {
        vector<string> rst;
        for (auto& [time, usr] : moderators_) {
            rst.push_back(usr);
        }
        return rst;
    }
};

/*
Follow-up 1:
Extend the previous question to support multiple independent communities. Each community maintains its own moderator
ranking, and all rules from the previous question apply independently within each community. Each log entry now has the
format: "<community>,<targetUser>,<action>,<actorUser>,<timestamp>".

Implement the updated ModSystem class:

ModSystem(List<String> logs) Parses all logs in chronological order and maintains the moderator state and moderator
ranking separately for each community.

boolean canRemoveMod(String community, String targetUser, String actorUser) Applies the same removal rules as the
previous question, but scoped to the given community. Returns false if the community does not exist.

List<String> getModRanking(String community) Returns the current list of moderators ordered from highest level to lowest
level for the given community. Returns an empty list if the community does not exist.

Constraints:

All constraints and guarantees from the previous question still apply.
Example:

Input:
["ModSystem", "getModRanking", "canRemoveMod", "canRemoveMod", "getModRanking"]
[["java,alice,added,admin,1", "java,bob,added,alice,2", "java,charlie,added,bob,3"], ["java"], ["java", "bob", "alice"],
["java", "alice", "bob"], ["python"]]

Output:
[null, ["alice", "bob", "charlie"], true, false, []]

Explanation:

ModSystem modSystem = new ModSystem(logs);
modSystem.getModRanking("java"); // Returns ["alice", "bob", "charlie"], the moderator ranking for "java" from most
senior to least senior. modSystem.canRemoveMod("java", "bob", "alice"); // Returns true; "alice" is more senior than
"bob" in the "java" community. modSystem.canRemoveMod("java", "alice", "bob"); // Returns false; "bob" joined after
"alice" and is less senior. modSystem.getModRanking("python"); // Returns [], since "python" does not exist.
*/

struct Community {
    string comm_name;
    set<pair<string, string>> moderators_;
    unordered_map<string, string> active_time_;

    Community() {
        comm_name = "";
    }

    Community(string name) {
        comm_name = name;
    }

    void add(string& time, string& tgt_usr, string& act_usr) {
        moderators_.insert({time, tgt_usr});
        active_time_[tgt_usr] = time;
    }

    void remove(string& time, string& tgt_usr, string& act_usr) {
        if (active_time_.find(tgt_usr) != active_time_.end()) {
            moderators_.erase({active_time_[tgt_usr], tgt_usr});
            active_time_.erase(tgt_usr);
        }
    }

    bool canRemoveMod(string targetUser, string actorUser) {
        if (targetUser == actorUser) {
            return false;
        }

        if (active_time_.find(targetUser) == active_time_.end() || active_time_.find(actorUser) == active_time_.end()) {
            return false;
        }

        return active_time_[targetUser] > active_time_[actorUser];
    }

    vector<string> get_mod_ranking() {
        vector<string> rst;
        for (auto& [time, usr] : moderators_) {
            rst.push_back(usr);
        }
        return rst;
    }

    void demote(string user) {
        if (active_time_.find(user) == active_time_.end()) {
            return;
        }

        auto it = lower_bound(moderators_.begin(), moderators_.end(), make_pair(active_time_[user], user));
        auto after = next(it);
        if (after == moderators_.end()) {
            return;
        }

        string cur_time = it->first;
        string cur_usr = it->second;
        string next_time = after->first;
        string next_usr = after->second;
        cout << "cur_time = " << cur_time << " cur_usr = " << cur_usr << " next_time = " << next_time << " next_usr = " << next_usr << endl;
        cout << "=-=-=-=" << endl;

        moderators_.erase(it);
        moderators_.erase(after);
        moderators_.insert({cur_time, next_usr});
        moderators_.insert({next_time, cur_usr});

        active_time_[cur_usr] = next_time;
        active_time_[next_usr] = cur_time;
    }
};

class ModSystem {
private:
    unordered_map<string, Community> all_comm_;
    ;

    void parse_log(vector<string>& rst, string& log) {
        int pos = log.find(',');
        int start = 0;
        while (pos != string::npos) {
            rst.push_back(log.substr(start, pos - start));
            start = pos + 1;
            pos = log.find(',', start);
        }
        rst.push_back(log.substr(start));
    }

public:
    ModSystem(vector<string> logs) {
        for (auto& log : logs) {
            vector<string> log_vals;
            parse_log(log_vals, log);

            if (all_comm_.find(log_vals[0]) == all_comm_.end()) {
                all_comm_[log_vals[0]] = Community(log_vals[0]);
            }

            Community& comm = all_comm_[log_vals[0]];
            if (log_vals[2] == "added") {
                comm.add(log_vals[4], log_vals[1], log_vals[3]);
            } else {
                comm.remove(log_vals[4], log_vals[1], log_vals[3]);
            }
        }
    }

    bool canRemoveMod(string community, string targetUser, string actorUser) {
        if (all_comm_.find(community) == all_comm_.end()) {
            return false;
        }
        return all_comm_[community].canRemoveMod(targetUser, actorUser);
    }

    vector<string> getModRanking(string community) {
        if (all_comm_.find(community) == all_comm_.end()) {
            return {};
        }
        return all_comm_[community].get_mod_ranking();
    }

    void demote(string community, string user) {
        if (all_comm_.find(community) == all_comm_.end()) {
            return;
        }
        return all_comm_[community].demote(user);
    }
};

/*
Follow-up 2:
Extend the previous problem to support moderator demotion within a community.

Enhance the updated ModSystem class by adding the following method:

void demote(String community, String user) Demotes the specified moderator within the given community.

A demotion decreases the user's moderator rank by exactly one position in the current ordering. For example, if the
current moderator ranking from highest to lowest is "user1 -> user2 -> user3", then demoting "user1" results in "user2
-> user1 -> user3". If user is already the lowest-ranked moderator, or if user is not currently a moderator in the
specified community, the operation has no effect. Constraints:

All constraints and guarantees from the previous question still apply.
Each log entry has the format "<community>,<targetUser>,<action>,<actorUser>,<timestamp>".
Example:

Input:
["ModSystem", "getModRanking", "demote", "getModRanking", "canRemoveMod", "canRemoveMod"]
[["java,user1,added,admin,1", "java,user2,added,admin,2", "java,user3,added,admin,3"], ["java"], ["java", "user1"],
["java"], ["java", "user1", "user2"], ["java", "user3", "user1"]]

Output:
[null, ["user1", "user2", "user3"], null, ["user2", "user1", "user3"], true, true]

Explanation:

ModSystem modSystem = new ModSystem(logs);
modSystem.getModRanking("java"); // Returns ["user1", "user2", "user3"], the initial ranking after all add operations.
modSystem.demote("java", "user1"); // Demotes "user1" by one position in the ranking.
modSystem.getModRanking("java"); // Returns ["user2", "user1", "user3"].
modSystem.canRemoveMod("java", "user1", "user2"); // Returns true. "user2" is now more senior than "user1".
modSystem.canRemoveMod("java", "user3", "user1"); // Returns true. "user1" is still more senior than "user3".
*/