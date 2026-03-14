/*
https://www.hack2hire.com/companies/openai/coding-questions/69b070d6a4e93c007df3fc35/practice?questionId=69b191c3a4e93c007df4004d
Snapshot Social Graph

Design a social network system that tracks follow relationships between users while maintaining the historical state
through snapshots. The system should allow users to follow and unfollow each other over time, and provide the ability to
query whether a specific follow relationship existed at any previous snapshot.

Implement the SocialNetwork class:

SocialNetwork() Initializes an empty social network.

void follow(int followerId, int followeeId) Records that user followerId begins following user followeeId in the current
working state.

void unfollow(int followerId, int followeeId) Records that user followerId stops following user
followeeId in the current working state.

int createSnapshot() Captures the current state of all follow relationships and
returns a unique snapshot identifier. The first snapshot has ID 0, and subsequent snapshots increment by 1.

boolean isFollowing(int followerId, int followeeId, int snapId) Returns true if user followerId was following user
followeeId at the time snapshot snapId was created; otherwise returns false.

Note: Your solution is expected to handle historical queries and data efficiently, even when thousands of snapshots have
been created.

Constraints:

1 ≤ followerId, followeeId, userId ≤ 105
0 ≤ snapId < 105
At most 105 calls will be made in total to all operations.
Example

Input:
["SocialNetwork", "follow", "follow", "createSnapshot", "unfollow", "isFollowing", "isFollowing", "isFollowing"]
[[], [1, 2], [2, 1], [], [1, 2], [1, 2, 0], [2, 1, 0], [1, 2, 1]]

Output:
[null, null, null, 0, null, true, true, false]

Explanation:

SocialNetwork sn = new SocialNetwork();
sn.follow(1, 2); // User 1 follows User 2.
sn.follow(2, 1); // User 2 follows User 1.
sn.createSnapshot(); // Returns 0. This snapshot captures the mutual follow state.
sn.unfollow(1, 2); // User 1 unfollows User 2.
sn.isFollowing(1, 2, 0); // Returns true. Since the unfollow happened after snapshot 0, User 1 was still following User
2 at that time. sn.isFollowing(2, 1, 0); // Returns true. sn.isFollowing(1, 2, 1); // Returns false.
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
#include <sstream>
using namespace std;

/*
Follow-up 1:
Now extend the SocialNetwork class to retrieve lists of a user's connections at any given historical snapshot.

Implement the following additional methods:

List<Integer> getFollowers(int userId, int snapId) Returns a list of user IDs who were following userId at the given
snapshot. You may return the result in any order.

List<Integer> getFollowees(int userId, int snapId) Returns a list of user IDs whom userId was following at the given
snapshot. You may return the result in any order.

Example

Input:
["SocialNetwork", "follow", "follow", "createSnapshot", "getFollowers", "getFollowees"]
[[], [1, 2], [3, 2], [], [2, 0], [1, 0]]

Output:
[null, null, null, 0, [1, 3], [2]]

Explanation:

SocialNetwork sn = new SocialNetwork();
sn.follow(1, 2); // User 1 follows User 2.
sn.follow(3, 2); // User 3 follows User 2.
sn.createSnapshot(); // Returns 0.
sn.getFollowers(2, 0); // Returns [1, 3]. Both User 1 and User 3 are following User 2 at snapshot 0.
sn.getFollowees(1, 0); // Returns [2]. User 1 is following User 2 at snapshot 0.

Follow-up 2:
Now extend the SocialNetwork class to recommend new users for a specific user to follow based on a "friends of friends"
logic at a given snapshot.

Implement the following additional method:

List<Integer> recommendUsers(int userId, int snapId, int k) Recommends the top k users for userId to follow based on the
state at snapId, following the rules below: At snapshot snapId, recommendations are generated based on second-degree
follow relationships. A user is considered a candidate if they are followed by at least one of userId's followees at
snapshot snapId.

A user is considered invalid as a candidate if they are the original userId, or if they are already directly followed by
userId at snapId.

Each valid candidate receives a score equal to the number of followees of userId who follow that candidate at the same
snapshot. Candidates are then ordered in descending order of score. If multiple candidates share the same score, they
are ordered by ascending user ID.

The result should contain at most the top k ranked candidates. If fewer than k valid candidates exist, return all
available candidates.

Constraints:

1 ≤ k ≤ 100
Example

Input:
["SocialNetwork", "follow", "follow", "follow", "follow", "createSnapshot", "recommendUsers"]
[[], [1, 2], [1, 3], [2, 4], [3, 4], [], [1, 0, 1]]

Output:
[null, null, null, null, null, 0, [4]]

Explanation:

SocialNetwork sn = new SocialNetwork();
sn.follow(1, 2); // User 1 follows User 2.
sn.follow(1, 3); // User 1 follows User 3.
sn.follow(2, 4); // User 2 follows User 4.
sn.follow(3, 4); // User 3 follows User 4.
sn.createSnapshot(); // Returns 0.
sn.recommendUsers(1, 0, 1); // Returns [4]. User 1's followees at snapshot 0 are [2, 3]. Both User 2 and User 3 follow
User 4, giving User 4 a count of 2. Since User 1 is not following User 4, it is the top recommendation.
*/
class SocialNetwork {
private:
    unordered_map<string, vector<pair<int, int>>> relation_change_time_;
    int cur_snapshot_id_;

    unordered_map<int, unordered_set<int>> related_followers_;
    unordered_map<int, unordered_set<int>> related_followees_;

    string build_key(int followerId, int followeeId) {
        return to_string(followerId) + "_" + to_string(followeeId);
    }

    void record_change(int followerId, int followeeId, int latest_val) {
        related_followers_[followeeId].insert(followerId);
        related_followees_[followerId].insert(followeeId);

        string key = build_key(followerId, followeeId);
        if (relation_change_time_.find(key) == relation_change_time_.end()) {
            relation_change_time_[key] = vector<pair<int, int>>();
        }

        if (relation_change_time_[key].empty()) {
            relation_change_time_[key].push_back({cur_snapshot_id_, latest_val});
            return;
        }

        if (relation_change_time_[key].back().first == cur_snapshot_id_) {
            relation_change_time_[key].back().second = latest_val;
            return;
        }

        relation_change_time_[key].push_back({cur_snapshot_id_, latest_val});
    }

public:
    SocialNetwork() {
        relation_change_time_ = unordered_map<string, vector<pair<int, int>>>();
        cur_snapshot_id_ = 0;
    }

    void follow(int followerId, int followeeId) {
        record_change(followerId, followeeId, 1);
    }

    void unfollow(int followerId, int followeeId) {
        record_change(followerId, followeeId, 0);
    }

    int createSnapshot() {
        int rst = cur_snapshot_id_;
        cur_snapshot_id_ += 1;
        return rst;
    }

    bool isFollowing(int followerId, int followeeId, int snapId) {
        string key = build_key(followerId, followeeId);
        if (relation_change_time_.find(key) == relation_change_time_.end()) {
            return false;
        }

        vector<pair<int, int>>& change_history = relation_change_time_[key];
        auto it = upper_bound(change_history.begin(), change_history.end(), make_pair(snapId, 2));
        if (it == change_history.begin()) {
            return false;
        }

        return prev(it)->second;
    }

    vector<int> getFollowers(int userId, int snapId) {
        vector<int> rst;
        if (related_followers_.find(userId) == related_followers_.end()) {
            return rst;
        }

        for (int usr : related_followers_[userId]) {
            if (isFollowing(usr, userId, snapId)) {
                rst.push_back(usr);
            }
        }
        return rst;
    }

    vector<int> getFollowees(int userId, int snapId) {
        vector<int> rst;
        if (related_followees_.find(userId) == related_followees_.end()) {
            return rst;
        }

        for (int usr : related_followees_[userId]) {
            if (isFollowing(userId, usr, snapId)) {
                rst.push_back(usr);
            }
        }
        return rst;
    }

    vector<int> recommendUsers(int userId, int snapId, int k) {
        vector<int> cur_followees = getFollowees(userId, snapId);
        unordered_set<int> cur_followees_set(cur_followees.begin(), cur_followees.end());
        unordered_map<int, int> candidate_score;
        for (int usr : cur_followees_set) {
            for (int candidate : getFollowees(usr, snapId)) {
                if (candidate == userId || cur_followees_set.find(candidate) != cur_followees_set.end()) {
                    continue;
                }

                candidate_score[candidate] += 1;
            }
        }

        vector<pair<int, int>> sorted_candidates;
        for (auto& [can, score] : candidate_score) {
            sorted_candidates.push_back({score, can});
        }
        sort(sorted_candidates.begin(), sorted_candidates.end(), [](pair<int, int>& a, pair<int, int>& b) {
            return a.first > b.first || (a.first == b.first && a.second < b.second);
        });

        vector<int> rst;
        for (pair<int, int>& can : sorted_candidates) {
            rst.push_back(can.second);
            if (rst.size() >= k) {
                break;
            }
        }
        return rst;
    }
};