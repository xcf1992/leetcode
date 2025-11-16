/*
1136. Parallel Courses
There are N courses, labelled from 1 to N.

We are given relations[i] = [X, Y],
representing a prerequisite relationship between course X and course Y:
course X has to be studied before course Y.

In one semester you can study any number of courses
as long as you have studied all the prerequisites for the course you are studying.

Return the minimum number of semesters needed to study all courses.
If there is no way to study all the courses, return -1.

Example 1:
1       3
 \    /
    2
Input: N = 3, relations = [[1,3],[2,3]]
Output: 2
Explanation:
In the first semester, courses 1 and 2 are studied. In the second semester, course 3 is studied.
Example 2:



Input: N = 3, relations = [[1,2],[2,3],[3,1]]
Output: -1
Explanation:
No course can be studied because they depend on each other.


Note:

1 <= N <= 5000
1 <= relations.length <= 5000
relations[i][0] != relations[i][1]
There are no repeated relations in the input.
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
using namespace std;

class Solution {
    // bfs 72.3%
public:
    int minimumSemesters(int n, vector<vector<int>>& relations) {
        vector<int> pre_cnt(n, 0);
        vector<unordered_set<int>> next_courses(n);
        for (vector<int>& relation : relations) {
            int pre = relation[0] - 1;
            int after = relation[1] - 1;
            pre_cnt[after] += 1;
            next_courses[pre].insert(after);
        }

        queue<int> bfs;
        int left_cnt = n;
        for (int i = 0; i < n; ++i) {
            if (pre_cnt[i] == 0) {
                bfs.push(i);
                left_cnt -= 1;
            }
        }

        if (bfs.empty()) {
            return -1;
        }

        int rst = 0;
        while (!bfs.empty()) {
            rst += 1;
            int curSize = bfs.size();
            for (int i = 0; i < curSize; ++i) {
                int cur = bfs.front();
                bfs.pop();

                for (int nxt : next_courses[cur]) {
                    pre_cnt[nxt] -= 1;
                    if (pre_cnt[nxt] == 0) {
                        bfs.push(nxt);
                        left_cnt -= 1;
                    }
                }
            }
        }
        return left_cnt == 0 ? rst : -1;
    }
};

class Solution1 {
    // 36.6%
public:
    int minimumSemesters(int N, vector<vector<int>>& relations) {
        vector<int> preCount(N, 0);
        vector<unordered_set<int>> learnAfter(N);
        for (vector<int>& relation : relations) {
            preCount[relation[1] - 1] += 1;
            learnAfter[relation[0] - 1].insert(relation[1] - 1);
        }

        int courseLeft = N;
        int result = 0;
        while (courseLeft > 0) {
            result += 1;
            vector<int> complelted;
            for (int i = 0; i < N; ++i)
                if (preCount[i] == 0) {
                    complelted.push_back(i);
                    preCount[i] = -1;
                    courseLeft -= 1;
                }

            if (complelted.empty()) {
                break;
            }

            for (int c : complelted) {
                for (int nxt : learnAfter[c]) {
                    preCount[nxt] -= 1;
                }
            }
        }
        return courseLeft == 0 ? result : -1;
    }
};