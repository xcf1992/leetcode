/*
You are building a simplified backend for a social finance app. You receive a list of API requests, where each request
is a pair [sequenceNumber, requestString].

The API Endpoints
REGISTER: "v1/REGISTER/{user}/{initialBalance}"

Creates a user with the given balance.

FRIEND_REQUEST: "v1/FRIEND_REQUEST/{fromUser}/{toUser}"

Creates a pending friend request. You must store this request using its sequenceNumber.

FRIEND_ACCEPT: "v1/FRIEND_ACCEPT/{toUser}/{sequenceNumber}"

The user toUser accepts the pending request associated with sequenceNumber.

If the request exists and was sent to toUser, the two users become friends.

TRANSFER_MONEY: "v1/TRANSFER_MONEY/{fromUser}/{toUser}/{amount}"

Sends amount from fromUser to toUser.

Rule: This only succeeds if the users are friends and fromUser has a sufficient balance.

Constraints & Output
Requests are processed in the order they appear in the input array.

The output is typically a list of strings representing the final state or the results of specific "GET" queries (like
total balances or a list of friends), usually sorted alphabetically by username.
*/
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <map>
#include <unordered_set>
#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <iomanip>
using namespace std;

/*
We need three main data structures:

unordered_map<string, int> balances: To track user funds.

unordered_map<string, unordered_set<string>> friendships: To track who is friends with whom (bidirectional).

unordered_map<string, pair<string, string>> pendingRequests: Mapping sequenceNumber to {fromUser, toUser}.
 */
class SocialFinanceApp {
    unordered_map<string, long long> user_balance_;
    unordered_map<string, unordered_set<string>> user_to_friends_;
    // Maps sequenceNumber -> {fromUser, toUser}
    unordered_map<string, pair<string, string>> pending_friend_req_;

public:
    void processRequests(const vector<pair<string, string>>& requests) {
        for (const auto& req : requests) {
            string seqNum = req.first;
            string apiCall = req.second;

            if (apiCall.find("v1/REGISTER/") != string::npos) {
                handleRegister(apiCall);
            } else if (apiCall.find("v1/FRIEND_REQUEST/") != string::npos) {
                handleFriendRequest(seqNum, apiCall);
            } else if (apiCall.find("v1/FRIEND_ACCEPT/") != string::npos) {
                handleFriendAccept(apiCall);
            } else if (apiCall.find("v1/TRANSFER_MONEY/") != string::npos) {
                handleTransfer(apiCall);
            }
        }
    }

private:
    vector<string> split(const string& s, char delimiter) {
        vector<string> tokens;
        string token;
        istringstream tokenStream(s);
        while (getline(tokenStream, token, delimiter)) {
            if (!token.empty()) tokens.push_back(token);
        }
        return tokens;
    }

    void handleRegister(string& path) {
        auto parts = split(path, '/'); // ["v1", "REGISTER", "{user}", "{bal}"]
        user_balance_[parts[2]] = stoll(parts[3]);
    }

    void handleFriendRequest(string& seqNum, string& path) {
        auto parts = split(path, '/'); // ["v1", "FRIEND_REQUEST", "{from}", "{to}"]
        pending_friend_req_[seqNum] = {parts[2], parts[3]};
    }

    void handleFriendAccept(string& path) {
        auto parts = split(path, '/'); // ["v1", "FRIEND_ACCEPT", "{toUser}", "{seqNum}"]
        string toUser = parts[2];
        string targetSeq = parts[3];

        if (pending_friend_req_.count(targetSeq)) {
            auto& request = pending_friend_req_[targetSeq];
            // Verify the recipient matches the accept call
            if (request.second == toUser) {
                user_to_friends_[request.first].insert(request.second);
                user_to_friends_[request.second].insert(request.first);
                pending_friend_req_.erase(targetSeq);
            }
        }
    }

    void handleTransfer(string& path) {
        auto parts = split(path, '/'); // ["v1", "TRANSFER_MONEY", "{from}", "{to}", "{amt}"]
        string from = parts[2];
        string to = parts[3];
        long long amount = stoll(parts[4]);

        // Check if they are friends and balance is sufficient
        if (user_to_friends_[from].count(to) && user_balance_[from] >= amount) {
            user_balance_[from] -= amount;
            user_balance_[to] += amount;
        }
    }

public:
    void printFinalBalances() {
        // Use map for alphabetical sorting of usernames
        map<string, long long> sortedBalances(user_balance_.begin(), user_balance_.end());
        for (auto const& [user, bal] : sortedBalances) {
            cout << user << ": " << bal << endl;
        }
    }
};

int main() {
    vector<pair<string, string>> input = {
        {"1", "v1/REGISTER/Alice/100"},
        {"2", "v1/REGISTER/Bob/50"},
        {"3", "v1/FRIEND_REQUEST/Alice/Bob"},
        {"4", "v1/FRIEND_ACCEPT/Bob/3"},
        {"5", "v1/TRANSFER_MONEY/Alice/Bob/30"}
    };

    SocialFinanceApp app;
    app.processRequests(input);
    app.printFinalBalances();

    return 0;
}