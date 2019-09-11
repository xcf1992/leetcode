/*
355. Design Twitter
https://leetcode.com/problems/design-twitter/

Design a simplified version of Twitter where users can post tweets,
follow/unfollow another user and is able to see the 10 most recent tweets in the user's news feed.
Your design should support the following methods:

postTweet(userId, tweetId):
Compose a new tweet.

getNewsFeed(userId):
Retrieve the 10 most recent tweet ids in the user's news feed.
Each item in the news feed must be posted by users who the user followed or by the user herself.
Tweets must be ordered from most recent to least recent.

follow(followerId, followeeId):
Follower follows a followee.

unfollow(followerId, followeeId):
Follower unfollows a followee.

Example:

Twitter twitter = new Twitter();

// User 1 posts a new tweet (id = 5).
twitter.postTweet(1, 5);

// User 1's news feed should return a list with 1 tweet id -> [5].
twitter.getNewsFeed(1);

// User 1 follows user 2.
twitter.follow(1, 2);

// User 2 posts a new tweet (id = 6).
twitter.postTweet(2, 6);

// User 1's news feed should return a list with 2 tweet ids -> [6, 5].
// Tweet id 6 should precede tweet id 5 because it is posted after tweet id 5.
twitter.getNewsFeed(1);

// User 1 unfollows user 2.
twitter.unfollow(1, 2);

// User 1's news feed should return a list with 1 tweet id -> [5],
// since user 1 is no longer following user 2.
twitter.getNewsFeed(1);
*/
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <map>
#include <unordered_set>
#include <algorithm>
#include <cmath>
#include <queue>
#include <stack>
#include <stdio.h>
#include <set>
using namespace std;

struct Tweet {
    int id;
    int time;

    Tweet(int i, int t): id(i), time(t) {}
};

class Twitter {
private:
    unordered_map<int, unordered_set<int>> iFollow;
    unordered_map<int, vector<Tweet>> tweets;
    int curTime = 0;
public:
    /** Initialize your data structure here.*/
    Twitter() {}

    /** Compose a new tweet.*/
    void postTweet(int userId, int tweetId) {
        tweets[userId].push_back(Tweet(tweetId, curTime));
        curTime += 1;
    }

    /*
     * Retrieve the 10 most recent tweet ids in the user's news feed.
     * Each item in the news feed must be posted by users who the user followed or by the user herself.
     * Tweets must be ordered from most recent to least recent.
    */
    vector<int> getNewsFeed(int userId) {
        auto comp = [](Tweet& a, Tweet& b) {
            return a.time < b.time;
        };
        priority_queue<Tweet, vector<Tweet>, decltype(comp)> maxHeap(comp);

        unordered_set<int> users(iFollow[userId]);
        users.insert(userId);
        for (int user : users) {
            for (Tweet t : tweets[user]) {
                maxHeap.push(t);
            }
        }

        vector<int> result;
        while (!maxHeap.empty() and result.size() < 10) {
            result.push_back(maxHeap.top().id);
            maxHeap.pop();
        }
        return result;
    }

    /** Follower follows a followee. If the operation is invalid, it should be a no-op.*/
    void follow(int followerId, int followeeId) {
        iFollow[followerId].insert(followeeId);
    }

    /** Follower unfollows a followee. If the operation is invalid, it should be a no-op.*/
    void unfollow(int followerId, int followeeId) {
        if (iFollow[followerId].find(followeeId) == iFollow[followerId].end()) {
            return;
        }
        iFollow[followerId].erase(iFollow[followerId].find(followeeId));
    }
};
/**
 * Your Twitter object will be instantiated and called as such:
 * Twitter obj = new Twitter();
 * obj.postTweet(userId,tweetId);
 * vector<int> param_2 = obj.getNewsFeed(userId);
 * obj.follow(followerId,followeeId);
 * obj.unfollow(followerId,followeeId);
*/
