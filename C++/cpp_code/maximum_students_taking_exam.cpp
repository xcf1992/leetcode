/*
1349. Maximum Students Taking Exam
https://leetcode.com/problems/maximum-students-taking-exam/

Given a m * n matrix seats that represent seats distributions in a classroom.
If a seat is broken, it is denoted by '#' character otherwise it is denoted by a '.' character.

Students can see the answers of those sitting next to the left, right, upper left and upper right,
but he cannot see the answers of the student sitting directly in front or behind him.
Return the maximum number of students that can take the exam together without any cheating being possible..

Students must be placed in seats in good condition.

Example 1:
Input: seats = [["#",".","#","#",".","#"],
                [".","#","#","#","#","."],
                ["#",".","#","#",".","#"]]
Output: 4
Explanation: Teacher can place 4 students in available seats so they don't cheat on the exam.

Example 2:
Input: seats = [[".","#"],
                ["#","#"],
                ["#","."],
                ["#","#"],
                [".","#"]]
Output: 3
Explanation: Place all students in available seats.

Example 3:
Input: seats = [["#",".",".",".","#"],
                [".","#",".","#","."],
                [".",".","#",".","."],
                [".","#",".","#","."],
                ["#",".",".",".","#"]]
Output: 10
Explanation: Place students in available seats in column 1, 3 and 5.

Constraints:
seats contains only characters '.' and'#'.
m == seats.length
n == seats[i].length
1 <= m <= 8
1 <= n <= 8
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
#include "extra_data_types.hpp"
using namespace std;

class Solution {
private:
    int m = 0;
    int n = 0;

    bool canSit(int row, int col, vector<vector<char> > &seats) {
        if (row < 0 or row
        >=
        m or col<0 or col >= n or seats[row][col] != '.'
        )
        {
            return false;
        }

        if (col > 0 and seats[row][col - 1]
        ==
        's'
        )
        {
            return false;
        }
        if (col < n - 1 and seats[row][col + 1]
        ==
        's'
        )
        {
            return false;
        }

        if (row > 0 and col
        >
        0
        and seats[row - 1][col - 1]
        ==
        's'
        )
        {
            return false;
        }
        if (row > 0 and col<n - 1 and seats[row - 1][col + 1] == 's'
        )
        {
            return false;
        }
        return true;
    }

    unordered_map<int, int> memo;

    int dfs(int row, int col, int prev, int cur, vector<vector<char> > &seats) {
        if (row == m) {
            return 0;
        }

        if (col == 0) {
            prev = cur;
            cur = 0;
        }

        int key = (prev << 16) | (cur << 8) | (row << 4) | col;
        if (memo.find(key) != memo.end()) {
            return memo[key];
        }

        int nextR = row;
        int nextC = col + 1;
        if (nextC == n) {
            nextR += 1;
            nextC = 0;
        }

        memo[key] = dfs(nextR, nextC, prev, cur, seats);
        if (canSit(row, col, seats)) {
            cur |= (1 << col);
            seats[row][col] = 's';
            memo[key] = max(memo[key], 1 + dfs(nextR, nextC, prev, cur, seats));
            seats[row][col] = '.';
        }
        return memo[key];
    }

public:
    int maxStudents(vector<vector<char> > &seats) {
        m = seats.size();
        n = seats[0].size();
        return dfs(0, 0, 0, 0, seats);
    }
};