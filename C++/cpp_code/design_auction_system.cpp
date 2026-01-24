/*
https://leetcode.com/problems/design-auction-system/description/
3815. Design Auction System

You are asked to design an auction system that manages bids from multiple users in real time.

Each bid is associated with a userId, an itemId, and a bidAmount.

Implement the AuctionSystem class:​​​​​​​

AuctionSystem(): Initializes the AuctionSystem object.
void addBid(int userId, int itemId, int bidAmount): Adds a new bid for itemId by userId with bidAmount. If the same
userId already has a bid on itemId, replace it with the new bidAmount. void updateBid(int userId, int itemId, int
newAmount): Updates the existing bid of userId for itemId to newAmount. It is guaranteed that this bid exists. void
removeBid(int userId, int itemId): Removes the bid of userId for itemId. It is guaranteed that this bid exists. int
getHighestBidder(int itemId): Returns the userId of the highest bidder for itemId. If multiple users have the same
highest bidAmount, return the user with the highest userId. If no bids exist for the item, return -1.


Example 1:

Input:
["AuctionSystem", "addBid", "addBid", "getHighestBidder", "updateBid", "getHighestBidder", "removeBid",
"getHighestBidder", "getHighestBidder"]
[[], [1, 7, 5], [2, 7, 6], [7], [1, 7, 8], [7], [2, 7], [7], [3]]

Output:
[null, null, null, 2, null, 1, null, 1, -1]

Explanation

AuctionSystem auctionSystem = new AuctionSystem(); // Initialize the Auction system
auctionSystem.addBid(1, 7, 5); // User 1 bids 5 on item 7
auctionSystem.addBid(2, 7, 6); // User 2 bids 6 on item 7
auctionSystem.getHighestBidder(7); // return 2 as User 2 has the highest bid
auctionSystem.updateBid(1, 7, 8); // User 1 updates bid to 8 on item 7
auctionSystem.getHighestBidder(7); // return 1 as User 1 now has the highest bid
auctionSystem.removeBid(2, 7); // Remove User 2's bid on item 7
auctionSystem.getHighestBidder(7); // return 1 as User 1 is the current highest bidder
auctionSystem.getHighestBidder(3); // return -1 as no bids exist for item 3


Constraints:

1 <= userId, itemId <= 5 * 104
1 <= bidAmount, newAmount <= 109
At most 5 * 104 total calls to addBid, updateBid, removeBid, and getHighestBidder.
The input is generated such that for updateBid and removeBid, the bid from the given userId for the given itemId will be
valid.
*/
#include <iostream>
#include <string>
#include <set>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <cmath>
#include <queue>
#include <stack>
#include <climits>
#include <map>
using namespace std;

class AuctionSystem {
    unordered_map<int, unordered_map<int, int>> item_to_user_to_bid_;
    unordered_map<int, set<pair<int, int>>> item_to_bid_and_user_;

public:
    void addBid(int u, int i, int a) {
        if (item_to_user_to_bid_[i].find(u) != item_to_user_to_bid_[i].end()) {
            item_to_bid_and_user_[i].erase({item_to_user_to_bid_[i][u], u});
        }

        item_to_user_to_bid_[i][u] = a;
        item_to_bid_and_user_[i].insert({a, u});
    }

    void updateBid(int u, int i, int a) {
        addBid(u, i, a);
    }

    void removeBid(int u, int i) {
        item_to_bid_and_user_[i].erase({item_to_user_to_bid_[i][u], u});
        item_to_user_to_bid_[i].erase(u);
    }

    int getHighestBidder(int i) {
        return item_to_bid_and_user_[i].empty() ? -1 : item_to_bid_and_user_[i].rbegin()->second;
    }
};

struct ItemBid {
    // Stores bidAmount -> set of userIds (sorted ascending)
    map<int, set<int>> bid_to_uids;
    // Stores userId -> bidAmount
    unordered_map<int, int> uid_to_bid;
};

class AuctionSystem {
private:
    unordered_map<int, ItemBid> item_ids_;

public:
    AuctionSystem() {}

    void addBid(int userId, int itemId, int bidAmount) {
        // If user already has a bid, we must remove the old one first to "replace" it
        if (item_ids_[itemId].uid_to_bid.count(userId)) {
            removeBid(userId, itemId);
        }

        ItemBid& item = item_ids_[itemId];
        item.uid_to_bid[userId] = bidAmount;
        item.bid_to_uids[bidAmount].insert(userId);
    }

    void updateBid(int userId, int itemId, int newAmount) {
        // Since it's guaranteed to exist, we remove and re-add
        removeBid(userId, itemId);
        addBid(userId, itemId, newAmount);
    }

    void removeBid(int userId, int itemId) {
        ItemBid& item = item_ids_[itemId];
        int old_bid = item.uid_to_bid[userId];

        // Remove from both structures
        item.bid_to_uids[old_bid].erase(userId);
        if (item.bid_to_uids[old_bid].empty()) {
            item.bid_to_uids.erase(old_bid);
        }
        item.uid_to_bid.erase(userId);
    }

    int getHighestBidder(int itemId) {
        if (item_ids_.find(itemId) == item_ids_.end() || item_ids_[itemId].bid_to_uids.empty()) {
            return -1;
        }

        ItemBid& item = item_ids_[itemId];
        // map::rbegin() gives the entry with the highest bidAmount
        // set::rbegin() gives the highest userId for that amount
        return *(item.bid_to_uids.rbegin()->second.rbegin());
    }
};

/**
 * Your AuctionSystem object will be instantiated and called as such:
 * AuctionSystem* obj = new AuctionSystem();
 * obj->addBid(userId,itemId,bidAmount);
 * obj->updateBid(userId,itemId,newAmount);
 * obj->removeBid(userId,itemId);
 * int param_4 = obj->getHighestBidder(itemId);
 */