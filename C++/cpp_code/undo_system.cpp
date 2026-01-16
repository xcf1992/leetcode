/*
359. Logger Rate Limiter
Design a logger system that receive stream of messages along with its timestamps,
each message should be printed if and only if it is not printed in the last 10 seconds.

Given a message and a timestamp (in seconds granularity),
return true if the message should be printed in the given timestamp,
otherwise returns false.

It is possible that several messages arrive roughly at the same time.

Example:

Logger logger = new Logger();

// logging string "foo" at timestamp 1
logger.shouldPrintMessage(1, "foo"); returns true;

// logging string "bar" at timestamp 2
logger.shouldPrintMessage(2,"bar"); returns true;

// logging string "foo" at timestamp 3
logger.shouldPrintMessage(3,"foo"); returns false;

// logging string "bar" at timestamp 8
logger.shouldPrintMessage(8,"bar"); returns false;

// logging string "foo" at timestamp 10
logger.shouldPrintMessage(10,"foo"); returns false;

// logging string "foo" at timestamp 11
logger.shouldPrintMessage(11,"foo"); returns true;
*/
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <cmath>
#include <queue>
#include <map>
#include <climits>
using namespace std;

struct ListNode {
    string command_;
    unordered_set<string> tags_;
    ListNode* next_;
    ListNode* prev_;
    int cmd_idx_;

    ListNode(string command, vector<string> tags, int idx) : command_(command) {
        tags_.insert(tags.begin(), tags.end());
        prev_ = nullptr;
        next_ = nullptr;
        cmd_idx_ = idx;
    }
};

class CommandSystem {
private:
    unordered_map<string, int> msg_timestamp;

    ListNode* cmd_chain_;

    unordered_map<string, map<int, ListNode*>> tag_to_cmd_;

    int cmd_cnt_;
public:
    CommandSystem() {
        msg_timestamp.clear();
        cmd_chain_ = new ListNode("head", {}, 0);
        cmd_cnt_ = 0;
    }

    void execute(string& command, vector<string>& tags) {
        cmd_cnt_ += 1;
        ListNode* new_cmd = new ListNode(command, tags, cmd_cnt_);
        ListNode* tail = cmd_chain_->prev_;
        tail->next_ = new_cmd;
        new_cmd->prev_ = tail;
        cmd_chain_->prev_ = new_cmd;
        new_cmd->next_ = cmd_chain_;

        for (string& tag : tags) {
            tag_to_cmd_[tag].insert({cmd_cnt_, new_cmd});
        }
    }

    string undo(string tag) {
        if (tag == "") {
            if (cmd_chain_ -> next_ == cmd_chain_) {
                return "";
            }

            ListNode* tail = cmd_chain_->next_;
            tail->prev_->next_ = cmd_chain_;
            cmd_chain_->prev_ = tail->prev_;

            int cmd_idx = tail->cmd_idx_;
            for (auto& [tag, cmd_map] : tag_to_cmd_) {
                cmd_map.erase(cmd_idx);
            }
            return tail->command_;
        }

        if (tag_to_cmd_.find(tag) == tag_to_cmd_.end() || tag_to_cmd_[tag].empty()) {
            return "";
        }

        ListNode* rm_cmd = tag_to_cmd_[tag].rbegin()->second;
        rm_cmd->prev_->next_ = rm_cmd->next_;
        rm_cmd->next_->prev_ = rm_cmd->prev_;

        int cmd_idx = rm_cmd->cmd_idx_;
        for (const string& rm_tag : rm_cmd->tags_) {
            tag_to_cmd_[rm_tag].erase(cmd_idx);
        }
        return rm_cmd->command_;
    }
};

/*
 * Your Logger object will be instantiated and called as such:
 * Logger obj = new Logger();
 * bool param_1 = obj.shouldPrintMessage(timestamp,message);
 */