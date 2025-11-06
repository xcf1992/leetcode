/*
547. Friend Circles
https://leetcode.com/problems/friend-circles/

There are N students in a class.
Some of them are friends, while some are not.
Their friendship is transitive in nature.
For example, if A is a direct friend of B, and B is a direct friend of C,
then A is an indirect friend of C.
And we defined a friend circle is a group of students who are direct or indirect friends.

Given a N*N matrix M representing the friend relationship between students in the class.
If M[i][j] = 1, then the ith and jth students are direct friends with each other,
otherwise not.
And you have to output the total number of friend circles among all the students.

Example 1:
Input:
[[1,1,0],
 [1,1,0],
 [0,0,1]]
Output: 2
Explanation:The 0th and 1st students are direct friends, so they are in a friend circle.
The 2nd student himself is in a friend circle. So return 2.
Example 2:
Input:
[[1,1,0],
 [1,1,1],
 [0,1,1]]
Output: 1
Explanation:The 0th and 1st students are direct friends, the 1st and 2nd students are direct friends,
so the 0th and 2nd students are indirect friends. All of them are in the same friend circle, so return 1.
Note:
N is in range [1,200].
M[i][i] = 1 for all students.
If M[i][j] = 1, then M[j][i] = 1.
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

class Solution {
private:
    int find(int num, vector<int>& friends) {
        if (friends[num] != num) {
            friends[num] = find(friends[num], friends);
        }
        return friends[num];
    }

    void unin(int num1, int num2, vector<int>& friends, vector<int>& count) {
        int f1 = find(num1, friends);
        int f2 = find(num2, friends);
        if (f1 == f2) {
            return;
        }

        if (count[f1] > count[f2]) {
            friends[f2] = f1;
            count[f1] += count[f2];
            return;
        }
        friends[f1] = f2;
        count[f2] += count[f1];
    }

public:
    int findCircleNum(vector<vector<int>>& M) {
        int n = M.size();
        vector<int> friends(n, -1);
        iota(friends.begin(), friends.end(), 0);
        vector<int> count(n, 1);

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j)
                if (M[i][j]) {
                    unin(i, j, friends, count);
                }
        }

        int result = 0;
        for (int i = 0; i < n; ++i)
            if (friends[i] == i) {
                result += 1;
            }
        return result;
    }
};

class Solution1 {
private:
    void visit(vector<vector<int>>& M, vector<bool>& visited, int start) {
        visited[start] = true;
        for (int i = 0; i < M[0].size(); i++) {
            if (!visited[i] and M[start][i]) {
                visit(M, visited, i);
            }
        }
    }

public:
    int findCircleNum(vector<vector<int>>& M) {
        vector<bool> visited(M.size(), false);
        int result = 0;
        for (int i = 0; i < M.size(); i++) {
            if (!visited[i]) {
                visited[i] = true;
                result += 1;
                for (int j = 0; j < M[0].size(); j++) {
                    if (!visited[j] and M[i][j]) {
                        visit(M, visited, j);
                    }
                }
            }
        }
        return result;
    }
};