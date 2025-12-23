/*
https://github.com/JesseZhuang/InCodeLearning-Python3/blob/main/algorithm/ood/cloud_storage.py

code signal, cloud storage
Level 1
The cloud storage system should support file manipulation.
• ADD_FILE <name> ‹size> — should add a new file name to the storage. size is the amount of memory required in bytes.
The current operation fails if a file with the same name already exists. Returns "true" if the file was added
successfully or "false" otherwise.
• GET_FILE_SIZE <name> - Should return a string representing the size of the file name if it exists, or an empty
string otherwise.
• DELETE_FILE ‹name> — should delete the file name. Returns a string representing the deleted file size if the
deletion was successful or an empty string if the file does not exist.
Level 2
Implement an operation for retrieving some statistics about files with a specific prefix.
• GET_N LARGEST ‹prefix› <n> — should return the string representing the names of the top n-largest files with
names starting with prefix in the following format: "‹name1›(<size1>), ..., <nameN> (<sizeN>)". Returned files
should be sorted by size in descending order, or in case of a tie, sorted in lexicographical order of the names.
If there are no such files, return an empty string. If the number of such files is less than n, all of them
  should be returned in the specified format.
Level 3
Implement support for queries from different users. All users share a common filesystem in the cloud storage system,
 but each user is assigned a storage capacity limit.
• ADD_USER ‹userId ‹capacity› — should add a new user in the system, with capacity as their storage limit in bytes.
 The total size of all files owned by userId cannot exceed capacity. The operation fails if a user with userId
 already exists. Returns "true" if a user with userId is successfully created, or "False" otherwise.
• ADD_FILE_BY <userId ‹name> ‹size> - should behave in the same way as the ADD_FILE from Level 1, but the added
 file should be owned by the user with userId. A new file cannot be added to the storage if doing so will exceed
  the user's capacity limit. Returns a string representing the remaining capacity of the user if the file is added
successfully, or an empty string otherwise.
Note that all queries calling the ADD_FILE operation implemented during Level 1 are run by the user with
userId = "admin", who has unlimited storage capacity.
• MERGE_USER <userId1> <userId2> - should merge the account of userId2 with the userId1. Ownership of
 all of userId2 's files is transferred to userId1, and any remaining storage capacity is also added to
 userId1's limit. userId2 is deleted if the merge is successful. Returns a string representing the remaining
  capacity of userId1 after merging, or an empty string if one of the users does not exist or userId1 is
  equal to userId2. It is guaranteed that neither userId1 nor userId2 equals "admin".

Level 4
Implement support to allow users to back up their files.
• BACKUP_USER < userId> - should back up the current state of all files owned by userid - i.e., file names and sizes.
 The backup is stored on a separate storage system and is not affected by any new file manipulation queries.
  Overwrites any backups for the same user if previous backups exist. Returns a string representing the number
  of backed-up files, or an empty string if userid does not exist.
• RESTORE _USER ‹userId> — should restore the state of userId 's files to the latest backup. If there was no backup,
 all of userid 's files are deleted. If a file can't be restored because another user added another file with
  the same name, it is ignored. Returns a string representing the number of the files that are successfully restored
  or an empty string if userId does not exist.

Note that MERGE_USER does not affect userId's backup, and userid2 is deleted along with its backup.
Note that the RESTORE_USER operation does not affect the user's capacity. Badly worded, test cases show capacity
increased back when restore deleted all user's files. It actually means the initial capacity not changed.
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
#include <numeric>
using namespace std;

class File {
public:
    string name_;
    int size_;
    string user_id_;

    File() : name_(""), size_(0), user_id_("") {
    }

    File(string file_name, int file_size, string file_user) : name_(file_name), size_(file_size), user_id_(file_user) {
    }
};

class User {
public:
    string user_id_;
    int available_cap_;
    unordered_set<string> files_;
    unordered_map<string, File> backup_;

    User() : user_id_(""), available_cap_(0) {
    }
    User(string user_id, int available_cap) : user_id_(user_id), available_cap_(available_cap) {
    }
};

class CloudStorage {
public:
    unordered_map<string, User> users_;
    unordered_map<string, File> files_;

    CloudStorage() {
        users_.clear();
        files_.clear();
        users_["admin"] = User("admin", -1);
    }

    bool add_user(string user_id, int capacity) {
        if (users_.find(user_id) != users_.end()) {
            return false;
        }

        users_[user_id] = User(user_id, capacity);
        return true;
    }

    bool add_file(string file_name, int file_size) {
        if (files_.find(file_name) != files_.end()) {
            return false;
        }

        File new_file = File(file_name, file_size, "admin");
        files_.emplace(file_name, new_file);
        users_["admin"].files_.insert(file_name);
        return true;
    }

    string add_file_by(string user_id, string file_name, int file_size) {
        if (files_.find(file_name) != files_.end()) {
            return "";
        }

        if (users_.find(user_id) == users_.end()) {
            return "";
        }

        User& cur_user = users_[user_id];
        if (cur_user.available_cap_ < file_size) {
            return "";
        }

        File new_file = File(file_name, file_size, user_id);
        files_[file_name] = new_file;
        users_[user_id].available_cap_ -= file_size;
        users_[user_id].files_.insert(file_name);
        return to_string(cur_user.available_cap_);
    }

    string get_file_size(string file_name) {
        if (files_.find(file_name) != files_.end()) {
            return to_string(files_[file_name].size_);
        }
        return "";
    }

    string delete_file(string file_name) {
        if (files_.find(file_name) == files_.end()) {
            return "";
        }

        string user_id = files_[file_name].user_id_;
        int file_size = files_[file_name].size_;
        users_[user_id].files_.erase(file_name);
        users_[user_id].available_cap_ += file_size;
        files_.erase(file_name);
        return to_string(file_size);
    }

    string n_largest(string prefix, int n) {
        vector<File*> rst;
        for (auto it = files_.begin(); it != files_.end(); ++it) {
            string file_name = it->first;
            if (!start_with(prefix, file_name)) {
                continue;
            }
            rst.push_back(&files_[file_name]);
        }

        if (rst.empty()) {
            return "";
        }

        sort(rst.begin(), rst.end(), [](File* a, File* b) {
            return a->size_ > b->size_ || (a->size_ == b->size_ && a->name_ < b->name_);
        });

        string rst_str = "";
        int limit = min((int)rst.size(), n);
        for (int i = 0; i < limit; ++i) {
            rst_str += rst[i]->name_ + "(" + to_string(rst[i]->size_) + "), ";
        }

        if (!rst_str.empty()) {
            // Remove trailing comma and space
            rst_str.pop_back();
            rst_str.pop_back();
        }
        return rst_str;
    }

    string merge_user(string user_id_1, string user_id_2) {
        if (users_.find(user_id_1) == users_.end() || users_.find(user_id_2) == users_.end() ||
            user_id_1 == user_id_2) {
            return "";
        }

        User& user_1 = users_[user_id_1];
        User& user_2 = users_[user_id_2];
        for (const string& file_name : user_2.files_) {
            files_[file_name].user_id_ = user_id_1;
            user_1.files_.insert(file_name);
        }
        user_1.available_cap_ += user_2.available_cap_;
        users_.erase(user_id_2);
        return to_string(user_1.available_cap_);
    }

    string backup(string user_id) {
        if (users_.find(user_id) == users_.end()) {
            return "";
        }

        User& cur_user = users_[user_id];
        cur_user.backup_.clear();
        for (const string& file_name : cur_user.files_) {
            File& cur_file = files_[file_name];
            cur_user.backup_[file_name] = File(cur_file.name_, cur_file.size_, cur_file.user_id_);
        }
        return to_string(cur_user.files_.size());
    }

    string restore(string user_id) {
        if (users_.find(user_id) == users_.end()) {
            return "";
        }

        User& cur_user = users_[user_id];
        vector<string> current_files(cur_user.files_.begin(), cur_user.files_.end());
        for (const string& file_name : current_files) {
            delete_file(file_name);
        }

        if (cur_user.backup_.size() == 0) {
            return "0";
        }

        int rst = 0;
        for (auto it = cur_user.backup_.begin(); it != cur_user.backup_.end(); ++it) {
            if (add_file_by(user_id, it->first, it->second.size_) != "") {
                rst += 1;
            }
        }
        return to_string(rst);
    }

private:
    bool start_with(string& prefix, string& file_name) {
        if (file_name.size() < prefix.size()) {
            return false;
        }

        for (int i = 0; i < prefix.size(); i++) {
            if (prefix[i] != file_name[i]) {
                return false;
            }
        }
        return true;
    }
};