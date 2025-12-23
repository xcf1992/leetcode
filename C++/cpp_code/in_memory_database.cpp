/*
https://github.com/JesseZhuang/InCodeLearning-Python3/blob/main/algorithm/ood/in_memory_db.py

code signal in memory database
Level 1
The basic level of the in-memory database contains records.
Each record can be accessed with a unique identifier key, which is of string type. A record contains several
field - value pairs, with field as string type and value as integer type. All operations have a timestamp parameter
 - a string field timestamp in milliseconds. It is guaranteed that all timestamps are unique and are in a range
  from 1 to 10^9 . Operations will be given in order of strictly increasing timestamps. Timestamps will be needed
   starting from Level 3.

• set(self, timestamp: int, key: str, field: str, value: int) -> None
- should insert a field - value pair to the record associated with key. If the field in the record already exists,
 replace the existing value with the specified value. If the record does not exist, a new one is created.

• compare_and_set (self, timestamp: int, key: str, field: str, expected_value: int, new_value: int) -› bool
 - should update the value of field in the record associated with key to new_value if the current value equals
  expected value. If expected value does not match the current value, or either key or field does not exist,
   this operation is ignored. This operation should return True if the field was updated and False otherwise.

- compare_and_delete (self, timestamp: int, key: str, field: str, expected value: int) -> bool
— Should remove the field in the record associated with key if the previous value equals expected_value.
If expected_value does not match the current value, or either key or field does not exist, this operation is ignored.
 This operation should return True if the field was removed and False otherwise.

• get (self, timestamp: int, key: sti, field: str) -> int | None — should return the value contained within
field of the record associated with key. If the record or the field does not exist, should return None.

other notes

2. implement with timestamp: set, get, delete, set_with_ttl，cannot get if ttl expires.
3. implement scan and scan_with_prefix
4. 实现 backup and restore，backup就是take snapshot，restore就是把指定时间的snapshot给恢复了。
题目不难，90分钟的题，65分钟搞定，得到600满分。(Holly!)
需要注意的点：
1. 搞snapshot的时候要用copy.deepcopy，把class里的所有的状态无脑copy一份存了。
2. 不用花时间优化，能brute force就不要写binary search，能过test case 就行。
3. 有的set不带ttl，那就把过期时间设为 float('inf')，后期的处理能省不少事儿

Level 2
The database should support displaying data based on filters.
Introduce an operation to support printing some fields of a record.

• scan (self, timestamp: int, key: str) -> list[str]
— should return a list of strings representing the fields of the record associated with key. The returned list should
be in the following format ["‹field_1>(<value_1>)", " <field_2>(‹value_2>)", ...] , where fields are sorted
 lexicographically. If the specified record does not exist, returns an empty list.

• scan_by_prefix(self, timestamp: int, key: str, prefix: str) -> list[str] - should return a list of
strings representing some fields of the record associated with key. Specifically, only fields that start with prefix
 should be included. The returned list should be in the same format as in the scan operation with fields sorted in
 lexicographical order.

我的思路是将field map变成TreeMap (java 选手...)，scan by prefix用regex匹配搜索

Level 3
Support the TTL (Time-To-Live) settings for records and fields.
For each field - value pair in the database, the TTL determines how long that value will persist before being removed.

Note: All relevant operations defined in previous levels are assumed to have an infinite TTL.
• set_with_ttl (self, timestamp: int, key: str, field: str, value: int, ttl: int) -> None
 - should insert the specified value and set its Time-To-Live starting at timestamp. If the field in the record
 already exists, then update its value and TTL. The ttl parameter represents the number of time units that this field
  - value pair should exist in the database, meaning it will be available during this interval:
  [timestamp, timestamp + ttl) . It is guaranteed that ttl is greater than 0.

• compare_and_set_with_ttl (self, timestamp: int, key: str, field: str,
expected_value: int, new_value: int, ttl: int) -> bool
 - the same as compare_and_set, but should also update TTL of the new_value. This operation should return True
 if the field was updated and False otherwise. It is guaranteed that ttl is greater than 0.

我在这里花了最多时间以至于没来得及写下一题，主要是没理解题目要求 "SET_AT" 是指带上了timestamp，但是没有expire time，
如果之前对同一个<key>+<field>设置过 "SET_AT_WITH_TTL"，则再次调用"SET_AT" 时需要将expire time设为永久
我的思路是field map的value变成一对值 (value, expireTime)，expireTime为永久的搞个 null 啥的

Level 4

The database should be backed up from time to time. Introduce operations to support backing up and restoring the
 database state based on timestamps. When restoring, ttl expiration times should be recalculated accordingly.

• BACKUP ‹timestamp> — should save the database state at the specified timestamp, including the remaining ttl
 for all records and fields. Remaining ttl is the difference between their initial ttl and their current lifespan
  (the duration between the timestamp of this operation and their initial timestamp). Returns a string representing
   the number of non-empty non-expired records in the database.
• RESTORE ‹timestamps «timestampToRestore›
— should restore the database from the latest backup before or at timestampToRestore. It's guaranteed that a backup
 before or at timestampToRestore will exist. Expiration

Assumption: delete_at, set_at, set_at_with_ttl, .etc. should not affect existing backups.
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

class Item {
public:
    map<string, int> filed_to_val_;
    unordered_map<string, long long> field_expiry_;

    Item() {
    }
};

class InMemDb {
public:
    unordered_map<string, Item> key_to_item_;
    map<int, unordered_map<string, Item>> backups_;

    InMemDb() {}

    bool is_expired(string key, string field, int cur_ts) {
        if (key_to_item_.find(key) == key_to_item_.end()) {
            return true;
        }
        Item& item = key_to_item_[key];

        if (item.filed_to_val_.find(field) == item.filed_to_val_.end()) {
            return true;
        }

        // If expiry is -1, it never expires
        if (item.field_expiry_.count(field) && item.field_expiry_[field] != -1) {
            if (cur_ts >= item.field_expiry_[field]) {
                // Lazy deletion
                item.filed_to_val_.erase(field);
                item.field_expiry_.erase(field);
                return true;
            }
        }
        return false;
    }

    void set(string key, string field, int value, int cur_ts) {
        if (key_to_item_.find(key) == key_to_item_.end()) {
            key_to_item_[key] = Item();
        }

        Item& item = key_to_item_[key];
        item.filed_to_val_[field] = value;
        item.field_expiry_[field] = -1;  // -1 mean infinite
    }

    void set_at(string key, string field, int value, int cur_ts, int set_at_ts) {
        if (key_to_item_.find(key) == key_to_item_.end()) {
            key_to_item_[key] = Item();
        }

        Item& item = key_to_item_[key];
        item.filed_to_val_[field] = value;
        item.field_ts_[field] = set_at_ts;
        item.field_ttl_[field] = -1;  // -1 mean infinite
    }

    void set_with_ttl(string key, string field, int value, int ttl, int cur_ts) {
        if (key_to_item_.find(key) == key_to_item_.end()) {
            key_to_item_[key] = Item();
        }

        Item& item = key_to_item_[key];
        item.filed_to_val_[field] = value;
        item.field_ts_[field] = cur_ts;
        item.field_ttl_[field] = ttl;
    }

    void set_at_with_ttl(string key, string field, int value, int cur_ts, int ttl, int set_at_ts) {
        if (key_to_item_.find(key) == key_to_item_.end()) {
            key_to_item_[key] = Item();
        }

        Item& item = key_to_item_[key];
        item.filed_to_val_[field] = value;
        item.field_ts_[field] = set_at_ts;
        item.field_ttl_[field] = ttl;
    }

    bool compare_and_set(string key, string field, int cur_ts, int expected_val, int new_val) {
        if (key_to_item_.find(key) == key_to_item_.end()) {
            return false;
        }

        Item& item = key_to_item_[key];
        if (item.filed_to_val_.find(field) == item.filed_to_val_.end()) {
            return false;
        }

        if (item.filed_to_val_[field] != expected_val) {
            return false;
        }

        item.filed_to_val_[field] = new_val;
        item.field_expiry_[field] = -1;
        return true;
    }

    bool compare_and_set_with_ttl(string key, string field, int cur_ts, int expected_val, int new_val, int ttl) {
        if (key_to_item_.find(key) == key_to_item_.end()) {
            return false;
        }

        Item& item = key_to_item_[key];
        if (item.filed_to_val_.find(field) == item.filed_to_val_.end()) {
            return false;
        }

        if (item.filed_to_val_[field] != expected_val) {
            return false;
        }

        item.filed_to_val_[field] = new_val;
        item.field_ts_[field] = cur_ts;
        item.field_ttl_[field] = ttl;
        return true;
    }

    // bool delete_at(string key, string field, int cur_ts) {
    //     if (key_to_item_.find(key) == key_to_item_.end()) {
    //         return false;
    //     }
    //
    //     Item& item = key_to_item_[key];
    //     if (item.filed_to_val_.find(field) == item.filed_to_val_.end()) {
    //         return false;
    //     }
    //
    //     item.field_ts_[field] = cur_ts;
    //     item.field_ttl_[field] = ttl;
    //     return true;
    // }

    bool compare_and_delete(string key, string field, int cur_ts, int expected_val, int new_val) {
        if (key_to_item_.find(key) == key_to_item_.end()) {
            return false;
        }

        Item& item = key_to_item_[key];
        if (item.filed_to_val_.find(field) == item.filed_to_val_.end()) {
            return false;
        }

        if (item.filed_to_val_[field] != expected_val) {
            return false;
        }

        item.filed_to_val_.erase(field);
        item.field_expiry_.erase(field);
        return true;
    }

    int get(string key, string field, int cur_ts) {
        if (is_expired(key, field, cur_ts)) {
            return -1;
        }

        return key_to_item_[key].filed_to_val_[field];
    }

    vector<string> scan(int cur_ts, string key) {
        if (key_to_item_.find(key) == key_to_item_.end()) return {};

        Item& item = key_to_item_[key];
        vector<string> rst;
        // map iterates in lexicographical order by default
        for (auto const& [field, val] : item.filed_to_val_) {
            if (!is_expired(key, field, cur_ts)) {
                rst.push_back(field + "(" + to_string(val) + ")");
            }
        }
        return rst;
    }

    vector<string> scan_at(int at_ts, string key) {
        if (key_to_item_.find(key) == key_to_item_.end()) {
            return vector<string>();
        }

        Item& item = key_to_item_[key];
        vector<string> rst;
        for (auto it = item.filed_to_val_.begin(); it != item.filed_to_val_.end(); ++it) {
            const string& field = it->first;
            if (item.field_ttl_.find(field) != item.field_ttl_.end() && item.field_ttl_[field] != -1 &&
                item.field_ts_[field] + item.field_ttl_[field] <= at_ts) {
                continue;
            }
            rst.push_back(field + "(" + to_string(it->second) + ")");
        }
        return rst;
    }

    vector<string> scan_by_prefix(int cur_ts, string key, string prefix) {
        if (key_to_item_.find(key) == key_to_item_.end()) return {};

        Item& item = key_to_item_[key];
        vector<string> rst;
        for (auto const& [field, val] : item.filed_to_val_) {
            if (field.find(prefix) == 0 && !is_expired(key, field, cur_ts)) {
                rst.push_back(field + "(" + to_string(val) + ")");
            }
        }
        return rst;
    }

    int backup(int cur_ts) {
        unordered_map<string, Item> snapshot;
        int non_empty_records = 0;

        for (auto& [key, item] : key_to_item_) {
            Item snap_item;
            for (auto const& [field, val] : item.filed_to_val_) {
                // Only backup if not expired
                if (!is_expired(key, field, cur_ts)) {
                    snap_item.filed_to_val_[field] = val;
                    // Store remaining TTL: Expiry - current time
                    long long expiry = item.field_expiry_[field];
                    snap_item.field_expiry_[field] = (expiry == -1) ? -1 : expiry - cur_ts;
                }
            }
            if (!snap_item.filed_to_val_.empty()) {
                snapshot[key] = snap_item;
                non_empty_records++;
            }
        }
        backups_[cur_ts] = snapshot;
        return non_empty_records;
    }

    int restore(int cur_ts, int ts_to_restore) {
        // Find latest backup at or before timestampToRestore
        auto it = backups_.upper_bound(ts_to_restore);
        if (it == backups_.begin()) return 0;
        --it;

        key_to_item_.clear();
        unordered_map<string, Item>& snapshot = it->second;

        for (auto const& [key, snap_item] : snapshot) {
            Item newItem;
            for (auto const& [field, val] : snap_item.filed_to_val_) {
                newItem.filed_to_val_[field] = val;
                // Recalculate expiry: Restore time + remaining TTL
                long long remaining = snap_item.field_expiry_.at(field);
                newItem.field_expiry_[field] = (remaining == -1) ? -1 : (long long)cur_ts + remaining;
            }
            key_to_item_[key] = newItem;
        }
    }

private:
    bool start_with(string& prefix, const string& filed_name) {
        if (filed_name.size() < prefix.size()) {
            return false;
        }

        for (int i = 0; i < prefix.size(); i++) {
            if (prefix[i] != filed_name[i]) {
                return false;
            }
        }
        return true;
    }
};