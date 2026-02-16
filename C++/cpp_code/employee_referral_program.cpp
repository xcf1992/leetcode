/*
Full Question Description
Goal: Build a leaderboard showing the top 3 users with the highest cumulative referral counts.

The Rules:

Direct & Indirect Credit: If A refers B, and B refers C, A's count is 2 (B and C), and B's count is 1 (C).

Order of Operations: Referral pairs are given in chronological order. A user can only be referred once. Once a user is
on the platform (either as an initial referrer or a new referral), they cannot be "referred" again by anyone else.

The Leaderboard:

Only include users with at least 1 referral.

The list should be sorted by count (descending).

Tie-breaking: If counts are equal, sort by username (alphabetical/ascending).

Return a maximum of 3 results in the format: "User Count".
*/
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>

using namespace std;

struct UserStats {
    string name;
    int count;
};

vector<string> getReferralLeaderboard(vector<string>& referrers, vector<string>& referrals) {
    unordered_map<string, int> counts;
    // Maps a user to the person who referred them
    unordered_map<string, string> parent;

    for (int i = 0; i < referrers.size(); ++i) {
        string r_er = referrers[i];  // Referrer
        string r_al = referrals[i];  // Referral

        // Map the new user's parent
        parent[r_al] = r_er;

        // Traverse up the chain to give credit to all ancestors
        string current = r_er;
        while (true) {
            counts[current]++;
            // If the current user has no parent, we've reached the top of the chain
            if (parent.find(current) == parent.end()) {
                break;
            }
            current = parent[current];
        }
    }

    // Convert map to a sortable vector
    vector<UserStats> leaderboard;
    for (auto const& [name, count] : counts) {
        leaderboard.push_back({name, count});
    }

    // Sort: Primary (Count DESC), Secondary (Name ASC)
    sort(leaderboard.begin(), leaderboard.end(), [](const UserStats& a, const UserStats& b) {
        if (a.count != b.count) {
            return a.count > b.count;
        }
        return a.name < b.name;
    });

    // Format output for top 3
    vector<string> result;
    for (int i = 0; i < min((int)leaderboard.size(), 3); ++i) {
        result.push_back(leaderboard[i].name + " " + to_string(leaderboard[i].count));
    }

    return result;
}

int main() {
    vector<string> referrers = {"A", "B", "C"};
    vector<string> referrals = {"B", "C", "D"};

    vector<string> top3 = getReferralLeaderboard(referrers, referrals);

    for (const string& s : top3) {
        cout << s << endl;
    }
    // Expected Output:
    // A 3
    // B 2
    // C 1
    return 0;
}