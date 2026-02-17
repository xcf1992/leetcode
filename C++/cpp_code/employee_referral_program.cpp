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

Robinhood is famous for its referral program. It’s exciting to see our users spreading the word across their friends and
family. One thing that is interesting about the program is the network effect it creates. We would like to build a
dashboard to track the status of the program. Specifically, we would like to learn about how people refer others through
the chain of referral.

For the purpose of this question, we consider that a person refers all other people down the referral chain. For
example, A refers B, C, and D in a referral chain of A -> B -> C -> D. Please build a leaderboard for the top 3 users
who have the most referred users along with the referral count.

Referral rules:

A user can only be referred once.
Once the user is on the RH platform, he/she cannot be referred by other users. For example: if A refers B, no other user
can refer A or B since both of them are on the RH platform. Referrals in the input will appear in the order they were
made. Leaderboard rules:

The user must have at least 1 referral count to be on the leaderboard.
The leaderboard contains at most 3 users.
The list should be sorted by the referral count in descending order.
If there are users with the same referral count, break the ties by the alphabetical order of the user name.
Input

rh_users –> array.string
new_users –> array.string
rh_users = ["A", "B", "C"]
| | |
v v v
new_users = ["B", "C", "D"]
Output

array.string
["A 3", "B 2", "C 1"]
** note: at the beginning of the interview, the output may be returning [“a”,”b”] as starter code.

Additional Details

[execution time limit] 4 seconds
[memory limit] 1GB
[input] array.string rh_users
A list of referring users
[input] array.string new_users
A list of users that was referred by the users in the referrers array in the same order
[output] array.string
An array of 3 users on the leaderboard. Each of the elements here would have the “[user] [referral count]” format. For
example, “A 4”
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