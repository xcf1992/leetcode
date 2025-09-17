/*
911. Online Election
https://leetcode.com/problems/online-election/

In an election, the i-th vote was cast for persons[i] at time times[i].
Now, we would like to implement the following query function:

TopVotedCandidate.q(int t)
will return the number of the person that was leading the election at time t.

Votes cast at time t will count towards our query.
In the case of a tie, the most recent vote (among tied candidates) wins.

Example 1:
Input: ["TopVotedCandidate","q","q","q","q","q","q"], [[[0,1,1,0,0,1,0],[0,5,10,15,20,25,30]],[3],[12],[25],[15],[24],[8]]
Output: [null,0,1,1,0,0,1]
Explanation:
At time 3, the votes are [0], and 0 is leading.
At time 12, the votes are [0,1,1], and 1 is leading.
At time 25, the votes are [0,1,1,0,0,1], and 1 is leading (as ties go to the most recent vote.)
This continues for 3 more queries at time 15, 24, and 8.

Note:
1 <= persons.length = times.length <= 5000
0 <= persons[i] <= persons.length
times is a strictly increasing array with all elements in [0, 10^9].
TopVotedCandidate.q is called at most 10000 times per test case.
TopVotedCandidate.q(int t) is always called with t >= times[0].
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
#include <stdio.h>
#include <map>
#include <numeric>
using namespace std;

class TopVotedCandidate {
private:
    map<int, int> topVote;
public:
    TopVotedCandidate(vector<int>& persons, vector<int>& times) {
        unordered_map<int, int> count;
        int lead = -1;
        for (int i = 0; i < persons.size(); ++i) {
            int person = persons[i];
            int time = times[i];
            count[person] += 1;
            if (lead == -1 or count[person] >= count[lead]) {
                lead = person;
                topVote[time] = lead;
            }
        }
    }

    int q(int t) {
        auto it = topVote.upper_bound(t);
        return prev(it) -> second;
    }
};

class TopVotedCandidate1 {
private:
    map<int, int> topVote;
public:
    TopVotedCandidate(vector<int> persons, vector<int> times) {
        int n = persons.size();
        int lead = -1;
        unordered_map<int, int> count;
        for (int i = 0; i < n; i++) {
            topVote[times[i]] = persons[i];
        }
        for (auto& it : topVote) {
            count[it.second] += 1;
            if (lead == -1 or count[it.second] >= count[lead]) {
                lead = it.second;
            }
            topVote[it.first] = lead;
        }
    }

    int q(int t) {
        auto it = topVote.upper_bound(t);
        it--;
        return it -> second;
    }
};

/*
 * Your TopVotedCandidate object will be instantiated and called as such:
 * TopVotedCandidate obj = new TopVotedCandidate(persons, times);
 * int param_1 = obj.q(t);
*/
