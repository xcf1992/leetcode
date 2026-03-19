/*
https://www.hack2hire.com/companies/reddit/coding-questions/69557d994a0202df9569e981/practice?questionId=69557daa4a0202df9569e982
Related Communities Finder

You are given two lists describing the following relationships on a social platform:

communityToFollowers:
A 2D list where the ith element (0-indexed) represents a list of follower IDs (e.g., "F0", "F1", "F2") that follow
community Ci

followerToCommunities: A 2D list where jth element represents a list of community IDs (as strings, e.g., "C0", "C1",
"C2") that are followed by the follower Fj

Given a community index communityIdx, return a list of all distinct community IDs that share at least one follower with
the community at communityIdx, excluding communityIdx itself.

Note that only direct shared-follower relationships are considered. Do not include communities that are connected only
through chains of relationships.

If communityIdx is out of bounds or the community at that index has no followers, return an empty list.

Constraints:

0 ≤ communityIdx < 10⁴
0 ≤ communityToFollowers.size() ≤ 10⁴
0 ≤ the number of followers per community ≤ 10⁴
Each follower may follow up to 10³ communities.
Example 1:

Input: communityToFollowers = [["F0", "F2"], ["F0", "F1"], ["F1"], ["F2"]], followerToCommunities = [["C0", "C1"],
["C1", "C2"], ["C0", "C3"]], communityIdx = 3 Output: ["C0"] Explanation: Community at index 3 ("C3") is followed by
"F2". "F2" also follows "C0", so "C0" shares a follower with "C3".

Example 2:

Input: communityToFollowers = [["F0", "F2"], ["F0", "F1"], ["F1"], ["F2"]], followerToCommunities = [["C0", "C1"],
["C1", "C2"], ["C0", "C3"]], communityIdx = 1 Output: ["C0", "C2"]

Example 3:

Input: communityToFollowers = [["F0"], []], followerToCommunities = [["C0"]], communityIdx = 1
Output: []
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
using namespace std;

class Solution {
public:
    vector<string> getRelatedCommunities(vector<vector<string>> communityToFollowers,
                                         vector<vector<string>> followerToCommunities, int communityIdx) {
        int community_cnt = communityToFollowers.size();
        if (communityIdx >= community_cnt) {
            return vector<string>();
        }

        string src_community = "C" + to_string(communityIdx);
        int follower_cnt = followerToCommunities.size();
        unordered_set<string> rst;
        for (string& follower : communityToFollowers[communityIdx]) {
            int idx = stoi(follower.substr(1));
            if (idx >= follower_cnt) {
                continue;
            }

            for (string& community : followerToCommunities[idx]) {
                if (community != src_community) {
                    rst.insert(community);
                }
            }
        }
        return vector<string>(rst.begin(), rst.end());
    }
};

/*Follow-up:
Extend the function to find communities related to the community at communityIdx through both direct and indirect
shared-follower connections, up to a specified number of steps.

A community is considered related if it can be reached by repeatedly traversing direct shared-follower links, with the
maximum number of steps controlled by the integer degree.

If degree = 1, return all communities that share at least one follower with the target community.
For larger degree values, each additional step includes communities directly related to those discovered in the previous
step. Return all unique community IDs that are reachable from the target community within at most degree steps, but do
not include the community at communityIdx itself.

Constraints:

0 ≤ degree ≤ 10⁴
0 ≤ communityIdx < 10⁴
Example 1:

Input: communityToFollowers = [["F0", "F2"], ["F0", "F1"], ["F1"], ["F2"]], followerToCommunities = [["C0", "C1"],
["C1", "C2"], ["C0", "C3"]], degree = 2, communityIdx = 3 Output: ["C0", "C1"] Explanation: Both "C0" and "C1" are
reachable from "C3" in at most 2 steps:

Step 1: Community at index 3 ("C3") shares "F2" with "C0", so "C0" is found.
Step 2: "C0" shares "F0" with "C1", so "C1" is found.
Example 2:

Input: communityToFollowers = [["F0", "F2"], ["F0", "F1"], ["F1"], ["F2"]], followerToCommunities = [["C0", "C1"],
["C1", "C2"], ["C0", "C3"]], degree = 2, communityIdx = 1 Output: ["C0", "C2", "C3"]

Example 3:

Input: communityToFollowers = [["F0"], ["F0"]], followerToCommunities = [["C0", "C1"]], degree = 0, communityIdx = 0
Output: []
*/
class Solution {
public:
    vector<string> getRelatedCommunitiesWithDegree(vector<vector<string>> communityToFollowers,
                                                   vector<vector<string>> followerToCommunities, int degree,
                                                   int communityIdx) {
        int community_cnt = communityToFollowers.size();
        if (communityIdx >= community_cnt) {
            return vector<string>();
        }

        string src_community = "C" + to_string(communityIdx);
        unordered_set<string> rst;
        rst.insert(src_community);
        queue<string> bfs;
        bfs.push(src_community);

        int follower_cnt = followerToCommunities.size();
        while (!bfs.empty() && degree > 0) {
            size_t cur_size = bfs.size();
            for (size_t i = 0; i < cur_size; i++) {
                string cur_community = bfs.front();
                bfs.pop();

                int c_idx = stoi(cur_community.substr(1));
                for (string& follower : communityToFollowers[c_idx]) {
                    int f_idx = stoi(follower.substr(1));
                    if (f_idx >= follower_cnt) {
                        continue;
                    }

                    for (string& community : followerToCommunities[f_idx]) {
                        if (rst.find(community) == rst.end()) {
                            rst.insert(community);
                            bfs.push(community);
                        }
                    }
                }
            }
            degree -= 1;
        }

        rst.erase(src_community);
        return vector<string>(rst.begin(), rst.end());
    }
};
