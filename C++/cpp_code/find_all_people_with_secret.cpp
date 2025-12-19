/*
https://leetcode.com/problems/find-all-people-with-secret/description/
2092. Find All People With Secret

You are given an integer n indicating there are n people numbered from 0 to n - 1. You are also given a 0-indexed 2D
integer array meetings where meetings[i] = [xi, yi, timei] indicates that person xi and person yi have a meeting at
timei. A person may attend multiple meetings at the same time. Finally, you are given an integer firstPerson.

Person 0 has a secret and initially shares the secret with a person firstPerson at time 0. This secret is then shared
every time a meeting takes place with a person that has the secret. More formally, for every meeting, if a person xi has
the secret at timei, then they will share the secret with person yi, and vice versa.

The secrets are shared instantaneously. That is, a person may receive the secret and share it with people in other
meetings within the same time frame.

Return a list of all the people that have the secret after all the meetings have taken place. You may return the answer
in any order.



Example 1:

Input: n = 6, meetings = [[1,2,5],[2,3,8],[1,5,10]], firstPerson = 1
Output: [0,1,2,3,5]
Explanation:
At time 0, person 0 shares the secret with person 1.
At time 5, person 1 shares the secret with person 2.
At time 8, person 2 shares the secret with person 3.
At time 10, person 1 shares the secret with person 5.​​​​
Thus, people 0, 1, 2, 3, and 5 know the secret after all the meetings.
Example 2:

Input: n = 4, meetings = [[3,1,3],[1,2,2],[0,3,3]], firstPerson = 3
Output: [0,1,3]
Explanation:
At time 0, person 0 shares the secret with person 3.
At time 2, neither person 1 nor person 2 know the secret.
At time 3, person 3 shares the secret with person 0 and person 1.
Thus, people 0, 1, and 3 know the secret after all the meetings.
Example 3:

Input: n = 5, meetings = [[3,4,2],[1,2,1],[2,3,1]], firstPerson = 1
Output: [0,1,2,3,4]
Explanation:
At time 0, person 0 shares the secret with person 1.
At time 1, person 1 shares the secret with person 2, and person 2 shares the secret with person 3.
Note that person 2 can share the secret at the same time as receiving it.
At time 2, person 3 shares the secret with person 4.
Thus, people 0, 1, 2, 3, and 4 know the secret after all the meetings.


Constraints:

2 <= n <= 105
1 <= meetings.length <= 105
meetings[i].length == 3
0 <= xi, yi <= n - 1
xi != yi
1 <= timei <= 105
1 <= firstPerson <= n - 1
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
#include <climits>
#include <set>
using namespace std;

// union find
class Solution {
private:
    // Path compression is the key optimization here
    int find(vector<int>& parent, int cur) {
        if (parent[cur] == -1) {
            return cur;
        }
        parent[cur] = find(parent, parent[cur]);
        return parent[cur];
    }
public:
    vector<int> findAllPeople(int n, vector<vector<int>>& meetings, int firstPerson) {
        vector<int> parent(n, -1);

        // Connect firstPerson and 0.
        // Typically we make 0 the parent, but your way works too.
        parent[firstPerson] = 0;

        sort(meetings.begin(), meetings.end(), [](vector<int>& a, vector<int>& b) {
            return a[2] < b[2];
        });

        // Group meetings by time
        map<int, vector<pair<int, int>>> groups;
        for (vector<int>& meeting : meetings) {
            groups[meeting[2]].push_back({meeting[0], meeting[1]});
        }

        for (auto it = groups.begin(); it != groups.end(); ++it) {
            vector<pair<int, int>>& group = it->second;

            // 1. UNION PHASE: Connect everyone meeting at this time
            for (auto& [p1 ,p2] : group) {
                int parent1 = find(parent, p1);
                int parent2 = find(parent, p2);
                if (parent1 != parent2) {
                    // Without rank, we just arbitrarily attach parent1 to parent2
                    parent[parent1] = parent2;
                }
            }

            // 2. RESET PHASE: Disconnect those who aren't connected to 0
            for (auto& [p1 ,p2] : group) {
                if (find(parent, p1) != find(parent, 0)) {
                    parent[p1] = -1;
                    parent[p2] = -1;
                }
            }
        }

        vector<int> rst;
        for (int i = 0; i < n; i++) {
            if (find(parent, i) == find(parent, 0)) {
                rst.push_back(i);
            }
        }
        return rst;
    }
};

// BFS TLE if pure BFS, adding priority queue
class Solution {
public:
    vector<int> findAllPeople(int n, vector<vector<int>>& meetings, int firstPerson) {
        unordered_map<int, vector<pair<int, int>>> connected;
        for (vector<int>& meeting : meetings) {
            int p1 = meeting[0];
            int p2 = meeting[1];
            int time = meeting[2];
            connected[p1].push_back({time, p2});
            connected[p2].push_back({time, p1});
        }

        vector<bool> visited(n, false);
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        pq.push({0, firstPerson});
        pq.push({0, 0});
        while (!pq.empty()) {
            int person = pq.top().second;
            int known_time = pq.top().first;
            pq.pop();

            if (visited[person]) {
                continue;
            }

            visited[person] = true;
            for (pair<int, int>& con : connected[person]) {
                int meet_t = con.first;
                int next_p = con.second;
                if (!visited[next_p] && meet_t >= known_time) {
                    pq.push({meet_t, next_p});
                }
            }
        }

        vector<int> rst;
        for (int i = 0; i < n; i++) {
            if (visited[i]) {
                rst.push_back(i);
            }
        }
        return rst;
    }
};