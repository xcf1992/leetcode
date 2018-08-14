/*
 Given a set of N people (numbered 1, 2, ..., N), we would like to split everyone into two groups of any size.
 
 Each person may dislike some other people, and they should not go into the same group.
 
 Formally, if dislikes[i] = [a, b], it means it is not allowed to put the people numbered a and b into the same group.
 
 Return true if and only if it is possible to split everyone into two groups in this way.
 
 
 
 Example 1:
 
 Input: N = 4, dislikes = [[1,2],[1,3],[2,4]]
 Output: true
 Explanation: group1 [1,4], group2 [2,3]
 Example 2:
 
 Input: N = 3, dislikes = [[1,2],[1,3],[2,3]]
 Output: false
 Example 3:
 
 Input: N = 5, dislikes = [[1,2],[2,3],[3,4],[4,5],[1,5]]
 Output: false
 
 
 Note:
 
 1 <= N <= 2000
 0 <= dislikes.length <= 10000
 1 <= dislikes[i][j] <= N
 dislikes[i][0] < dislikes[i][1]
 There does not exist i != j for which dislikes[i] == dislikes[j].
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
#include <numeric>
using namespace std;

class Solution {
public:
    bool possibleBipartition(int N, vector<vector<int>>& dislikes) {
        vector<int> group(N + 1, 0); // there are 2 colors 1 & -1
        unordered_map<int, vector<int>> hate;
        for (vector<int>& d : dislikes) {
            hate[d[0]].push_back(d[1]);
            hate[d[1]].push_back(d[0]);
        }
        
        queue<int> bfs;
        for (auto cur : hate) {
            if (group[cur.first] == 0) { // untouched person
                group[cur.first] = 1;
                bfs.push(cur.first);
                
                while (!bfs.empty()) {
                    int s = bfs.front();
                    bfs.pop();
                    for (int next : hate[s]) { // all neighbors of s
                        if (group[next] == 0) {
                            group[next] = -1 * group[s];
                            bfs.push(next);
                        }
                        else if (group[next] != -1 * group[s]) {
                            return false;
                        }
                    }
                }
            }
        }
        return true;
    }
};

// Time Limit Exceed
class Solution1 {
private:
    bool dispatch(int cur, int N, unordered_set<int>& group1, unordered_set<int>& group2,
                  unordered_map<int, unordered_set<int>>& hate) {
        if (cur > N) {
            return true;
        }
        
        bool putIn1 = true;
        for (int j : hate[cur]) {
            if (group1.find(j) != group1.end()) {
                putIn1 = false;
                break;
            }
        }
        
        if (putIn1) {
            group1.insert(cur);
            if (dispatch(cur + 1, N, group1, group2, hate)) {
                return true;
            }
            group1.erase(group1.find(cur));
        }
        
        for (int j : hate[cur]) {
            if (group2.find(j) != group2.end()) {
                return false;
            }
        }
        group2.insert(cur);
        if (dispatch(cur + 1, N, group1, group2, hate)) {
            return true;
        }
        group2.erase(group2.find(cur));
        return false;
    }
public:
    bool possibleBipartition(int N, vector<vector<int>>& dislikes) {
        unordered_map<int, unordered_set<int>> hate;
        for (vector<int>& dislike : dislikes) {
            hate[dislike[0]].insert(dislike[1]);
            hate[dislike[1]].insert(dislike[0]);
        }
        
        unordered_set<int> group1;
        unordered_set<int> group2;
        return dispatch(1, N, group1, group2, hate);
    }
};
