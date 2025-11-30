/*
839. Similar String Groups

Two strings X and Y are similar if we can swap two letters (in different positions) of X,
so that it equals Y.

For example, "tars" and "rats" are similar (swapping at positions 0 and 2),
and "rats" and "arts" are similar,
but "star" is not similar to "tars", "rats", or "arts".

Together, these form two connected groups by similarity: {"tars", "rats", "arts"} and {"star"}.
Notice that "tars" and "arts" are in the same group even though they are not similar.
Formally, each group is such that a word is in the group,
if and only if it is similar to at least one other word in the group.

We are given a list A of strings.
Every string in A is an anagram of every other string in A.
How many groups are there?

Example 1:
Input: ["tars","rats","arts","star"]
Output: 2

Note:
A.length <= 2000
A[i].length <= 1000
A.length * A[i].length <= 20000
All words in A consist of lowercase letters only.
All words in A have the same length and are anagrams of each other.
The judging time limit has been increased for this question.
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
#include <numeric>
using namespace std;

class Solution {  // use union find
private:
    int find(vector<int>& parent, int num) {
        if (parent[num] != num) {
            parent[num] = find(parent, parent[num]);
        }
        return parent[num];
    }

    bool similar(string a, string b) {
        int diff = 0;
        for (int i = 0; i < a.size(); i++)
            if (a[i] != b[i]) {
                diff += 1;
                if (diff > 2) {
                    return false;
                }
            }
        return true;
    }

public:
    int numSimilarGroups(vector<string>& A) {
        int n = A.size();
        vector<int> parent(n);
        iota(parent.begin(), parent.end(), 0);

        for (int i = 0; i < n; ++i) {
            int p1 = find(parent, i);
            for (int j = i + 1; j < n; ++j) {
                if (similar(A[i], A[j])) {
                    int p2 = find(parent, j);
                    if (p1 != p2) {
                        parent[p2] = p1;
                    }
                }
            }
        }

        int result = 0;
        for (int i = 0; i < n; ++i) {
            if (parent[i] == i) {
                result += 1;
            }
        }
        return result;
    }
};

class Solution1 {
    // 14.07%
private:
    bool similar(string a, string b) {
        int diff = 0;
        for (int i = 0; i < a.size(); i++) {
            if (a[i] != b[i]) {
                diff++;
            }
        }
        return diff == 2 or (diff == 0 and a.size() >= 2);
    }

public:
    int numSimilarGroups(vector<string>& A) {
        int n = A.size();
        if (n <= 1) {
            return n;
        }

        vector<bool> visited(n, false);
        int result = 0;
        queue<int> bfs;
        for (int i = 0; i < n; i++) {
            if (visited[i]) {
                continue;
            }

            result += 1;
            visited[i] = true;
            bfs.push(i);
            while (!bfs.empty()) {
                int cur = bfs.front();
                bfs.pop();
                for (int next = 0; next < n; next++) {
                    if (visited[next] or !similar(A[cur], A[next])) {
                        continue;
                    }
                    visited[next] = true;
                    bfs.push(next);
                }
            }
        }
        return result;
    }
};